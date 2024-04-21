#include "SFML_header.hpp"
#include "item.hpp";

//-----------------SHOOTER--------------------------

//constructor
bullet::bullet() {
    image = new sf::Texture;
    image->loadFromFile("CS122_PA9/bullet.png");
    sprite.setTexture(*image);
    direction = sf::Vector2f(0, 0);
    center_origin(sprite);
}

void bullet::lock_on(const sf::Sprite& origin, const sf::Sprite& target) {
    direction = normal_direction(origin, target);
    sprite.setRotation(vector_to_degrees(direction) + 180);
}

void bullet::set_position(const sf::Vector2f& position) {
    sprite.setPosition(position + 15.0f * direction);
}

sf::Sprite& bullet::get_sprite() {
    return sprite;
}

void bullet::move(const float speed) {
    sprite.move(direction * speed);
}

bullet::~bullet() {

}



void normalize_vector(sf::Vector2f& unnormalized_vec) {
    unnormalized_vec = unnormalized_vec / sqrt(powf(unnormalized_vec.x, 2) + powf(unnormalized_vec.y, 2));
}

sf::Vector2f full_direction(const sf::Sprite& origin, const sf::Sprite& target) {
    sf::Vector2f unit_direction(target.getPosition() - origin.getPosition());
    return unit_direction;
}

sf::Vector2f normal_direction(const sf::Sprite& origin, const sf::Sprite& target) {
    sf::Vector2f unit_direction(target.getPosition() - origin.getPosition());
    normalize_vector(unit_direction);
    return unit_direction;
}

float vector_to_degrees(const sf::Vector2f& vec) {
    if (vec.y == 0) return 90;
    return 90 - atan(vec.x / vec.y) * 180 / PI;
}

sf::Vector2f degrees_to_vector(float degrees) {
    int common = (90 - degrees) * PI / 180;
    return sf::Vector2f(cosf(common), sinf(common));
}

float magnitude(const sf::Vector2f& vec) {
    return sqrtf(vec.x * vec.x + vec.y * vec.y);
}

int hit_window(const sf::Sprite& shape, const float buffer, const sf::FloatRect& boundary) {
    int hit = 0;
    //buffer of 0 means half of shape can be seen
    //buffer of 1 means entire shape can be seen
    sf::Vector2f shape_size = shape.getLocalBounds().getSize();

    if (shape.getPosition().x > boundary.left + boundary.width - buffer * shape_size.x / 2) hit += 1; //hit right
    if (shape.getPosition().x < boundary.left + buffer * shape_size.x / 2) hit += 2; //hit left
    if (shape.getPosition().y < boundary.top + buffer * shape_size.y / 2) hit += 4; //hit top
    if (shape.getPosition().y > boundary.top + boundary.height - buffer * shape_size.y / 2) hit += 8; //hit bottom

    //hit relies on binary interpretation such that
    //right -> ***1, left -> **1*, up -> *1**, down -> 1***

    return hit;
}

bool touching_hitbox(const sf::Sprite& sprite1, const sf::Sprite& sprite2) {

    float x_pos_dif = sprite1.getPosition().x - sprite2.getPosition().x;
    float y_pos_dif = sprite1.getPosition().y - sprite2.getPosition().y;
    x_pos_dif = fabsf(x_pos_dif);
    y_pos_dif = fabsf(y_pos_dif);

    float x_len = sprite1.getLocalBounds().getSize().x + sprite2.getLocalBounds().getSize().x;
    float y_len = sprite1.getLocalBounds().getSize().y + sprite2.getLocalBounds().getSize().y;
    x_len /= 2.0f;
    y_len /= 2.0f;

    if (x_pos_dif < x_len && y_pos_dif < y_len) return true;
    return false;

}

bool touching_hitdisc(const sf::CircleShape& sprite1, const sf::CircleShape& sprite2) {
    float distance = magnitude(sprite1.getPosition() - sprite2.getPosition());
    float double_size = sprite1.getRadius() + sprite2.getRadius();
    if (distance <= double_size) return true;
    else return false;

}

void key_move(sf::Sprite& shape, const float user_speed, const sf::FloatRect& boundary) {

    float speed = user_speed * 0.01;
    int direction = 0;
    bool curr_move[4];
    static int last_move[4];

    sf::Keyboard::Key keys[] = { sf::Keyboard::Key::D, sf::Keyboard::Key::A , sf::Keyboard::Key::W , sf::Keyboard::Key::S };

    direction = hit_window(shape, 1, boundary);
    for (int i = 0; i < 4; i++) {
        curr_move[i] = 1 - direction % 2;
        direction >>= 1;
    }

    if (sf::Keyboard::isKeyPressed(keys[0])) shape.move(speed * curr_move[0], 0);
    else curr_move[0] = 0;

    if (sf::Keyboard::isKeyPressed(keys[1])) shape.move(-speed * curr_move[1], 0);
    else curr_move[1] = 0;

    if (sf::Keyboard::isKeyPressed(keys[2])) shape.move(0, -speed * curr_move[2]);
    else curr_move[2] = 0;

    if (sf::Keyboard::isKeyPressed(keys[3])) shape.move(0, speed * curr_move[3]);
    else curr_move[3] = 0;

    if (curr_move[0] && curr_move[1]) {
        if (last_move[0]) {
            shape.move(speed, 0);
            curr_move[1] = 0;
        }
        else {
            shape.move(-speed, 0);
            curr_move[0] = 0;
        }
    }

    if (curr_move[2] && curr_move[3]) {
        if (last_move[2]) {
            shape.move(0, -speed);
            curr_move[3] = 0;
        }
        else {
            shape.move(0, speed);
            curr_move[2] = 0;
        }
    }

    for (int i = 0; i < 4; i++) {
        last_move[i] = curr_move[i];
    }
}

