#include "player_header.hpp"
#include "extra_header.hpp"
#include "item_header.hpp";
#include "andy_header.hpp";
#include <Windows.h>


int run_app(void);

int main(void) {
    while (run_app()) {
        system("pause");
    }

    return 0;
}

int run_app(void) 
{
    
    if (!menu()) return 0;

    //--------------------------INITIALIZATION-----------------------------------
    
    //Sockets setup:
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    sf::TcpSocket socket;
    char connectionType, mode;

    cout << "Enter (s) for Server or (c) for Client: " << endl;
    cin >> connectionType;

    if (connectionType == 's') {
        sf::TcpListener listener;
        listener.listen(2000);
        listener.accept(socket);


        float circ_radius = 10;
        bool andy_is_here = false;
        srand(time(NULL));
        sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "Toy Story Rivalry");
        sf::Music music;
        if (!music.openFromFile("CS122_PA9/themeSong.wav")) return 1;

        //creates backgound image
        sf::Texture bgd_img;
        if (!bgd_img.loadFromFile("CS122_PA9/background.png")) return 1;
        sf::Sprite background;
        background.setTexture(bgd_img, true);
        background.setPosition(sf::Vector2f(0, 0));

        player user("Woody"); //creates player
        player bad_guy("Buzz"); //creates opponent
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
                    cout << "YOU DON'T WANNA PLAY WITH ANDY? >:(" << endl << endl;
                    return 1;
                }
            }

            if (player_death(user)) {
                ///////////RUN DEATH ANIMATION + ETC.
                window.close();
                delete_items(items);
                cout << "YOU DIED (Displayed on Server's screen" << endl << endl;
                socket.send("You died Faggot (sent from server to client)", 50);
                return 1;
            }

            if (player_death(bad_guy)) {
                ///////////RUN DEATH ANIMATION + ETC.
                window.close();
                delete_items(items);
                cout << "YOUR OPPONENT DIED" << endl << endl;
                socket.send("You killed him!", 16);
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
            window.draw(background);

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
    else {
        
        sf::Socket::Status status;
        std::size_t recieved;
        char buffer[1000] = "", buffer2[1000] = "";
        socket.connect(ip, 2000);
        
        //while (1) {
             socket.receive(buffer, sizeof(buffer), recieved);
             system("cls");
             cout << buffer << endl;  
             Sleep(1000);
       //}
    }
}


/*

1. Progam AI opponent
4. Recording scores


*/












//#include "player_header.hpp"
//#include "extra_header.hpp"
//#include "item_header.hpp";
//#include "andy_header.hpp";
//
//
//int run_app(void);
//
//int main(void) {
//    while (run_app()) {
//        system("pause");
//    }
//
//    return 0;
//}
//
//int run_app(void)
//{
//
//    if (!menu()) return 0;
//
//    //--------------------------INITIALIZATION-----------------------------------
//
//    //Sockets setup:
//    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
//    sf::TcpSocket socket;
//    char connectionType, mode;
//
//    cout << "Enter (s) for Server or (c) for Client: " << endl;
//    cin >> connectionType;
//
//    if (connectionType == 's') {
//        sf::TcpListener listener;
//        listener.listen(2000);
//        listener.accept(socket);
//
//
//        float circ_radius = 10;
//        bool andy_is_here = false;
//        srand(time(NULL));
//        sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "Toy Story Rivalry");
//        sf::Music music;
//        if (!music.openFromFile("CS122_PA9/themeSong.wav")) return 1;
//
//        //creates backgound image
//        sf::Texture bgd_img;
//        if (!bgd_img.loadFromFile("CS122_PA9/background.png")) return 1;
//        sf::Sprite background;
//        background.setTexture(bgd_img, true);
//        background.setPosition(sf::Vector2f(0, 0));
//
//        player user("Woody"); //creates player
//        player bad_guy("Buzz"); //creates opponent
//        bad_guy.get_sprite().setPosition(sf::Vector2f(-200, -200));
//        andy_man andy;
//
//
//        std::vector<bullet> bullets; //creates ammo
//        std::vector<item*> items; //creates items
//
//        music.play();
//
//        //program loop
//        while (window.isOpen()) {
//
//            //-----------------------------------------UPDATE--------------------------------
//
//            //event loop
//            sf::Event event;
//            while (window.pollEvent(event))
//            {
//                if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
//                    window.close();
//                    delete_items(items);
//                    cout << "YOU DON'T WANNA PLAY WITH ANDY? >:(" << endl << endl;
//                    return 1;
//                }
//            }
//
//            if (player_death(user)) {
//                ///////////RUN DEATH ANIMATION + ETC.
//                window.close();
//                delete_items(items);
//                cout << "YOU DIED" << endl << endl;
//                socket.send("You died Faggot", 16);
//                return 1;
//            }
//
//            if (player_death(bad_guy)) {
//                ///////////RUN DEATH ANIMATION + ETC.
//                window.close();
//                delete_items(items);
//                cout << "YOUR OPPONENT DIED" << endl << endl;
//                socket.send("You killed him!", 16);
//                return 1;
//            }
//
//            //movement
//            //key_move(stop_sign, speed, "aswd");
//            andy_is_here = andy.andys_coming(user, bullets);
//            item_float(items, user, window, andy_is_here);
//            key_move(user);
//            new_item(items, andy_is_here);
//            fire_bullet(user, bad_guy, bullets, window);
//            item_triggered(items, user, bullets, andy_is_here);
//
//
//            //------------------------------------------DRAW---------------------------------------------
//
//            //clears screen with black pixels
//            window.draw(background);
//
//            for (size_t index = 0; index < items.size(); index++) {
//                window.draw(items[index]->get_sprite());
//            }
//            for (size_t index = 0; index < bullets.size(); index++) {
//                window.draw(bullets[index].get_sprite());
//            }
//
//            window.draw(bad_guy.get_sprite());
//            user.draw_player(window);
//            andy.draw_andy(window);
//            window.display();
//
//        }
//    }
//    else {
//        std::size_t recieved;
//        char buffer[1000] = "";
//        socket.connect(ip, 2000);
//        std::string tempMessage;
//        while (1) {
//            socket.receive(buffer, sizeof(buffer), recieved);
//            cout << buffer << endl;
//        }
//    }
//}
//
//
///*
//
//1. Progam AI opponent
//4. Recording scores
//
//
//*/