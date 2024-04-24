#include "player_header.hpp"
#include "extra_header.hpp"
#include "item_header.hpp"

//-----------------BULLETS--------------------------

//constructor
bullet::bullet() {
    direction = sf::Vector2f(0, 0);
    center_origin(sprite);
    fire_time = time(NULL);
    active = true;
}
//points bullet at target
void bullet::lock_on(const sf::Sprite& origin, const sf::Sprite& target, int accuracy) {
    sf::Sprite temp(origin);
    if (accuracy < 1) temp.setPosition(sf::Vector2f((float)(rand() % WINDOW_W), (float)(rand() % WINDOW_H)));
    direction = normal_direction(temp, target);
    sprite.setRotation(vector_to_degrees(direction) + 180);
}
//sets position of bullet
void bullet::set_position(const sf::Vector2f& position) {
    sprite.setPosition(position + 15.0f * direction);
}
//return bullet sprite
sf::Sprite& bullet::get_sprite() {
    return sprite;
}
time_t bullet::get_fire_time() {
    return fire_time;
}
bool bullet::is_active() {
    return active;
}

//moves bullet in direction of target
void bullet::move(const float speed) {
    sprite.move(direction * speed);
}

void bullet::hit() {
    sprite.scale(sf::Vector2f(0, 0));
    active = false;
}

bool bullet::past_sound_time() {
    if (time(NULL) > fire_time + 2)
        return true;
    else return false;
}

void bullet::set_sound() {
    if (soundFile.loadFromFile("CS122_PA9/bulletSound.wav"))
    {
        sound.setBuffer(soundFile);
        sound.play();
    }
}

void bullet::set_image() {
    image.loadFromFile("CS122_PA9/bullet.png");
    sprite.setTexture(image);
}

//destructor
bullet::~bullet() {

}


//-------------------STAT BAR--------------------------------

//constructor
stat_bar::stat_bar() {

    if (!text_font.loadFromFile("CS122_PA9/Pixellari.ttf")) {
        //error
    }

    text_box.setPosition(sf::Vector2f(5, 5));
    text_box.setFillColor(sf::Color::White);
    text_box.setOutlineColor(sf::Color::Red);
    text_box.setOutlineThickness(2);

    stats.setString("Hearts: 3\nSpeed: 1\nFire Rate: 1");
    stats.setFillColor(sf::Color::Black);
    stats.setPosition(sf::Vector2f(10, 10));
    stats.setCharacterSize(25);
    stats.setFont(text_font);
}
void stat_bar::draw_bar(sf::RenderWindow& window) {
    window.draw(text_box);
    window.draw(stats);
}
void stat_bar::update_stats(int lives, int speed, int fire_rate) {
    std::string update = "Hearts: ";
    text_box.setSize(sf::Vector2f(150, 100));
    if (lives / 1000) {
        update.append(int_to_str(lives % 1000));
        update.append("\n  SHIELD");
        text_box.setSize(sf::Vector2f(150, 130));
    }
    else update.append(int_to_str(lives));
    update.append("\nSpeed: ");

    update.append(int_to_str(speed));
    update.append("\nFire Rate: ");
    update.append(int_to_str(fire_rate));
    stats.setString(update);
}
stat_bar::~stat_bar() {}


//----------------------PLAYER----------------------------------

player::player(const std::string& new_name) {
    
    speed = 3;
    accuracy = 1;
    fire_timer = 0;

    name = new_name;
    if (new_name == "Woody") {
        image.loadFromFile("CS122_PA9/woody.png");
        sprite.setPosition(sf::Vector2f(2 * WINDOW_W / 3.0f, WINDOW_H / 2.0f));
        fire_rate = 3;
        lives = 3;
    }
    else if (new_name == "Buzz") {
        image.loadFromFile("CS122_PA9/buzz.png");
        sprite.setPosition(sf::Vector2f(WINDOW_W / 3.0f, WINDOW_H / 2.0f));
        fire_rate = 1;
        lives = 10;
    }
    else {
        fire_rate = 0;
        lives = 0;
    }
    sprite.setTexture(image);
    center_origin(sprite);
}

void player::sound_base(const std::string file)
{
    if (buffer.loadFromFile(file))
    {
        soundEffect.setBuffer(buffer);
        soundEffect.play();
    }
}

//setters
void player::add_lives(int extra) {
    if (lives < 1000 || extra <= -1000 || extra > 0)
        lives += extra;

    if (extra < 0)
    {
        sound_base("CS122_PA9/owSound.wav");
    }
}
void player::speed_up() {
    speed++;
}
void player::speed_down() {
    speed--;
}
void player::gun_up() {
    fire_rate++;
}
void player::gun_down() {
    fire_rate--;
}
void player::drop_accuracy() {
    accuracy--;
}
void player::raise_accuracy() {
    accuracy++;
}
void player::set_fire_timer(int new_timer) {
    fire_timer = new_timer;
}

//getters
int player::get_accuracy() {
    return accuracy;
}
int player::get_fire_rate() {
    return fire_rate;
}
int player::get_fire_timer() {
    return fire_timer;
}
int player::get_speed() {
    return speed;
}
int player::get_lives() {
    return lives;
}
sf::Sprite& player::get_sprite() {
    return sprite;
}
std::string player::get_name() {
    return name;
}
std::vector<bullet*>& player::get_bullets() {
    return bullets;
}

void player::load_gun(sf::Sprite& target) {

    bullets.push_back(new bullet);
    //points bullet towards mouse position
    bullets[bullets.size() - 1]->lock_on(sprite, target, accuracy);
    //sets bullet slightly in front of gunman
    bullets[bullets.size() - 1]->set_position(sprite.getPosition());

    bullets[bullets.size() - 1]->set_sound();

    bullets[bullets.size() - 1]->set_image();
}
void player::fire_gun(player& target) {

    for (size_t index = 0; index < bullets.size(); index++) {

        //moves bullet 0.3 pixel lengths
        bullets[index]->move(0.3f);

        //if bullet touches window or target
        if (touching_hitbox(bullets[index]->get_sprite(), target.get_sprite()) && bullets[index]->is_active()) {
            bullets[index]->hit();
            target.add_lives(-1);
        }

        if (bullets[index]->past_sound_time() && !bullets[index]->is_active()) {
            //erases bullet
            delete bullets[index];
            bullets[index] = NULL;
            bullets.erase(bullets.begin() + index);
            index--;
        }

    }
}
bool player::isGunLoaded() {
    if (bullets.empty()) return false;
    else if (touching_hitbox(bullets[bullets.size() - 1]->get_sprite(), sprite)) return true;
    else return false;
}

void player::draw_player(sf::RenderWindow& window) {
    window.draw(sprite);
    data.update_stats(lives, speed, fire_rate);
    data.draw_bar(window); //stats = speed, hearts, fire_rate

    for (size_t index = 0; index < bullets.size(); index++) {
        window.draw(bullets[index]->get_sprite());
    }

}
void player::spray() {
    //shape set position to mouse
    sf::Sprite position;
    sf::Vector2f direction;

    sf::SoundBuffer* bulletBuffer = new sf::SoundBuffer;
    sf::Sound* bulletSound = new sf::Sound;
    if (bulletBuffer->loadFromFile("CS122_PA9/bulletSound.wav"))
    {
        bulletSound->setBuffer(*bulletBuffer);
        bulletSound->play();
    }
    
    for (int i = 0; i < 18; i++) {
        direction = degrees_to_vector(i * 20);
        position.setPosition(sprite.getPosition());
        position.move(direction);
        load_gun(position);
    }
}

player::~player() {
    delete_vector(bullets);
}
