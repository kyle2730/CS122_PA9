#include "SFML_header.hpp"
#include "item.hpp";

int shooter(void);

int main(void) {
    shooter();
}

int shooter(void) {

    //--------------------------INITIALIZATION-----------------------------------
    float circ_radius = 10, speed = 8;

    srand(time(NULL));

    if (!menu()) return 0;

    sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "Game Name"); //creates window called window and opens it
    //window is opened in video mode ??? //400, 400 specifies height and width, string specifies window title

     ///////////////////////MOVE TO CLASS FUNCTIONS/////////////

    item andySprite("regularAndy.png");
    item evilAndySprite("evilAndy.png");
    item bombSprite("bomb.png");
    item gunSprite("gun.png");
    item shieldSprite("shield.png");
    item sunSprite("sun.png");
    item forwardArrowsSprite("forwardArrows.png");
    item backwardsArrowsSprite("backwardsArrows.png");
    item beerSprite("beer.png");
    item ak47Sprite("ak47.png");

    
    sf::Sprite player; //creates player
    sf::Texture p_t;
    p_t.loadFromFile("CS122_PA9/player.png");
    player.setTexture(p_t);
    player.setPosition(sf::Vector2f(200, 200));
    center_origin(player);
    
    sf::Sprite stop_sign;
    center_origin(stop_sign);

    std::vector<bullet> bullets;
    std::vector<item> items;

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
        //key_move(stop_sign, speed, "aswd");
        key_move(player, speed);
        trigger_item(items);
        fire_bullet(player, stop_sign, bullets, window);
        
        //------------------------------------------DRAW---------------------------------------------

        //clears screen with black pixels
        window.clear();

        for (size_t index = 0; index < items.size(); index++) {
            window.draw(items[index].get_sprite());
        }
        for (size_t index = 0; index < bullets.size(); index++) {
            window.draw(bullets[index].get_sprite());
        }


        window.draw(player);
        window.draw(stop_sign);
        andySprite.draw_sprite(window);
        evilAndySprite.draw_sprite(window);
        bombSprite.draw_sprite(window);
        gunSprite.draw_sprite(window);
        shieldSprite.draw_sprite(window);
        sunSprite.draw_sprite(window);
        forwardArrowsSprite.draw_sprite(window);
        backwardsArrowsSprite.draw_sprite(window);
        beerSprite.draw_sprite(window);
        ak47Sprite.draw_sprite(window);
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

CS122_PA9/ - use to load images
*/
