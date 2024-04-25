#include "player_header.hpp"
#include "extra_header.hpp"
#include "item_header.hpp"
#include "andy_header.hpp"


int run_app(sf::TcpSocket& socket);

int main(void) {
    sf::TcpSocket socket;

<<<<<<< HEAD
    //write_score(9000);

=======
>>>>>>> 5a876c115828d7af784b931a3303a2b4c15d4f3b
    while (1) {
        
        switch (menu()) {
        case 0: return 0;
        case 1: break;
        }
        run_app(socket);
    }

    return 0;
}

int run_app(sf::TcpSocket& socket)
{
    
    //some initializing
    float circ_radius = 10;
    bool andy_is_here = false;
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "Toy Story Rivalry"); //create render window

    //clair de lune set up
    sf::Music music;
    music.openFromFile("CS122_PA9/themeSong.wav");

    //creates backgound image
    sf::Texture bgd_img;
    bgd_img.loadFromFile("CS122_PA9/background.png");
    sf::Sprite background;
    background.setTexture(bgd_img, true);
    background.setPosition(sf::Vector2f(0, 0));

    player user("Woody"); //creates player
    player bad_guy("Buzz"); //creates opponent
    andy_man Andy; //creates Andy

    std::vector<item*> items; //creates items

    music.play(); //play's theme song

    //program loop
    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event))
        {
            //if the window is closed, yell at the player!
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
                delete_vector(items);
                cout << " YOU DON'T WANNA PLAY WITH ANDY? >:(" << endl << endl << " ";
                system("pause");
                return 1;
            }
        }

        //if user dies
        if (player_death(user) && !andy_is_here) {
            window.close();
            delete_vector(items);
            cout << " YOU DIED" << endl << endl;
            send_message(" I died (sent from server)", socket);
            return 1;
        }

        //if opponent dies
        if (player_death(bad_guy)) {
            window.close();
            delete_vector(items);
            cout << " YOUR OPPONENT DIED" << endl << endl;
            send_message(" I killed Buzz! (sent from server)", socket);
            return 1;
        }
        
        //andy stuff
        andy_is_here = Andy.andys_coming(user);
        //if andy mechanic is running
        if (!andy_is_here) {
            item_float(items, window);
            new_item(items);
            item_triggered(items, user, bad_guy);
            auto_move(bad_guy, user, items);
            fire_bullet(bad_guy, user, window, "auto");
        }
        
        //moves user with ASWD
        key_move(user);
        //fires bullet with mouse
        fire_bullet(user, bad_guy, window);

        //draws background
        window.draw(background);

        //draw items
        for (size_t index = 0; index < items.size(); index++) {
            window.draw(items[index]->get_sprite());
        }

        //draws all the players
        bad_guy.draw_player(window);
        user.draw_player(window);
        Andy.draw_andy(window);
        
        //displays everything
        window.display();

    }
}