void track(sf::Sprite& hunter, const sf::Sprite& prey, const float speed) {


    if (prey.getPosition() != hunter.getPosition()) {

        //gets direction from tracker to prey
        sf::Vector2f unit_direction = normal_direction(hunter, prey);

        //moves tracker in the direction of prey at 0.01 times 1
        hunter.move(unit_direction * 0.01f * speed);

    }
}

void center_origin(sf::Sprite& shape) {
    shape.setOrigin(shape.getLocalBounds().getSize() / 2.0f);
}

void fire_bullet(const sf::Sprite& gunman, sf::Sprite& target, std::vector<bullet>& bullets, const sf::RenderWindow& window) {
    
  
  
    //shape set position to mouse
    static int reload_time = 0, bleed_time = -1;
    static sf::Color og_color;
    sf::Sprite mouse_pos;
    mouse_pos.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && reload_time == 0) {
        
        sf::SoundBuffer *bulletBuffer = new sf::SoundBuffer; 
        sf::Sound* bulletSound = new sf::Sound;
        if (bulletBuffer->loadFromFile("CS122_PA9/bulletSound.wav"))
        {
            bulletSound->setBuffer(*bulletBuffer);
            bulletSound->play();
        }
        //creates new bullet
        bullets.push_back(bullet());
        //points bullet towards mouse position
        bullets[bullets.size() - 1].lock_on(gunman, mouse_pos);
        //sets bullet slightly in front of gunman
        bullets[bullets.size() - 1].set_position(gunman.getPosition());
        //starts reload timer (how long it takes for another bullet to be fired)
        reload_time = 1000;
       
    }

    //loops through each current bullet, moves each tiny amount
    for (size_t index = 0; index < bullets.size(); index++) {

        //moves bullet 0.3 pixel lengths
        bullets[index].move(0.3f);

        //if bullet touches window or target
        if (touching_hitbox(bullets[index].get_sprite(), target) || hit_window(bullets[index].get_sprite())) {

            //erases bullet
            bullets.erase(bullets.begin() + index);
        }

    }

    if (reload_time != 0) reload_time--;
    if (bleed_time != 0) bleed_time--;
}

int menu()
{
    bool option;
    int selection = 0;
    while (selection != 1 && selection != 5)
    {
        system("cls");
        cout << "WELCOME TO [INSERT NAME OF GAME]!!" << endl;
        cout << "Please choose from the following options:\n" << endl;
        cout << "1. Play game" << endl;
        cout << "2. How to play" << endl;
        cout << "3. Items" << endl;
        cout << "4. Credits" << endl;
        cout << "5. Exit" << endl;
        cin >> selection;

        switch (selection)
        {
        case 1:
            system("cls");
            return true;
            break;
        case 2:
            system("cls");
            cout << "How to play:\n" << endl;
            cout << "Movement: Use WASD to move!" << endl;
            cout << "Shooting: Use your mouse or trackpad to aim and press the spacebar to shoot!" << endl;
            cout << "Items: there are items in the game that will affect your gameplay, see the items section for a description of all the items! \n" << endl;
            system("PAUSE");
            break;
        case 3:
            system("cls");
            cout << "Items:\n" << endl;
            cout << "Items are icon sprites that float across the screen and are collected by a player. Each item has a different effect on the player and/or the game.\n\n" << endl;
            cout << "Power-Ups:\n" << endl;
            cout << "Speed Boost - Increases player's speed\nGun Upgrade - Increasees player's fire rate\nShield - Protects player\nBullet Spray - Launches bullets in every direction\n\n" << endl;
            cout << "Power-Downs:\n" << endl;
            cout << "Speed Drop - Decreases player's speed\nGun Downgrade - Decreases player's fire rate\nConfusion - Decreases player's fire accuracy\n\n" << endl;
            cout << "Miscellaneous:\n\n" << endl;
            cout << "Bomb - Bomb appears randomly on map and explodes\nMystery - Random item" << endl;
            system("PAUSE");
            break;

        case 4:
            system("cls");
            cout << "Credits:\n" << endl;
            cout << "Creators: Eli Lawrence, Jon B., Kyle Ortega-Gammill, Omar Herrera-Rea" << endl;
            system("PAUSE");
            break;

        case 5:
            system("cls");
            cout << "Thanks for playing!" << endl;
            return false;
            break;
        }

    }
}
