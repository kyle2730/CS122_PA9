#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <conio.h>
#include <iostream>
#include <thread>
#include <math.h>

#define WINDOW_W 1000
#define WINDOW_H 800
#define PI 3.14159265359

using std::cout;
using std::cin;
using std::endl;


class bullet {

private:
    sf::Sprite sprite;
    sf::Texture* image;
    sf::Vector2f direction;
    sf::SoundBuffer* soundFile;
    sf::Sound* sound;

public:
    //constructor
    bullet();

    //setters
    void lock_on(const sf::Sprite& origin, const sf::Sprite& target);
    void set_position(const sf::Vector2f& position);

    //getter
    sf::Sprite& get_sprite();

    void move(const float speed);

    //destructor
    ~bullet();
};

class stat_bar {
private:
    sf::RectangleShape text_box;
    sf::Text stats;
    sf::Font* text_font;

public:
    stat_bar();
    void draw_bar(sf::RenderWindow& window);
    void update_stats(int lives, int speed, int fire_rate);
};

class player {
private:
    sf::Sprite sprite;
    sf::Texture* image;
    stat_bar data;

    int lives;
    int speed;
    int fire_rate;

public:
    //constructor
    player();

    //setters
    void add_heart();
    void lose_heart();
    void speed_up();
    void speed_down();
    void gun_up();
    void gun_down();

    //getters
    int get_fire_rate();
    int get_speed();
    sf::Sprite& get_sprite();

    void draw_player(sf::RenderWindow& window);

    //destructor
    ~player();

    friend class stat_bar;

};

//VECTOR FUNCTIONS
void normalize_vector(sf::Vector2f& unnormalized_vec);
sf::Vector2f full_direction(const sf::Sprite& origin, const sf::Sprite& target);
sf::Vector2f normal_direction(const sf::Sprite& origin, const sf::Sprite& target);
float vector_to_degrees(const sf::Vector2f& vec);
sf::Vector2f degrees_to_vector(float degrees);
float magnitude(const sf::Vector2f& vec);

//POSITION FUNCTIONS
int hit_window(const sf::Sprite& shape, const float buffer = 0, const sf::FloatRect& boundary = sf::FloatRect(0, 0, WINDOW_W, WINDOW_H));
bool touching_hitbox(const sf::Sprite& sprite1, const sf::Sprite& sprite2);
bool touching_hitdisc(const sf::CircleShape& sprite1, const sf::CircleShape& sprite2);
void center_origin(sf::Sprite& shape);

//MOVE FUNCTIONS
void key_move(player& user, const sf::FloatRect& boundary = sf::FloatRect(0, 0, WINDOW_W, WINDOW_H));
void track(sf::Sprite& hunter, const sf::Sprite& prey, const float speed);

void fire_bullet(player& gunman, player& target, std::vector<bullet>& bullets, const sf::RenderWindow& window);

int menu();

std::string int_to_str(int num);