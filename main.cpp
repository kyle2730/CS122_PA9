#include "player_header.hpp"
#include "extra_header.hpp"
#include "item_header.hpp";
#include "andy_header.hpp";

int run_app(void);

int main(void) {
    while (run_app());
    return 0;
}

int run_app(void) 
{
    
    if (!menu()) return 0;

    //--------------------------INITIALIZATION-----------------------------------
    float circ_radius = 10;
    bool andy_is_here = false;
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "Game Name");
    sf::Music music;
    if (!music.openFromFile("CS122_PA9/themeSong.wav")){
        //error checking
    }

    player user; //creates player
    player bad_guy; //creates opponent
    bad_guy.get_sprite().setPosition(sf::Vector2f(-200, -200));
    andy_man andy;


    std::vector<bullet> bullets; //creates ammo
    std::vector<item*> items; //creates items

    music.play();

    //program loop
    while (window.isOpen()) {

        //-----------------------------------------UPDATE--------------------------------

        //event loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
                delete_items(items);
                return 1;
            }
        }

        if (player_death(user)) {
            ///////////RUN DEATH ANIMATION + ETC.
            window.close();
            delete_items(items);
            return 1;
        }

        //movement
        //key_move(stop_sign, speed, "aswd");
        andy_is_here = andy.andys_coming(user, bullets);
        item_float(items, user, window, andy_is_here);
        key_move(user);
        new_item(items, andy_is_here);
        fire_bullet(user, bad_guy, bullets, window);
        item_triggered(items, user, bullets, andy_is_here);


        //------------------------------------------DRAW---------------------------------------------

        //clears screen with black pixels
        window.clear(sf::Color::White);

        for (size_t index = 0; index < items.size(); index++) {
            window.draw(items[index]->get_sprite());
        }
        for (size_t index = 0; index < bullets.size(); index++) {
            window.draw(bullets[index].get_sprite());
        }

        window.draw(bad_guy.get_sprite());
        user.draw_player(window);
        andy.draw_andy(window);
        window.display();

    }
    
}

