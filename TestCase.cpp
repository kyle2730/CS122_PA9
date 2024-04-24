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
	int i;
	for (i = -1; i < 5;)
	{
		player user("TestUser");
		cout << "Function being tested: player_death()" << endl;
		bool death = player_death(user);
		if (death == false)
		{
			cout << "Player is not currently dead, function successfully tested" << endl;
			i++;
		}
		else if (death == true)
		{
			cout << "Player has died, function successfully tested" << endl;
			i++;
		}
		else
		{
			cout << "Error testing function: player_death()" << endl;

		}
	}

	


	return i;
}
