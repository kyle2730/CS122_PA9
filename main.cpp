#include "player_header.hpp"
#include "extra_header.hpp"
#include "item_header.hpp";

int main(void) 
{
    //runs until user decides to exit
    while (1) {
        if (!menu()) return 0;

        //--------------------------INITIALIZATION-----------------------------------
        float circ_radius = 10;
        srand(time(NULL));
        sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "Game Name");
        sf::Music music;
        if (!music.openFromFile("CS122_PA9/themeSong.wav"))
            return -1;

        music.play();


        player user; //creates player
        player bad_guy; //creates opponent
        bad_guy.get_sprite().setPosition(sf::Vector2f(-200, -200));

        std::vector<bullet> bullets; //creates ammo
        std::vector<item*> items; //creates items

        //program loop
        while (window.isOpen()) {

            //-----------------------------------------UPDATE--------------------------------

            //event loop
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window.close();
                }
            }

            if (player_death(user)) {
                ///////////RUN DEATH ANIMATION + ETC.
                window.close();
                break;
            }

            //movement
            //key_move(stop_sign, speed, "aswd");
            item_float(items, user, window);
            key_move(user);
            new_item(items);
            fire_bullet(user, bad_guy, bullets, window);
            item_triggered(items, user, bullets);


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
            window.display();

        }
    }
}

