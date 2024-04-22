#pragma once

#include "player_header.hpp"
#include "item_header.hpp"
#include "andy_header.hpp";

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
void center_origin(sf::Sprite& shape);

//MOTION FUNCTIONS
void key_move(player& user, const sf::FloatRect& boundary = sf::FloatRect(0, 0, WINDOW_W, WINDOW_H));
void track(sf::Sprite& hunter, const sf::Sprite& prey, const float speed);
void fire_bullet(player& gunman, player& target, std::vector<bullet>& bullets, const sf::RenderWindow& window);

int menu();
bool player_death(player& user);

std::string int_to_str(int num);

void new_item(std::vector<item*>& items, bool andy);
item* random_item();
void item_float(std::vector<item*>& items, player& user, sf::RenderWindow& window, bool andy);
void item_triggered(std::vector<item*>& items, player& user, std::vector<bullet>& bullets, bool andy);
