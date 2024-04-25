#pragma once

#include "player_header.hpp"
#include "item_header.hpp"
#include "extra_header.hpp"

//ANDY CLASS
class andy_man {

private:

    //data members

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

    //member functions

    //plays sound effect from file
    void sound_base(const std::string file);

    //constructor
    andy_man();

    //draws andy
    void draw_andy(sf::RenderWindow& window);

    //runs andy mechanic, returns 1 if andy is HERE, 0 if he is not
    bool andys_coming(player& user);
};