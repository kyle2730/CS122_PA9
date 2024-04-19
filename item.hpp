#pragma once
#include "SFML_header.hpp"

class item
{
public:
	item();
	item(const std::string& file_name);

	void hit(); //function when player hits item, different for each item
	void draw_sprite(sf::RenderWindow& window); //draws the graphics for the item

	sf::Sprite& get_sprite();

private:

	sf::Sprite sprite;
	sf::Vector2f direction;
	sf::Texture* image;
	float speed; 
};

class heart : public item {
public:
	//void hit();
};
class speed_boost : public item {
public:
	//void hit();
};
class gun_upgrade : public item {
public:
	//void hit();
};
class shield : public item {
public:
	//void hit();
};
class bullet_spray : public item {
public:
	//void hit();
};
class speed_drop : public item {
public:
	//void hit();
};
class gun_downgrade : public item {
public:
	//void hit();
};
class confusion : public item {
public:
	//void hit();
};
class bomb : public item {
public:
	//void hit();
};
class mystery : public item {
public:
	//void hit();
};

void trigger_item(std::vector<item>& items);

item* random_item();