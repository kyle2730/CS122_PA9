#pragma once

//ALL NECESSARY HEADERS INCLUDED
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <math.h>
#include <string>
#include <string.h>

//MACROS
#define WINDOW_W 1000
#define WINDOW_H 800
#define PI 3.14

//STD SHORCUTS
using std::cout;
using std::cin;
using std::endl;


//STAT BAR CLASS
class stat_bar {
private:

    //data members

    sf::RectangleShape text_box; //box that holds stats
    sf::Text stats; //literal text that displays stats
    sf::Font text_font; //stat font

public:
    
    //member functions

    stat_bar(); //constructor
    void draw_bar(sf::RenderWindow& window); //draws text_box and stats inside it
    void update_stats(int lives, int speed, int fire_rate); //if stats change, they are updated accordingly
    ~stat_bar(); //destructor
};

//BULLET CLASS
class bullet {

private:

    //data members

    sf::Sprite sprite; //the body of the bullet
    sf::Texture image; //bullet image displayed on sprite
    sf::Vector2f direction; //direction bullet flies through the air
    sf::SoundBuffer soundFile; //sound file for sound effects
    sf::Sound sound; //sound effects for the bullet
    time_t fire_time; //the time in seconds when bullet was fired
    bool active; //whether the bullet is still flying through the air

public:

    //member functions
    
    bullet(); //constructor

    //setters
 
    //points bullet towards target from origin
    void lock_on(const sf::Sprite& origin, const sf::Sprite& target, int accuracy);
    //sets bullet position
    void set_position(const sf::Vector2f& position);
    //sets sound effects
    void set_sound();
    void set_woody_sound();
    //sets bullet image
    void set_image();

    //getters

    //returns sprite
    sf::Sprite& get_sprite();
    //returns time when bullet was fired
    time_t get_fire_time();
    //returns whether bullet is active
    bool is_active();

    
    void move(const float speed);//moves bullet at speed
    void hit();//sets active to false and size to 0
    bool past_sound_time();//returns whether bullet sound has played through
    
    ~bullet(); //destructor
};

//PLAYER CLASS
class player {

private:

    //data members

    sf::Sprite sprite;
    sf::Texture image;
    stat_bar data;
    std::string name;

    int lives;
    int speed;
    int fire_rate;
    int fire_timer; //time left til next bullet can be fired
    int accuracy;

    std::vector<bullet*> bullets; //vector of bullet pointers that are dynamically allocated as needed

    //sound file and effect
    sf::SoundBuffer buffer;
    sf::Sound soundEffect;

public:

    //member functions

    player(const std::string& new_name);//constructor

    //setters

    void add_lives(int extra); //edits lives left
    //increments data members
    void speed_up();
    void speed_down();
    void gun_up();
    void gun_down();
    void drop_accuracy();
    void raise_accuracy();
    void set_fire_timer(int new_timer); //sets new timer once bullet has been fired
    void sound_base(const std::string file); //plays sound from file

    //getters

    int get_accuracy();
    int get_fire_rate();
    int get_fire_timer();
    int get_speed();
    int get_lives();
    sf::Sprite& get_sprite();
    std::string get_name();
    std::vector<bullet*>& get_bullets();

    //gun functions

    void load_gun(sf::Sprite& target); //prepares bullet to be fired
    void fire_gun(player& target); //fires bullet
    bool isGunLoaded(); //checks if gun just fired a bullet
    void spray(); //sprays bullets in all directions

    //draws player, player's bullets, and player's stat bar
    void draw_player(sf::RenderWindow& window);
    

    //destructor
    ~player();

    friend class stat_bar;

};