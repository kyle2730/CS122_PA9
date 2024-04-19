#include "SFML_header.hpp"

int shooter(void);

int main(void) {
    shooter();
}

int shooter(void) {

    //--------------------------INITIALIZATION-----------------------------------
    int circ_radius = 10;
    float speed = 8;

    sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "SFML works!"); //creates window called window and opens it
    //window is opened in video mode ??? //400, 400 specifies height and width, string specifies window title

     ///////////////////////MOVE TO CLASS FUNCTIONS/////////////
     sf::Texture andyTexture; //andy
     sf::Texture evilAndyTexture; //evil andy
     sf::Texture bombTexture; //bomb
     sf::Texture gunTexture; //gun upgrade
     sf::Texture shieldTexture; //shield
     sf::Texture sunTexture; //bullet spray
     sf::Texture forwardArrowsTexture; //speed boost
     sf::Texture backwardsArrowsTexture; //speed drop


     if (!andyTexture.loadFromFile("regularAndy.png"))
     {
         //error checking
     }

     if (!evilAndyTexture.loadFromFile("evilAndy.png"))
     {
         //error checking
     }
    
     if (!bombTexture.loadFromFile("bomb.png"))
     {
         //error checking
     }
    
     if (!gunTexture.loadFromFile("gun.png"))
     {
         //error checking
     }
    
     if (!shieldTexture.loadFromFile("shield.png"))
     {
         //error checking
     }
    
     if (!sunTexture.loadFromFile("sun.png"))
     {
         //error
     }
    
     if (!forwardArrowsTexture.loadFromFile("forwardArrows.png"))
     {
         //error checking
     }

     if (!backwardsArrowsTexture.loadFromFile("backwardsArrows.png"));
     {
         //error checking
     }
     sf::Sprite andySprite;
     sf::Sprite evilAndySprite;
     sf::Sprite bombSprite;
     sf::Sprite gunSprite;
     sf::Sprite shieldSprite;
     sf::Sprite sunSprite;
     sf::Sprite forwardArrowsSprite;
     sf::Sprite backwardsArrowsSprite;
    
     andySprite.setTexture(andyTexture);
     evilAndySprite.setTexture(evilAndyTexture);
     bombSprite.setTexture(bombTexture);
     gunSprite.setTexture(gunTexture);
     shieldSprite.setTexture(shieldTexture);
     sunSprite.setTexture(sunTexture);
     forwardArrowsSprite.setTexture(forwardArrowsTexture);
     backwardsArrowsSprite.setTexture(backwardsArrowsTexture);
    
     window.draw(andySprite);
     window.draw(evilAndySprite);
     window.draw(bombSprite);
     window.draw(gunSprite);
     window.draw(shieldSprite);
     window.draw(sunSprite);
     window.draw(forwardArrowsSprite);
     window.draw(backwardsArrowsSprite);
    
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
