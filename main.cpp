#include "SFML_header.hpp"

int hockey(void);
int shooter(void);

int main(void) {
    shooter();
}

int hockey(void) {

    //--------------------------INITIALIZATION-----------------------------------
    int radius = 80;
    float speed = radius / 5;

    sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "SFML works!"); //creates window called window and opens it
    //window is opened in video mode ??? //400, 400 specifies height and width, string specifies window title

    sf::CircleShape mallet_1(radius); //creates circle
    mallet_1.setPosition(sf::Vector2f(200, 10));
    mallet_1.setFillColor(sf::Color::Blue); //sets circle color to green
    center_origin(mallet_1);

    sf::CircleShape mallet_2(radius); //creates circle
    mallet_2.setPosition(sf::Vector2f(200, 390));
    mallet_2.setFillColor(sf::Color::Green); //sets circle color to green
    center_origin(mallet_2);

    sf::CircleShape puck(radius); //creates circle
    puck.setPosition(sf::Vector2f(WINDOW_W/2, WINDOW_H/2));
    puck.setFillColor(sf::Color::Red); //sets circle color to green
    center_origin(puck);

    sf::RectangleShape half_court(sf::Vector2f(WINDOW_W, 2));
    half_court.setPosition(sf::Vector2f(WINDOW_W / 2, WINDOW_H / 2));
    center_origin(half_court);

       //program loop
    while (window.isOpen()) {

        //-----------------------------------------UPDATE--------------------------------

        //event loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }

        //movement
        key_move(mallet_1, speed, "aswd", sf::FloatRect(0, 0, WINDOW_W, WINDOW_H / 2));
        mouse_move(mallet_2, window, sf::FloatRect(0, WINDOW_H / 2, WINDOW_W, WINDOW_H / 2));
        //key_move(mallet_2, speed, "arrow", sf::FloatRect(0, WINDOW_H / 2, WINDOW_W, WINDOW_H / 2));
        puck_slide(puck, mallet_1, mallet_2);

        //------------------------------------------DRAW------------------------

        //clears screen with black pixels
        window.clear();

        window.draw(half_court);
        window.draw(mallet_1);
        window.draw(mallet_2);
        window.draw(puck);
        window.display();

    }

    return 0;

}

int shooter(void) {

    //--------------------------INITIALIZATION-----------------------------------
    int circ_radius = 10;
    float speed = 8;

    sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "SFML works!"); //creates window called window and opens it
    //window is opened in video mode ??? //400, 400 specifies height and width, string specifies window title

    sf::CircleShape wheel(circ_radius); //creates circle
    wheel.setPosition(sf::Vector2f(200, 200));
    wheel.setFillColor(sf::Color::Green); //sets circle color to green
    center_origin(wheel);
    
    sf::CircleShape stop_sign(circ_radius, 8);
    stop_sign.setFillColor(sf::Color::Red);
    center_origin(stop_sign);

    std::vector<bullet> bullets;

    //sf::RectangleShape bullet(sf::Vector2f(rect_width / 10, rect_height / 20)); //creates rectangle_shaped bullet


    //program loop
    while (window.isOpen()) {

        //-----------------------------------------UPDATE--------------------------------

        //event loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }

        //movement
        key_move(stop_sign, speed, "aswd");
        key_move(wheel, speed);
        fire_bullet(stop_sign, wheel, bullets);
        
        //------------------------------------------DRAW------------------------

        //clears screen with black pixels
        window.clear();

        //draws each bullet
        for (size_t index = 0; index < bullets.size(); index++) {
            window.draw(bullets[index].casing);
        }

        window.draw(stop_sign);
        window.draw(wheel);
        window.display();

      }

    return 0;

}


//game ideas
/*

1. Killing Tux the Penguin (tap a specific number of times in 10 seconds to kill tux)
    - alternative gameplay ideas: 
        - chase Tux around some board/field
        - hit specific keys on keyboard fast, instead of tapping same key fast

2. Pac-Man (ghost chases character controlled by user through maze until character collects all orbs)
    - Game Features:
        - 1 ghost (moves master as levels increase)
        - smaller map

3. Air Hockey or Tennis (two player game between user and A.I or user and another user through docks)
 
4. Shooter Game (user-controlled player fires projectiles at randomly spawned enemies)
    - Game Features:
        - player runs through map, past enemies that shoot back (player must dodge bullets)
        - player gets health, once health = 0, player dies
        - multiple rounds with more/faster/stronger/bigger/scarier enemies
        - helpful items fly across screen for player to collect
            - items can add lives, make user faster, make user smaller, etc.
            - can add negative items as well
    - Alternative features
        - obstacles on map

5. 
*/