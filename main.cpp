#include "SFML_header.hpp"
#include "item.hpp";

int main(void) 
{
    if (!menu()) return 0;
   
    //--------------------------INITIALIZATION-----------------------------------
    float circ_radius = 10, speed = 8;

    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "Game Name"); //creates window called window and opens it
    //window is opened in video mode ??? //400, 400 specifies height and width, string specifies window title

     ///////////////////////MOVE TO CLASS FUNCTIONS/////////////

    item andySprite("CS122_PA9/regularAndy.png");
    item evilAndySprite("CS122_PA9/evilAndy.png");

    
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
        item_float(items, player, window);
        key_move(player, speed);
        trigger_item(items);
        fire_bullet(player, stop_sign, bullets, window);
        
        //------------------------------------------DRAW---------------------------------------------

        //clears screen with black pixels
        window.clear(sf::Color::White);

        for (size_t index = 0; index < items.size(); index++) {
            window.draw(items[index].get_sprite());
        }
        for (size_t index = 0; index < bullets.size(); index++) {
            window.draw(bullets[index].get_sprite());
        }


        window.draw(player);
        window.draw(stop_sign);
        window.display();

      }

    return 0;

}
