#pragma once

#include "player_header.hpp"
#include "item_header.hpp"

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
void fire_bullet(player& gunman, player& target, const sf::RenderWindow& window, const std::string control = "mouse");
bool control_event(const std::string control);
void auto_move(player& robot, player& human);

int menu();
int testCases();
bool player_death(player& user);
bool recieve_message();
bool send_message(const char string[], sf::TcpSocket& socket);

std::string int_to_str(int num);
bool isPressed(char alpha);


void new_item(std::vector<item*>& items);
item* random_item();
void item_float(std::vector<item*>& items, player& user, sf::RenderWindow& window);
void item_triggered(std::vector<item*>& items, player& user);

template <class T>
void delete_vector(std::vector<T*>& items) {
    while (!items.empty()) {
        delete items[0];
        items[0] = NULL;
        items.erase(items.begin());
    }
}


int testCases();