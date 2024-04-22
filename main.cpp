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
        bool andy_is_here = false;
        srand(time(NULL));
        sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "Game Name");
        sf::Music music;
        if (!music.openFromFile("CS122_PA9/themeSong.wav"))
            return -1;

        music.play();


        player user; //creates player
        player bad_guy; //creates opponent
        bad_guy.get_sprite().setPosition(sf::Vector2f(-200, -200));
        struct andy_man andy;
        andy.body.setPosition(sf::Vector2f(WINDOW_W, WINDOW_H / 2.0f));

        if (!andy.normal_face.loadFromFile("CS122_PA9/regularAndy.png")) {
            //error checking
        }
        if (!andy.evil_face.loadFromFile("CS122_PA9/evilAndy.png")) {
            //error checking
        }
        andy.body.setTexture(andy.normal_face, true);

        if (!andy.text_font.loadFromFile("CS122_PA9/Pixellari.ttf")) {
            //error
        }

        andy.text_box.setPosition(sf::Vector2f(-200,-200));
        andy.text_box.setSize(sf::Vector2f(250, 75));
        andy.text_box.setFillColor(sf::Color::White);
        andy.text_box.setOutlineColor(sf::Color::Red);
        andy.text_box.setOutlineThickness(2);

        andy.warning.setString("ANDY IS COMING!\nHIDE!");
        andy.warning.setFillColor(sf::Color::Black);
        andy.warning.setPosition(sf::Vector2f(-200,-200));
        andy.warning.setCharacterSize(25);
        andy.warning.setFont(andy.text_font);


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
            andy_is_here = andys_coming(andy, user, bullets);
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
            window.draw(andy.body);
            window.draw(andy.text_box);
            window.draw(andy.warning);
            window.display();

        }
    }
}

