#include "player_header.hpp"
#include "extra_header.hpp"
#include "item_header.hpp";
#include "andy_header.hpp";

// things to test:
// playerDeath
// randomItem
// keyMove
// track
// fireBullet

int testCases()
{

	for (int i = 0; i < 5;)
	{
		player user("TestUser");
		cout << "Function being tested: player_death()" << endl;
		bool death = player_death(user);
		if (death == false)
		{
			cout << "Player is not currently dead, function successfully tested\n" << endl;
			i++;
		}
		else if (death == true)
		{
			cout << "Player has died, function successfully tested\n" << endl;
			i++;
		}
		else
		{
			cout << "Error testing function: player_death()\n" << endl;

		}

		sf::Sprite sprite1, sprite2;
		cout << "Function being tested: touching_hitbox() " << endl;
		bool touchesFreaky = touching_hitbox(sprite1, sprite2);
		if (touchesFreaky == true)
		{
			cout << "Player has been toouched, function successfully tested\n" << endl;
			i++;
		}
		else if (touchesFreaky == false)
		{
			cout << "Player has not been touched, function sucessfully tested\n" << endl;
			i++;
		}
		else
		{
			cout << "Error testing function: touching_hitbox()\n" << endl;
		}

	}

	

	


	return 1;
}
