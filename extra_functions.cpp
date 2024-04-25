#include "player_header.hpp"
#include "extra_header.hpp"
#include "item_header.hpp"

//vector math functions
void normalize_vector(sf::Vector2f& unnormalized_vec) {
    unnormalized_vec = unnormalized_vec / sqrt(powf(unnormalized_vec.x, 2) + powf(unnormalized_vec.y, 2));
}
sf::Vector2f full_direction(const sf::Sprite& origin, const sf::Sprite& target) {
    sf::Vector2f unit_direction(target.getPosition() - origin.getPosition());
    return unit_direction;
}
sf::Vector2f normal_direction(const sf::Sprite& origin, const sf::Sprite& target) {
    sf::Vector2f unit_direction(target.getPosition() - origin.getPosition());
    normalize_vector(unit_direction);
    return unit_direction;
}
float vector_to_degrees(const sf::Vector2f& vec) {
    float angle = (atan(abs(vec.y/vec.x))) * 180 / PI;
    if (vec.x < 0) angle = 180 - angle;
    if (vec.y < 0) angle = 360 - angle;
    return angle;
}
sf::Vector2f degrees_to_vector(float degrees) {
    float common = (90 - degrees) * PI / 180;
    return sf::Vector2f(cosf(common), sinf(common));
}
float magnitude(const sf::Vector2f& vec) {
    return sqrtf(vec.x * vec.x + vec.y * vec.y);
}

//sprite and player functions
int hit_window(const sf::Sprite& shape, const float buffer, const sf::FloatRect& boundary) {
    int hit = 0;
    //buffer of 0 means half of shape can be seen
    //buffer of 1 means entire shape can be seen
    sf::Vector2f shape_size = shape.getLocalBounds().getSize();

    if (shape.getPosition().x > boundary.left + boundary.width - buffer * shape_size.x / 2) hit += 1; //hit right
    if (shape.getPosition().x < boundary.left + buffer * shape_size.x / 2) hit += 2; //hit left
    if (shape.getPosition().y < boundary.top + buffer * shape_size.y / 2) hit += 4; //hit top
    if (shape.getPosition().y > boundary.top + boundary.height - buffer * shape_size.y / 2) hit += 8; //hit bottom

    //hit relies on binary interpretation such that
    //right -> ***1, left -> **1*, up -> *1**, down -> 1***

    return hit;
}
bool touching_hitbox(const sf::Sprite& sprite1, const sf::Sprite& sprite2) {

    float x_pos_dif = sprite1.getPosition().x - sprite2.getPosition().x;
    float y_pos_dif = sprite1.getPosition().y - sprite2.getPosition().y;
    x_pos_dif = fabsf(x_pos_dif);
    y_pos_dif = fabsf(y_pos_dif);

    float x_len = sprite1.getLocalBounds().getSize().x + sprite2.getLocalBounds().getSize().x;
    float y_len = sprite1.getLocalBounds().getSize().y + sprite2.getLocalBounds().getSize().y;
    x_len /= 2.0f;
    y_len /= 2.0f;

    if (x_pos_dif < x_len && y_pos_dif < y_len)
    {
        return true;
    }
    return false;

}
void key_move(player& user, const sf::FloatRect& boundary) {

    float speed = 0.05 * user.get_speed();

    int direction = 0;
    bool curr_move[4];
    static int last_move[4];

    sf::Keyboard::Key keys[] = { sf::Keyboard::Key::D, sf::Keyboard::Key::A , sf::Keyboard::Key::W , sf::Keyboard::Key::S };

    direction = hit_window(user.get_sprite(), 1, boundary);
    for (int i = 0; i < 4; i++) {
        curr_move[i] = 1 - direction % 2;
        direction >>= 1;
    }

    if (sf::Keyboard::isKeyPressed(keys[0])) user.get_sprite().move(speed * curr_move[0], 0);
    else curr_move[0] = 0;

    if (sf::Keyboard::isKeyPressed(keys[1])) user.get_sprite().move(-speed * curr_move[1], 0);
    else curr_move[1] = 0;

    if (sf::Keyboard::isKeyPressed(keys[2])) user.get_sprite().move(0, -speed * curr_move[2]);
    else curr_move[2] = 0;

    if (sf::Keyboard::isKeyPressed(keys[3])) user.get_sprite().move(0, speed * curr_move[3]);
    else curr_move[3] = 0;

    if (curr_move[0] && curr_move[1]) {
        if (last_move[0]) {
            user.get_sprite().move(speed, 0);
            curr_move[1] = 0;
        }
        else {
            user.get_sprite().move(-speed, 0);
            curr_move[0] = 0;
        }
    }

    if (curr_move[2] && curr_move[3]) {
        if (last_move[2]) {
            user.get_sprite().move(0, -speed);
            curr_move[3] = 0;
        }
        else {
            user.get_sprite().move(0, speed);
            curr_move[2] = 0;
        }
    }

    for (int i = 0; i < 4; i++) {
        last_move[i] = curr_move[i];
    }
}
void track(sf::Sprite& hunter, const sf::Sprite& prey, const float speed) {


    if (prey.getPosition() != hunter.getPosition()) {

        //gets direction from tracker to prey
        sf::Vector2f unit_direction = normal_direction(hunter, prey);

        //moves tracker in the direction of prey at 0.01 times 1
        hunter.move(unit_direction * speed);

    }
}
void center_origin(sf::Sprite& shape) {
    shape.setOrigin(shape.getLocalBounds().getSize() / 2.0f);
}
void fire_bullet(player& gunman, player& target, const sf::RenderWindow& window, const std::string control) {
    
    int timer = gunman.get_fire_timer();

    sf::Sprite control_pos;
    //shape set position to mouse
    if (control == "mouse") {
        control_pos.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
    }
    else if (control == "auto") {
        control_pos.setPosition(target.get_sprite().getPosition());
    }
    if (control_event(control) && timer == 0) {

        gunman.load_gun(control_pos);
        //starts reload timer (how long it takes for another bullet to be fired)
        timer = 3000 / gunman.get_fire_rate();
    }

    gunman.fire_gun(target);

    if (timer != 0) timer--;

    gunman.set_fire_timer(timer);
}
bool control_event(const std::string control) {

    if (control == "mouse") {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) return true;
    }
    else if (control == "auto") return true;
    return false;

}
void auto_move(player& robot, player& human, std::vector<item*>& items) {
    
    float dist_from_human = magnitude(robot.get_sprite().getPosition() - human.get_sprite().getPosition());
    float good_item_dist = WINDOW_W;
    float bad_item_dist = 0;
    float temp_dist;
    int good_item = -1, bad_item = -1;
    int speed = robot.get_speed();

    if (dist_from_human > 500) {
        track(robot.get_sprite(), human.get_sprite(), 0.03f * speed);
    }
    else if (dist_from_human < 400) {
        track(robot.get_sprite(), human.get_sprite(), -0.03f * speed);
    }

    if (items.empty()) return;

    for (size_t index = 0; index < items.size(); index++) {
        temp_dist = magnitude(robot.get_sprite().getPosition() - items[index]->get_sprite().getPosition());
        if ((temp_dist < good_item_dist) && items[index]->is_good() && !items[index]->is_collected()) {
            good_item_dist = temp_dist;
            good_item = index;
        }
        else if ((temp_dist < bad_item_dist) && !items[index]->is_good() && !items[index]->is_collected()) {
            bad_item_dist = temp_dist;
            bad_item = index;
        }
    }
    
    if (good_item != -1) {
        track(robot.get_sprite(), items[good_item]->get_sprite(), 0.05f * speed);
    }
    if (bad_item != -1) {
        track(robot.get_sprite(), items[bad_item]->get_sprite(), -0.05f * speed);
    }

}

