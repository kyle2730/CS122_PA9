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

class player {
private:
    sf::Sprite sprite;
    sf::Texture* image;
public:
    //constructor
    player();

    sf::Sprite& get_sprite();

    //destructor
    ~player();

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

//MOVE FUNCTIONS
void key_move(sf::Sprite& shape, const float user_speed, const sf::FloatRect& boundary = sf::FloatRect(0, 0, WINDOW_W, WINDOW_H));
void track(sf::Sprite& hunter, const sf::Sprite& prey, const float speed);

void center_origin(sf::Sprite& shape);

void fire_bullet(const sf::Sprite& gunman, sf::Sprite& target, std::vector<bullet>& bullets, const sf::RenderWindow& window);

int menu();