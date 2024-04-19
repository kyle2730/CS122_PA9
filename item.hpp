#pragma once
#include "SFML_header.hpp"

class item
{
public:

	item();
	item(const std::string& file_name);

	void hit(); //function when player hits item, different for each item
	void draw(); //draws the graphics for the item

private:
	sf::Sprite sprite;
	sf::Vector2f direction;
	sf::Texture image;
	float speed; 
};


class TimedItems : public item {
	
private:
	float time;


};

class PowerDown : public item {
	void hit();
};