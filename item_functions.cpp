#include "SFML_header.hpp"
#include "item.hpp";

item::item() {
    image = NULL;
    speed = 0;
}
item::item(const std::string& file_name) {
    image = new sf::Texture;

	if (!image->loadFromFile(file_name)) {
		//error checking
	}
	sprite.setTexture(*image);

	speed = 0;
}

void item::draw_sprite(sf::RenderWindow& window) {
	window.draw(sprite);
}

sf::Sprite& item::get_sprite() {
	return sprite;
}

void trigger_item(std::vector<item>& items) {
    static int random_timer = 1000;
    item* new_item;

    if (!random_timer) {
        new_item = random_item();
        items.push_back(*new_item);
        random_timer = (rand() % 1000) + 1000;
    }
    else random_timer--;
}

item* random_item() {
    int rand_int = rand() % 10;
    switch (rand_int) {

    case 0: return new heart();
    case 1: return new speed_boost;
    case 2: return new gun_upgrade;
    case 3: return new shield;
    case 4: return new bullet_spray;
    case 5: return new speed_drop;
    case 6: return new gun_downgrade;
    case 7: return new confusion;
    case 8: return new bomb;
    case 9: return new mystery();
    }
}