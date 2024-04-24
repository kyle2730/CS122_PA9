#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <thread>
#include <math.h>
#include <string>
#include <string.h>

#define WINDOW_W 1000
#define WINDOW_H 800
#define PI 3.14

using std::cout;
using std::cin;
using std::endl;

class stat_bar {
private:
    sf::RectangleShape text_box;
    sf::Text stats;
    sf::Font text_font;

public:
    stat_bar();
    void draw_bar(sf::RenderWindow& window);
    void update_stats(int lives, int speed, int fire_rate);
    ~stat_bar();
};

class bullet {

private:
    sf::Sprite sprite;
    sf::Texture image;
    sf::Vector2f direction;
    sf::SoundBuffer soundFile;
    sf::Sound sound;
    time_t fire_time;
    bool active;

public:
    //constructor
    bullet();

    //setters
    void lock_on(const sf::Sprite& origin, const sf::Sprite& target, int accuracy);
    void set_position(const sf::Vector2f& position);

    //getter
    sf::Sprite& get_sprite();
    time_t get_fire_time();
    bool is_active();

    void move(const float speed);

    void hit();
    bool past_sound_time();
    void set_sound();
    void set_image();
    //destructor
    ~bullet();
};

class player {
private:
    sf::Sprite sprite;
    sf::Texture image;
    stat_bar data;
    std::string name;

    int lives;
    int speed;
    int fire_rate;
    int fire_timer;
    int accuracy;

    std::vector<bullet*> bullets;

    sf::SoundBuffer buffer;
    sf::Sound soundEffect;

public:
    //constructor
    player(const std::string& new_name);

    //setters
    void add_lives(int extra);
    void speed_up();
    void speed_down();
    void gun_up();
    void gun_down();
    void drop_accuracy();
    void raise_accuracy();
    void set_fire_timer(int new_timer);
    void sound_base(const std::string file);

    //getters
    int get_accuracy();
    int get_fire_rate();
    int get_fire_timer();
    int get_speed();
    int get_lives();
    sf::Sprite& get_sprite();
    std::string get_name();
    std::vector<bullet*>& get_bullets();

    void load_gun(sf::Sprite& target);
    void fire_gun(player& target);
    bool isGunLoaded();

    void draw_player(sf::RenderWindow& window);
    void spray();

    //destructor
    ~player();

    friend class stat_bar;

};