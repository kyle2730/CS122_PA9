#pragma once

#include "player_header.hpp"
#include "item_header.hpp"
#include "extra_header.hpp"

//andy class and attributes
class andy_man {

private:

    sf::Sprite body;
    sf::Texture normal_face;
    sf::Texture evil_face;
    sf::RectangleShape text_box;
    sf::Text warning;
    sf::Font text_font;
    time_t start_time;

    sf::SoundBuffer buffer;
    sf::Sound soundEffect;

public:

    void sound_base(const std::string file);

    andy_man();

    void draw_andy(sf::RenderWindow& window);

    bool andys_coming(player& user);
};