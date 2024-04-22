#include "player_header.hpp"
#include "extra_header.hpp"
#include "item_header.hpp";

//ITEM FUNCTIONS

//constructors
item::item() {
    collected = 0;
    float_time = 0;
    speed = 0;
    image = NULL;
}
item::item(const std::string& file_name) {
    image = new sf::Texture;

	if (!image->loadFromFile(file_name)) {
		//error checking
	}
	sprite.setTexture(*image, true);
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
void item::got_collected(player& user, std::vector<bullet>& bullets) {
    collected = true;
    float_time = 15000;
    hit(user);
}

//destructor
item::~item() {}

//hit functions
void heart::hit(player& user) {
    user.add_lives(1);
}
void speed_boost::hit(player& user) {
    user.speed_up();
}
void gun_upgrade::hit(player& user) {
    user.gun_up();
}
void shield::hit(player& user) {
    user.add_lives(1000);
}
void bullet_spray::hit(player& user, std::vector<bullet>& bullets) {
    user.spray(bullets);
}
void bullet_spray::hit(player& user){}
void speed_drop::hit(player& user) {
    user.speed_down();
}
void gun_downgrade::hit(player& user) {
    user.gun_down();
}
void confusion::hit(player& user) {
    user.drop_accuracy();
}
void bomb::hit(player& user) {}

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
void bullet_spray::got_collected(player& user, std::vector<bullet>& bullets) {
    collected = true;
    float_time = 15000;
    hit(user, bullets);
}
void bomb::move() {

    float multiplier = -0.001;
    if ((float_time % 2000) < 1000) multiplier = 0.001;

    if (!is_collected())
        sprite.move(direction * speed);
    else {
        sprite.scale(sf::Vector2f(1.0f + multiplier, 1.0f + multiplier));

        if (float_time == 1500) {

            if (!image->loadFromFile("CS122_PA9/explosion.png")) {
                //error checking
            }
            sprite.setTexture(*image, true);
            center_origin(sprite);
        }
    }
}