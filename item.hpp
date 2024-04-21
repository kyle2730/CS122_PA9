#pragma once
#include "SFML_header.hpp"

class item
{
public:
	item();
	item(const std::string& file_name);

	void set_speed(const float new_speed);

	int get_float_time();

	void flip_direction(const char wall);
	void float_timer();
	void random_direction();

	void move();
	void hit(); //function when player hits item, different for each item
	void draw_sprite(sf::RenderWindow& window); //draws the graphics for the item

	sf::Sprite& get_sprite();

private:

	sf::Sprite sprite;
	sf::Vector2f direction;
	sf::Texture* image;
	float speed;
	int float_time;
};

class heart : public item {
public:
	heart(const std::string& file_name) : item(file_name){}
};

class speed_boost : public item {
public:
	speed_boost(const std::string& file_name) : item(file_name) {}
};

class gun_upgrade : public item {
public:
	gun_upgrade(const std::string& file_name) : item(file_name) {}
};

class shield : public item {
public:
	shield(const std::string& file_name) : item(file_name) {}
};

class bullet_spray : public item {
public:
	bullet_spray(const std::string& file_name) : item(file_name) {}
};

class speed_drop : public item {
public:
	speed_drop(const std::string& file_name) : item(file_name) {}
};

class gun_downgrade : public item {
public:
	gun_downgrade(const std::string& file_name) : item(file_name) {}
};
class confusion : public item {
public:
	confusion(const std::string& file_name) : item(file_name) {}
};

class bomb : public item {
public:
	bomb(const std::string& file_name) : item(file_name) {}
};

class mystery : public item {
public:
	mystery(const std::string& file_name) : item(file_name) {}
};

void trigger_item(std::vector<item>& items);
item* random_item();
void item_float(std::vector<item>& items, sf::Sprite& user, sf::RenderWindow& window);
