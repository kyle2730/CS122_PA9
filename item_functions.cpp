#include "SFML_header.hpp"
#include "item.hpp"

item::item(const std::string& file_name) {

	image.loadFromFile(file_name);
	sprite.setTexture(image);

	speed = 0;
}