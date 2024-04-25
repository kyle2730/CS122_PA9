#include "player_header.hpp"
#include "extra_header.hpp"
#include "item_header.hpp"

//BASE CLASS ITEM FUNCTIONS

//constructors
item::item() {
    collected = 0;
    float_time = 0;
    speed = 0;
}
item::item(const std::string& file_name) {

	if (!image.loadFromFile(file_name)) {
		//error checking
	}
	sprite.setTexture(image, true);
    if (rand() % 2) {
        sprite.setPosition(sf::Vector2f(rand() % WINDOW_W, (rand() % 2) * WINDOW_H));
    }
    else {
        sprite.setPosition(sf::Vector2f((rand() % 2) * WINDOW_W, rand() % WINDOW_H));
    }
    center_origin(sprite);

	speed = 0;
    float_time = 15000;
    collected = false;
}

//setters
void item::set_speed(const float new_speed) {
    speed = new_speed;
}
void item::random_direction() {
    int angle = rand() % 360;
    sf::Vector2f temp = degrees_to_vector(angle);
    normalize_vector(temp);
    direction = temp;
}
void item::flip_direction(const char wall) {
    if (wall == 'V') direction.y *= -1;
    else if (wall == 'H') direction.x *= -1;
}
void item::float_timer() {
    float_time--;
}

//getters
bool item::is_collected() {
    return collected;
}
int item::get_float_time() {
    return float_time;
}
sf::Sprite& item::get_sprite() {
	return sprite;
}

//moves item or runs collected animation
void item::move() {
    if (!is_collected())
    sprite.move(direction * speed);
    else {
        sprite.scale(sf::Vector2f(0.99, 0.99));
    }
}
//draws item on to window
void item::draw_item(sf::RenderWindow& window) {
	window.draw(sprite);
}
//runs hit function and adjusts variables
void item::got_collected(player& user) {
    collected = true;
    float_time = 15000;
    hit(user);
}
//sets sound of item to specified file
void item::sound_base(const std::string file)
{

    if (buffer.loadFromFile(file))
    {
        soundEffect.setBuffer(buffer);
        soundEffect.play();
    }
}

//destructor
item::~item() {}

//DERIVED CLASS FUNCTIONS

//hit functions
void heart::hit(player& user) {
    set_sound();
    user.add_lives(1);
}
void speed_boost::hit(player& user) {
    set_sound();
    user.speed_up();
}
void gun_upgrade::hit(player& user) {
    set_sound();
    user.gun_up();
}
void shield::hit(player& user) {
    set_sound();
    user.add_lives(1000);
}
void bullet_spray::hit(player& user) {
    set_sound();
    user.spray();
}
void speed_drop::hit(player& user) {
    set_sound();
    user.speed_down();
}
void gun_downgrade::hit(player& user) {
    set_sound();
    user.gun_down();
}
void confusion::hit(player& user) {
    set_sound();
    user.drop_accuracy();   
}
void bomb::hit(player& user) {}

//set sound functions
void heart::set_sound()
{
    sound_base("CS122_PA9/upgradeSound.wav");
}
void speed_boost::set_sound()
{
    sound_base("CS122_PA9/upgradeSound.wav");
}
void gun_upgrade::set_sound()
{
    sound_base("CS122_PA9/upgradeSound.wav");
}
void shield::set_sound()
{
    sound_base("CS122_PA9/upgradeSound.wav");
}
void bullet_spray::set_sound()
{
    sound_base("CS122_PA9/bulletSpraySound.wav");
}
void speed_drop::set_sound()
{
    sound_base("CS122_PA9/downgradeSound.wav");
}
void gun_downgrade::set_sound()
{
    sound_base("CS122_PA9/downgradeSound.wav");
}
void confusion::set_sound()
{
    sound_base("CS122_PA9/confusionSound.wav");
}
void bomb::set_sound()
{
    sound_base("CS122_PA9/bombSound.wav");

}

//reset functions
void heart::reset_player(player& user) {}
void speed_boost::reset_player(player& user) {
    user.speed_down();
}
void gun_upgrade::reset_player(player& user) {
    user.gun_down();
}
void shield::reset_player(player& user) {
    user.add_lives(-1000);
}
void bullet_spray::reset_player(player& user) {}
void speed_drop::reset_player(player& user) {
    user.speed_up();
}
void gun_downgrade::reset_player(player& user) {
    user.gun_up();
}
void confusion::reset_player(player& user) {
    user.raise_accuracy();
}
void bomb::reset_player(player& user) {
    float distance = magnitude(user.get_sprite().getPosition() - sprite.getPosition());
    if (distance < 300) {
        user.add_lives((int)distance / 100 - 3);
    }
}

//overridden functions for special items
void shield::got_collected(player& user) {
    collected = true;
    float_time = 10000;
    hit(user);
}
void bullet_spray::got_collected(player& user) {
    collected = true;
    float_time = 15000;
    hit(user);
}
void bomb::move() {

    float multiplier = -0.001;
    if ((float_time % 2000) < 1000) multiplier = 0.001;

    if (!is_collected())
        sprite.move(direction * speed);
    else {
        sprite.scale(sf::Vector2f(1.0f + multiplier, 1.0f + multiplier));

        if (float_time == 1500) {

            if (!image.loadFromFile("CS122_PA9/explosion.png")) {
                //error checking
            }
            sprite.setTexture(image, true);
            center_origin(sprite);
            set_sound();
        }
    }
}

/*

sf::SoundBuffer* bulletBuffer = new sf::SoundBuffer;
    sf::Sound* bulletSound = new sf::Sound;
    if (bulletBuffer->loadFromFile("CS122_PA9/bulletSound.wav"))
    {
        bulletSound->setBuffer(*bulletBuffer);
        bulletSound->play();

*/