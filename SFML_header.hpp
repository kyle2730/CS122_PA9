#pragma once

#include <SFML/Graphics.hpp>
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
    sf::RectangleShape casing;
    sf::Vector2f direction;
public:
    //constructor
    bullet();

    //setters
    void lock_on(const sf::Shape& origin, const sf::Shape& target);
    void set_position(const sf::Vector2f& position);

    //getter
    sf::RectangleShape& get_casing();

    void chase(const float speed);

    //destructor
    ~bullet();
};

class player {

public:
    

};

//VECTOR FUNCTIONS
void normalize_vector(sf::Vector2f& unnormalized_vec);
sf::Vector2f full_direction(const sf::Shape& origin, const sf::Shape& target);
sf::Vector2f normal_direction(const sf::Shape& origin, const sf::Shape& target);
float vector_to_degrees(const sf::Vector2f& vec);
float magnitude(const sf::Vector2f& vec);

//POSITION FUNCTIONS
int hit_window(const sf::Shape& shape, const float buffer = 0, const sf::FloatRect& boundary = sf::FloatRect(0, 0, WINDOW_W, WINDOW_H));
bool touching_hitbox(const sf::Shape& sprite1, const sf::Shape& sprite2);
bool touching_hitdisc(const sf::CircleShape& sprite1, const sf::CircleShape& sprite2);

//MOVE FUNCTIONS
void key_move(sf::Shape& shape, const float user_speed, std::string input = "arrow", const sf::FloatRect& boundary = sf::FloatRect(0, 0, WINDOW_W, WINDOW_H));
void track(sf::Shape& hunter, const sf::Shape& prey, const float speed);

void center_origin(sf::Shape& shape);

void fire_bullet(const sf::Shape& gunman, sf::Shape& target, std::vector<bullet>& bullets, const sf::RenderWindow& window);
