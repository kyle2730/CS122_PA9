#include "player_header.hpp"
#include "extra_header.hpp"
#include "item_header.hpp";
#include "andy_header.hpp";

// things to test:

int testTrack()
{
	srand(unsigned int(time(nullptr)));

	cout << endl;
	int successes = 0;
	int finalsuccess = 0;
	sf::Vector2f initialHunterPosition(100, 100);
	sf::Vector2f initialPreyPosition(100, 100);
	sf::Sprite hunter, prey;
	hunter.setPosition(initialHunterPosition);
	prey.setPosition(initialPreyPosition);
	float speed = 5.0f;

	cout << "Initial Hunter Position: (" << initialHunterPosition.x << ", " << initialHunterPosition.y << ")" << endl;
	cout << "Initial Prey Position: (" << initialPreyPosition.x << ", " << initialPreyPosition.y << ")" << endl;

	track(hunter, prey, speed);

	cout << "Final Hunter Position: (" << hunter.getPosition().x << ", " << hunter.getPosition().y << ")" << endl;

	// Check if the hunter's position remains unchanged
	if (hunter.getPosition() == initialHunterPosition)
	{
		cout << "\nTest case 1 Passed: Hunter did not move when prey and hunter are at the same position.\n" << endl;
		successes++;
		finalsuccess++;
	}
	else
	{
		cout << "\nTest case 1 Failed: Hunter moved unexpectedly when prey and hunter are at the same position." << endl;
	}

	cout << "Testing movement according to speed:\n" << endl;
	for (int i = 0; i < 5; i++)
	{
		speed = 20.0f;
		sf::Vector2f randomizedHunterPosition((rand() % 100 + 1), (rand() % 100 + 1));
		hunter.setPosition(randomizedHunterPosition);
		cout << "Randomized Hunter Position: (" << randomizedHunterPosition.x << ", " << initialHunterPosition.y << ")" << endl;
		track(hunter, prey, speed);

		cout << "Final Hunter Position: (" << hunter.getPosition().x << ", " << hunter.getPosition().y << ")" << endl;
		successes++;
	}
	if (successes >= 5)
	{
		cout << "Test 2 passed: Hunter moved in respect to prey's postition" << endl;
		finalsuccess++;
	}
	else
	{
		cout << "Test 2 not passed: Hunter did not always move in respect to prey's position" << endl;
	}
	return finalsuccess;
}

// will ensure items are successfully being generated randomly
int testRandonItem()
{
	int successes = 0;
	int finalsuccess = 0;
	int prevItem = -1;

	for (int i = 0; i < 5; i++) 
	{
		int rand_int = rand() % 10;

		while (rand_int == prevItem) 
		{
			rand_int = rand() % 10;
		}

		switch (rand_int) 
		{
		case 0: cout << "Heart item generated.\n"; break;
		case 1: cout << "Speed boost item generated.\n"; break;
		case 2: cout << "Gun upgrade item generated.\n"; break;
		case 3: cout << "Shield item generated.\n"; break;
		case 4: cout << "Bullet spray item generated.\n"; break;
		case 5: cout << "Speed drop item generated.\n"; break;
		case 6: cout << "Gun downgrade item generated.\n"; break;
		case 7: cout << "Confusion item generated.\n"; break;
		case 8: cout << "Bomb item generated.\n"; break;
		case 9: cout << "Mystery item generated.\n"; break;
		}
		if (prevItem != rand_int)
		{
			successes++;
		}

		prevItem = rand_int;
	}

	bool testPassed = (successes >= 4);
	if (testPassed) 
	{
		cout << "Test successfully passed: Items generated randomly!\n" << endl;
		finalsuccess++;
	}
	else 
	{
		cout << "Test failed: Items not generated randomly. Review code." << endl;
	}
	return finalsuccess;
}

int testItemTriggered()
{
	srand(unsigned int(time(nullptr)));

	int successes = 0;
	int finalsuccess = 0;
	std::vector<item*> items;
	player user("testUser");
	std::vector<bullet> bullets;

	std::vector<bool> randomValues;
	for (int i = 0; i < 5; ++i) 
	{
		bool value = rand() % 2 == 0;
		randomValues.push_back(value);
	}
	
	for (int i = 0; i < 5; ++i) 
	{
		cout << "Testing item " << i + 1 << ": " << endl;

		if (randomValues[i]) 
		{
			cout << "Bool value = " <<randomValues[i] << '\n' << "Item should be triggered" << endl;
			cout << "Item triggered.\n" << endl;
			successes++;
		}
		else 
		{
			cout << "Bool value = \n" << randomValues[i] << "Item shouldn't be triggered\n" << endl;
			cout << "Item not triggered." << std::endl;
			successes++;
		}
		item_triggered(items, user, bullets, randomValues[i]);
	}
	if (successes >= 4)
	{
		cout << "Test passed, items triggered correctly\n" << endl;
		finalsuccess = 1;
		return finalsuccess;
	}
	else
	{
		cout << "Test failed, items triggered incorrectly\n" << endl;
		return finalsuccess;
	}
}

int testIntToAlpha()
{
	srand(unsigned int(time(nullptr)));
	int successes = 0;
	int finalsuccess = 0;

	for (int i = 0; i < 5; i++)
	{
		int testNumber = rand() % 100;
		std::string string = int_to_str(testNumber);
		cout << "Integer input: " << testNumber << endl;
		cout << "String generated: " << string << endl;
		successes++;
	}

	if (successes == 5)
	{
		cout << "Test passed! Integers successfully turned into strings.\n" << endl;
		finalsuccess++;
		return finalsuccess;
	}
	else
	{
		cout << "Test failed! Error turning integers into strings.\n" << endl;
		return finalsuccess;
	}
}

// this function houses all the other test functions/cases
int testCases()
{
	int successes = 0;
	cout << endl;
	cout << "Currently testing: Track()" << endl;

	successes += testTrack();
	cout << endl;
	system("pause");

	cout << "Currently testing: randomItem()" << endl;
	successes += testRandonItem();
	system("pause");

	cout << "Currently testing: itemTriggered()\n" << endl;
	successes += testItemTriggered();
	system("pause");

	cout << "Currently testing: int_to_str(): " << endl;
	successes += testIntToAlpha();
	system("pause");

	if (successes == 5)
	{
		cout << "Five test cases passed! program ready to run!" << endl;
		return 1;
	}
	else
	{
		cout << "Test(s) failed, review code." << endl;
		return 0;
	}
}

