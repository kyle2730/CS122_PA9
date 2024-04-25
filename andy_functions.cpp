#include "andy_header.hpp"

void andy_man::sound_base(const std::string file)
{
    if (buffer.loadFromFile(file))
    {
        soundEffect.setBuffer(buffer);
        soundEffect.play();
    }
}

andy_man::andy_man() {
    start_time = time(NULL) + 5;

    body.setPosition(sf::Vector2f(WINDOW_W + 300, WINDOW_H / 2.0f + 300));
    if (!normal_face.loadFromFile("CS122_PA9/regularAndy.png")) {}
    if (!evil_face.loadFromFile("CS122_PA9/evilAndy.png")) {}
    body.setTexture(normal_face, true);
    center_origin(body);

    if (!text_font.loadFromFile("CS122_PA9/Pixellari.ttf")) {}

    text_box.setPosition(sf::Vector2f(-200, -200));
    text_box.setSize(sf::Vector2f(250, 75));
    text_box.setFillColor(sf::Color::White);
    text_box.setOutlineColor(sf::Color::Red);
    text_box.setOutlineThickness(2);

    warning.setString("ANDY IS COMING!\nHIDE!");
    warning.setFillColor(sf::Color::Black);
    warning.setPosition(sf::Vector2f(-200, -200));
    warning.setCharacterSize(25);
    warning.setFont(text_font);
}

void andy_man::draw_andy(sf::RenderWindow& window) {
    window.draw(body);
    window.draw(text_box);
    window.draw(warning);
}

bool andy_man::andys_coming(player& user) {

    static float x_pos = 0, y_pos = 0;

    //Andy sequence doesn't start until time passes start_time
    if (time(NULL) < start_time) return false;

    sf::Vector2f position = user.get_sprite().getPosition();

    //items stop moving and displays warning about Andy for two seconds
    if (time(NULL) == start_time) {
        text_box.setPosition(sf::Vector2f(WINDOW_W / 2.0f - 125, WINDOW_H / 2.0f - 35));
        warning.setPosition(sf::Vector2f(WINDOW_W / 2.0f - 115, WINDOW_H / 2.0f - 25));
        sound_base("CS122_PA9/andySound.wav");
        start_time--;
    }
    else if (time(NULL) < start_time + 3);

    //removes warning display after 2 seconds
    else if (time(NULL) == start_time + 3) {
        body.setPosition(sf::Vector2f(WINDOW_W, WINDOW_H / 2));
        text_box.setPosition(sf::Vector2f(-200, -200));
        warning.setPosition(sf::Vector2f(-200, -200));
        x_pos = position.x;
        y_pos = position.y;
        sound_base("CS122_PA9/andyAlertSound.wav");
        start_time--;
    }

    //Andy moves to the center of the screen (2 second buffer)
    else if ((time(NULL) < start_time + 6) && (body.getPosition().x > WINDOW_W / 2)) {
        body.move(sf::Vector2f(-1, 0));
    }

    //Andy checks for movement for 9 seconds
    else if (time(NULL) < start_time + 15) {

        //if player moved or fired a bullet
        if ((position.x != x_pos) || (position.y != y_pos) || user.isGunLoaded()) {
            //moves to andy destroys if statement
            sound_base("CS122_PA9/andyKillSound.wav");
            start_time = time(NULL) - 16;

        }

        //andy plays retreat sound after 5 seconds
        if (time(NULL) == start_time + 11)
        {
            sound_base("CS122_PA9/andyRetreat2.wav");
            start_time--;
        }

        //andy retreats for 3 seconds
        else if ((time(NULL) > start_time + 11) && (body.getPosition().x > -100))
        {
            body.move(sf::Vector2f(-0.15, 0));
        }
    }



    //resets andy mechanic after andy moves off screen
    else if ((time(NULL) == start_time + 15) && (body.getPosition().x < -100)) {
        start_time = time(NULL) + 15;
    }

    //andy turns evil
    else if (time(NULL) == start_time + 16) {
        body.setTexture(evil_face, true);
        start_time--;
    }

    //andy moves to player for two seconds
    else if (time(NULL) < start_time + 20) {
        track(body, user.get_sprite(), (time(NULL) - (start_time + 16)) / 10.0f);
    }

    //andy DESTROYS
    else if (time(NULL) == start_time + 20) {
        user.add_lives(-10000);
        return false;
    }

    return true;
}