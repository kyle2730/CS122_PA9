#pragma once
#include "SFML_header.hpp"

class Item
{
public:

	Item();

	void virtual hits(); //function when player hits item, different for each item
	void virtual draw(); //draws the graphics for the item

private:
	sf::RectangleShape casing;
	sf::Vector2f direction;
	int speed; 
};