//user interface functions
int menu()
{
    char selection = ' ';
    while (selection != '1' && selection != '7')
    {
        system("cls");
        cout << endl << " Welcome to Toy Story Rivalry!!" << endl << endl
            << " Please choose from the following options:" << endl
            << " 1. Play game" << endl
            << " 2. How to play" << endl
            << " 3. Items" << endl
            << " 4. Open messages" << endl
            << " 5. Credits" << endl
            << " 6. Test cases" << endl
            << " 7. Exit" << endl;

        selection = _getch();
        system("cls");

        switch (selection)
        {
        case '1':
            return 1;
            break;

        case '2':
            cout << endl << " HOW TO PLAY" << endl
                << " ----------------------------------------------------------------------------------------------------" << endl
                << " Movement: Use WASD to move!" << endl
                << " Shooting: Use your mouse or trackpad to aim and left click to shoot!" << endl
                << " Items: There are different items in the game that will affect your gameplay," << endl
                << " see the items section for a description of all the items!" << endl << endl
                << " Watch our for Andy!" << endl
                << " ";

            system("pause");
            break;

        case '3':
            cout << endl << " ITEMS" << endl
                << " ----------------------------------------------------------------------------------------------------" << endl
                << " Items are icon sprites that float across the screen and are collected by a player." << endl
                << " Each item has a different effect on the player and/or the game." << endl << endl << endl
                << " Power-Ups:" << endl << endl
                << " Speed Boost - Increases player's speed" << endl
                << " Gun Upgrade - Increasees player's fire rate" << endl
                << " Shield - Protects player" << endl
                << " Bullet Spray - Launches bullets in every direction" << endl << endl << endl
                << " Power-Downs:" << endl << endl
                << " Speed Drop - Decreases player's speed" << endl
                << " Gun Downgrade - Decreases player's fire rate" << endl
                << " Confusion - Decreases player's fire accuracy" << endl << endl << endl
                << " Miscellaneous:" << endl << endl
                << " Bomb - Bomb appears randomly on map and explodes" << endl
                << " Mystery - Random item" << endl << endl
                << " ";

            system("pause");
            break;

        case '4':
            recieve_message();
            break;

        case '5':
            cout << endl << " CREDITS" << endl
                << " ----------------------------------------------------------------------------------------------------" << endl
                << " Creators: Eli Lawrence, Jon Beil, Kyle Ortega-Gammill, Omar Herrera-Rea" << endl
                << " Sockets help: CodingMadeEasy on Youtube" << endl
                << " ----------------------------------------------------------------------------------------------------" << endl
                << " SOUND EFFECTS" << endl << endl
                << " Andys arrival- https://www.youtube.com/watch?v=dinyOvO2EEo&ab_channel=GamingSoundFX" << endl << endl
                << " Andy's coming- https://www.youtube.com/watch?v=l7ttIbfXTYU&ab_channel=ixiTimmyixi" << endl << endl
                << " Andy kill- https://www.youtube.com/watch?v=mQZDonQ1PVk&ab_channel=AdOks" << endl << endl
                << " Andy retreat- https://www.youtube.com/watch?v=oAmDyjtuzjo&ab_channel=YTSFX" << endl << endl
                << " Clair De Lune- https://www.youtube.com/watch?v=WNcsUNKlAKw&ab_channel=Rousseau" << endl << endl
                << " ANY SOUND EFFECT NOT LISTED WAS BY US!!!!!" << endl
                << " ----------------------------------------------------------------------------------------------------" << endl
                << " GRAPHICS" << endl << endl
                << " Background- https://www.reddit.com/r/PixelArt/comments/ttszul/i_made_a_simple_pixel_art_version_of_andys/" << endl << endl
                << " Woody sprite- https://www.pixilart.com/art/sheriff-woody-15e2f9a743250aa" << endl << endl
                << " Buzz sprite- https://www.artstation.com/artwork/J9Ry2d" << endl << endl
                << " Water gun- https://www.pngkey.com/maxpic/u2t4y3i1i1r5r5r5/" << endl << endl
                << " Real gun- https://www.pngkey.com/maxpic/u2t4y3i1i1r5r5r5/" << endl << endl
                << " Andy pic- https://school.eecs.wsu.edu/faculty/profile/?nid=aofallon" << endl << endl
                << " Shield- https://havran.itch.io/wooden-shield" << endl << endl
                << " Sun sprite- https://pngtree.com/so/sun" << endl << endl
                << " Bomb sprite- https://opengameart.org/content/bomb-sprite-vector-image" << endl << endl
                << " Beer sprite- https://gallery.yopriceville.com/Free-Clipart-Pictures/Drinks-PNG/Beer_Bottle_PNG_Clip_Art" << endl
                << " ----------------------------------------------------------------------------------------------------" << endl << endl
                << " ";
            system("pause");
            break;

        case '6':
            cout << " Welcome to test cases. Press any button to run the tests" << endl
                << " ";
            system("pause");
            cout << endl;
            testCases();
            system("pause");
            //return false;
            break;

        case '7':
            cout << " Thanks for playing!" << endl;
            return 0;
            break;

        }
    }
    return 0;
}
bool player_death(player& user) {
    return (user.get_lives() <= 0);
}
bool recieve_message() {

    int exit_code = 1;
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    sf::TcpSocket socket;
    socket.setBlocking(false);

    std::size_t recieved;
    char buffer[1000] = "";
    sf::TcpListener listener;
    int index = 0;

    while (exit_code != 0) {

        //waits for connection to server, user can end the connection
        cout << endl << " Waiting for connection..." << endl
            << " Press 'e' on your keyboard to exit. ";

        exit_code = 1;
        listener.listen(2000);
        listener.setBlocking(false);
        while (exit_code) {
            exit_code = listener.accept(socket);
            if (isPressed('e')) return 0;
        }
        system("cls");
        exit_code = 1;

        //will receive and output messages until user exits or reloads connection
        cout << endl << " Currently receiving messages." << endl
            << " Press e to exit or r to reload connection. " << endl;
        while (exit_code == 1) {
            index = 0;
            socket.receive(buffer, sizeof(buffer), recieved);
            if (recieved) {
                cout << buffer << endl;
            }
            if (isPressed('e')) exit_code = 0;
            if (isPressed('r')) exit_code = -1;
        }
        system("cls");
    }
    return 1;
}
bool send_message(const char string[], sf::TcpSocket& socket) {
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    char choice = ' ';
    static bool first_connection = true;
    socket.send("\nwoah", 6);

    cout << " Do you want to share your result? Y for yes, N for no: ";
    while (choice != 'Y' && choice != 'N') {
        cin >> choice;
    }
    sizeof(string);
    if (choice == 'Y') {
        if (first_connection) {
            if (socket.connect(ip, 2000)) {
                cout << endl << " Could not establish a connection." << endl << " ";
                system("pause");
                return false;
            }
            first_connection = false;
        }
        socket.send(string, strlen(string));
        return true;
    }
    else {
        first_connection = true;
    }
    return false;
}

