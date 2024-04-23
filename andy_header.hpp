#pragma once

#include "player_header.hpp"

class andy_man {
private:
	sf::Sprite body;
	sf::Texture normal_face;
	sf::Texture evil_face;
	sf::RectangleShape text_box;
	sf::Text warning;
	sf::Font text_font;
    int timer = -25000;

    sf::SoundBuffer buffer;
    sf::Sound soundEffect;
public:

    void sound_base(const std::string file)
    {
        if (buffer.loadFromFile(file))
        {
            soundEffect.setBuffer(buffer);
            soundEffect.play();
        }
    }

	andy_man() {
        body.setPosition(sf::Vector2f(WINDOW_W, WINDOW_H / 2.0f));
        if (!normal_face.loadFromFile("CS122_PA9/regularAndy.png")) {}
        if (!evil_face.loadFromFile("CS122_PA9/evilAndy.png")) {}
        body.setTexture(normal_face, true);

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
    void draw_andy(sf::RenderWindow& window) {
        window.draw(body);
        window.draw(text_box);
        window.draw(warning);
    }
    bool andys_coming(player& user, std::vector<bullet>& bullets) {

        static float x_pos = 0, y_pos = 0;
        timer++;

        //andy sequence doesn't start until after 50,000 iterations
        if (timer < 0) return false;

        sf::Vector2f position = user.get_sprite().getPosition();

        //displays warning about andy, items stop moving at t-0
        if (timer == 0) {
            text_box.setPosition(sf::Vector2f(WINDOW_W / 2.0f - 125, WINDOW_H / 2.0f - 35));
            warning.setPosition(sf::Vector2f(WINDOW_W / 2.0f - 115, WINDOW_H / 2.0f - 25));
            sound_base("CS122_PA9/andySound.wav");
        }

        else if (timer < 5000);

        //removes warning display at t-5000
        else if (timer == 5000) {
            body.setPosition(sf::Vector2f(WINDOW_W, WINDOW_H / 2));
            text_box.setPosition(sf::Vector2f(-200, -200));
            warning.setPosition(sf::Vector2f(-200, -200));
            x_pos = position.x;
            y_pos = position.y;
            sound_base("CS122_PA9/andyAlertSound.wav");
        }

        //andy is moving from t-5000 to t-6000 towards the center
        else if (timer < 6000) {
            body.move(sf::Vector2f(WINDOW_W / -2000.0f, 0));
        }

        //andy checks for movement from t-6000 to t-15000
        else if (timer < 15000) {

            //if player moved or fired a bullet
            if ((position.x != x_pos) || (position.y != y_pos) || !bullets.empty()) {
                //moves to andy destroys if statement
                timer = 17000;
                sound_base("CS122_PA9/andyKillSound.wav");
                
            }
        }

        else if (timer == 15000)
        {
            sound_base("CS122_PA9/andyRetreat2.wav");
        }
        //andy retreats from t-15000 to t-16000
        else if (timer < 17000)
        {
            body.move(sf::Vector2f(WINDOW_W / -2000.0f, 0));
        }

        //resets andy at t-16000
        else if (timer == 17000) timer = -25000;

        //andy turns evil if t is set to 17000
        else if (timer == 17500) body.setTexture(evil_face, true);

        //andy moves to player from t-1700 to t-21000
        else if (timer < 22000) {}

        //andy DESTROYS at t-21000
        else if (timer == 22000) user.add_lives(-10000);

        return true;
    }

};