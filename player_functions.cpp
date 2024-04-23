#include "player_header.hpp"
#include "extra_header.hpp"
#include "item_header.hpp";

//-----------------BULLETS--------------------------

//constructor
bullet::bullet() {
    image = new sf::Texture;
    image->loadFromFile("CS122_PA9/bullet.png");
    sprite.setTexture(*image);
    direction = sf::Vector2f(0, 0);
    center_origin(sprite);

    sound = NULL;
    soundFile = NULL;
}
//points bullet at target
void bullet::lock_on(const sf::Sprite& origin, const sf::Sprite& target, int accuracy) {
    sf::Sprite temp(origin);
    if (accuracy < 1) temp.setPosition(sf::Vector2f(rand() % WINDOW_W, rand() % WINDOW_H));
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
//moves bullet in direction of target
void bullet::move(const float speed) {
    sprite.move(direction * speed);
}
//destructor
bullet::~bullet() {

}


//-------------------STAT BAR--------------------------------

//constructor
stat_bar::stat_bar() {

    text_font = new sf::Font();
    if (!text_font->loadFromFile("CS122_PA9/Pixellari.ttf")) {
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
    stats.setFont(*text_font);
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
stat_bar::~stat_bar() {
    delete text_font;
}


//----------------------PLAYER----------------------------------

player::player(const std::string& new_name) {
    lives = 3;
    speed = 3;
    fire_rate = 3;
    accuracy = 1;

    name = new_name;
    image = new sf::Texture;
    image->loadFromFile("CS122_PA9/woody.png");
    sprite.setTexture(*image);
    center_origin(sprite);
    sprite.setPosition(sf::Vector2f(WINDOW_W / 2.0f, WINDOW_H / 2.0f));
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

//getters
int player::get_accuracy() {
    return accuracy;
}
int player::get_fire_rate() {
    return fire_rate;
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

void player::draw_player(sf::RenderWindow& window) {
    window.draw(sprite);
    data.update_stats(lives, speed, fire_rate);
    data.draw_bar(window); //stats = speed, hearts, fire_rate
}
void player::spray(std::vector<bullet>& bullets) {
    //shape set position to mouse
    int degrees;
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
        //creates new bullet
        bullets.push_back(bullet());
        //points bullet towards mouse position
        bullets[bullets.size() - 1].lock_on(sprite, position, 1);
        //sets bullet slightly in front of gunman
        bullets[bullets.size() - 1].set_position(sprite.getPosition());
    }
}

player::~player() {
    delete image;
}
