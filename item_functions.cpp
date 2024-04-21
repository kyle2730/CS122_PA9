#include "SFML_header.hpp"
#include "item.hpp";

//ITEM FUNCTIONS

item::item(const std::string& file_name) {
    image = new sf::Texture;

	if (!image->loadFromFile(file_name)) {
		//error checking
	}
	sprite.setTexture(*image);
    sprite.setPosition(sf::Vector2f(WINDOW_W / 2, WINDOW_H / 2));
    center_origin(sprite);

	speed = 0;
    float_time = 15000;
}

void item::set_speed(const float new_speed) {
    speed = new_speed;
}

int item::get_float_time() {
    return float_time;
}

sf::Sprite& item::get_sprite() {
	return sprite;
}

void item::flip_direction(const char wall) {
    if (wall == 'V') direction.y *= -1;
    else if (wall == 'H') direction.x *= -1;
}

void item::float_timer() {
    float_time--;
}

void item::random_direction() {
    sf::Vector2f temp = degrees_to_vector(rand() % 360);
    normalize_vector(temp);
    direction = temp;
}

void item::move() {
    sprite.move(direction * speed);
}

void item::draw_sprite(sf::RenderWindow& window) {
	window.draw(sprite);
}



void trigger_item(std::vector<item>& items) {
    static int random_timer = 5000;
    item* new_item;

    if (!random_timer) {
        new_item = random_item();
        new_item->set_speed(0.2f);
        new_item->random_direction();
        items.push_back(*new_item);
        random_timer = (rand() % 1000) + 4000;
    }
    else random_timer--;
}

item* random_item() {
    int rand_int = rand() % 10;
    switch (rand_int) {

    case 0: return new heart("CS122_PA9/heart.png");
    case 1: return new speed_boost("CS122_PA9/forwardArrows.png");
    case 2: return new gun_upgrade("CS122_PA9/ak47.png");
    case 3: return new shield("CS122_PA9/shield.png");
    case 4: return new bullet_spray("CS122_PA9/sun.png");
    case 5: return new speed_drop("CS122_PA9/backwardsArrows.png");
    case 6: return new gun_downgrade("CS122_PA9/gun.png");
    case 7: return new confusion("CS122_PA9/beer.png");
    case 8: return new bomb("CS122_PA9/bomb.png");
    case 9: return new mystery("CS122_PA9/mystery.png");
    }

    return NULL;
}

void item_float(std::vector<item>& items, sf::Sprite& user, sf::RenderWindow& window) {

    //shape set position to mouse
    static int reload_time = 0;
    int wall = 0;

    //loops through each current bullet, moves each tiny amount
    for (size_t index = 0; index < items.size(); index++) {

        items[index].float_timer();

        //moves bullet 0.3 pixel lengths
        items[index].move();

        //if item touches window border, direction flips
        wall = hit_window(items[index].get_sprite());
        if ((wall % 2) || ((wall >> 1) % 2))
            items[index].flip_direction('H');
        else if (((wall >> 2) % 2) || ((wall >> 3) % 2))
            items[index].flip_direction('V');

        //if item touches hitbox OR item's timer runs out, item disappears
        if (touching_hitbox(items[index].get_sprite(), user) || items[index].get_float_time() == 0) {
            //erases bullet
            items.erase(items.begin() + index);
            //items[index].hit(player);
        }

    }

    if (reload_time != 0) reload_time--;

}