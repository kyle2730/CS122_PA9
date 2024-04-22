#pragma once

#include "player_header.hpp"

class item
{
public:
	item();
	item(const std::string& file_name);

	//setters
	void set_speed(const float new_speed);
	virtual void got_collected(player& user, std::vector<bullet>& bullets);

	//getters
	int get_float_time();
	bool is_collected();

	void flip_direction(const char wall);
	void float_timer();
	void random_direction();

	void sound_base(const std::string file);
	virtual void set_sound() = 0;
	virtual void move();
	virtual void hit(player& user) = 0; //function when player hits item, different for each item
	virtual void reset_player(player& user) = 0;
	void draw_item(sf::RenderWindow& window); //draws the graphics for the item

	sf::Sprite& get_sprite();

	~item();

protected:

	sf::Sprite sprite;
	sf::Vector2f direction;
	sf::Texture* image;
	float speed;
	int float_time;
	bool collected;
	sf::SoundBuffer buffer;
	sf::Sound soundEffect;
};

class heart : public item {
public:
	heart(const std::string& file_name) : item(file_name){}

	void hit(player& user);
	void reset_player(player& user);
	void set_sound();
};
class speed_boost : public item {
public:
	speed_boost(const std::string& file_name) : item(file_name) {}
	void hit(player& user);
	void reset_player(player& user);
	void set_sound();
};
class gun_upgrade : public item {
public:
	gun_upgrade(const std::string& file_name) : item(file_name) {}
	void hit(player& user);
	void reset_player(player& user);
	void set_sound();
};
class shield : public item {
public:
	shield(const std::string& file_name) : item(file_name) {}
	void hit(player& user);
	void reset_player(player& user);
	void set_sound();


};
class bullet_spray : public item {
public:
	bullet_spray(const std::string& file_name) : item(file_name) {}
	void hit(player& user, std::vector<bullet>& bullets);
	void hit(player& user);
	void reset_player(player& user);
	void got_collected(player& user, std::vector<bullet>& bullets);
	void set_sound();

};
class speed_drop : public item {
public:
	speed_drop(const std::string& file_name) : item(file_name) {}
	void hit(player& user);
	void reset_player(player& user);
	void set_sound();

};
class gun_downgrade : public item {
public:
	gun_downgrade(const std::string& file_name) : item(file_name) {}
	void hit(player& user);
	void reset_player(player& user);
	void set_sound();

};
class confusion : public item {
public:
	confusion(const std::string& file_name) : item(file_name) {}
	void hit(player& user);
	void reset_player(player& user);
	void set_sound();

};
class bomb : public item {
public:
	bomb(const std::string& file_name) : item(file_name) {}
	void hit(player& user);
	void reset_player(player& user);
	void move();
	void set_sound();
};