//converts integer to string
std::string int_to_str(int num) {

    std::string alpha = "";
    int index = 0, temp = num, length = log10(num) + 1;

    if (num == 0) return "0";

    while (index < length) {
        temp = num / (int)pow(10, length - 1 - index);
        alpha += (temp % 10 + 48);
        index++;
    }

    return alpha;

}

//converts string to integer
int str_to_int(std::string alpha) {
    int index = 0, num = 0, length = alpha.size();
    for (int i = 0; i < length; i++) {
        num += powf(10, i) * (alpha[length - i - 1] - 48);
    }
    return num;
}

bool isPressed(char alpha) {
    if (_kbhit()) {
        if (_getch() == alpha)
            return 1;
    }
    return 0;
}

//item helper functions
void new_item(std::vector<item*>& items) {
    static int random_timer = 5000;
    item* new_item;

    if (!random_timer) {
        new_item = random_item();
        new_item->set_speed(0.2f);
        new_item->random_direction();
        items.push_back(new_item);
        random_timer = (rand() % 1000) + 3000;
    }
    else random_timer--;
}
item* random_item() {
    int rand_int = rand() % 10;
    switch (rand_int) {

    case 0: return new heart("CS122_PA9/heart.png", true);
    case 1: return new speed_boost("CS122_PA9/forwardArrows.png", true);
    case 2: return new gun_upgrade("CS122_PA9/ak47.png", true);
    case 3: return new shield("CS122_PA9/shield.png", true);
    case 4: return new bullet_spray("CS122_PA9/sun.png", true);
    case 5: return new speed_drop("CS122_PA9/backwardsArrows.png", false);
    case 6: return new gun_downgrade("CS122_PA9/gun.png", false);
    case 7: return new confusion("CS122_PA9/beer.png", false);
    case 8: return new bomb("CS122_PA9/bomb.png", false);
    case 9:
        std::string mystery = "CS122_PA9/mystery.png";
        switch (rand() % 9) {

        case 0: return new heart(mystery, false);
        case 1: return new speed_boost(mystery, false);
        case 2: return new gun_upgrade(mystery, false);
        case 3: return new shield(mystery, false);
        case 4: return new bullet_spray(mystery, false);
        case 5: return new speed_drop(mystery, false);
        case 6: return new gun_downgrade(mystery, false);
        case 7: return new confusion(mystery, false);
        case 8: return new bomb(mystery, false);
        }
    }

    return NULL;
}
void item_float(std::vector<item*>& items, sf::RenderWindow& window) {
    //shape set position to mouse
    static int reload_time = 0;
    int wall = 0;

    //loops through each current item
    for (auto i : items) {

        i->float_timer();

        //moves bullet 0.3 pixel lengths
        i->move();

        //if item touches window border, direction flips
        wall = hit_window(i->get_sprite());
        if ((wall % 2) || ((wall >> 1) % 2))
            i->flip_direction('H');
        else if (((wall >> 2) % 2) || ((wall >> 3) % 2))
            i->flip_direction('V');

    }

    if (reload_time != 0) reload_time--;

}
void item_triggered(std::vector<item*>& items, player& user, player& bad_guy) {

    for (size_t index = 0; index < items.size(); index++) {

        //if item touches hitbox OR item's timer runs out, item disappears
        if (items[index]->is_collected() == false) {

            if (touching_hitbox(items[index]->get_sprite(), user.get_sprite())) {
                items[index]->got_collected(user);
            }
            if (touching_hitbox(items[index]->get_sprite(), bad_guy.get_sprite())) {
                items[index]->got_collected(bad_guy);
            }

            if (items[index]->get_float_time() == 0) {
                delete items[index];
                items[index] = NULL;
                items.erase(items.begin() + index);
                index--;
            }
        }
        else {

            if (items[index]->get_float_time() == 0) {
                items[index]->reset_player(user, bad_guy);
                delete items[index];
                items[index] = NULL;
                items.erase(items.begin() + index);
                index--;
            }
        }
    }

}