/* Abe Busschau -- busschau@pdx.edu -- Progam #3
 *
 * 11/17/25
 *
 * This program runs a virtual race between different types of racers!!
 * The types of racers can be a child, monster, or bear! These racers are stored in a 
 * Red/Black Balanced Tree. The race is ran in the race class.
 *
 * This file holds the implementation of the Race Heiarchy. Shows Monster and Bear
*/

#include "tree.h"

/* Monster Class */

// Default Constructor
monster::monster(): fly(0), nap(0) {}

// How the Monster Moves
int monster::move()
{
	// No Data
	if (fly == 0 || nap == 0) throw runtime_error("Missing Data!");

	// Flies this Much
	placement += fly;

	cout << "\n\n" << name << " Flew " << fly << " Steps!\n" << endl;

	return 1;
}

// How the Monster took a nap
int monster::stop()
{
	if (nap == 0) throw runtime_error("Missing Data!");

	// Takse a nap, loses steps	
	if ((placement - nap) <= 0)
		placement = 0;
	else
		placement -= nap;

	cout << "\n\n" << name << "  Took a NAP! Lost " << nap << " Steps!\n" << endl;

	return 1;
}

// If the Monster has any motivation
int monster::motivation()
{
	random_device seed;      
	mt19937 gen(seed());	
	uniform_int_distribution<> range(0, 1); // Random Motivation
	uniform_int_distribution<> range2(1, 3); // Motivation Effect to place

	int effect{range2(gen)};

	// They Gain Motivation
	if (range(gen))
	{
		cout << "\n\n" << name << " Remebered the Prize of a FEAST! Extra Boost!\n" << "Flew " << effect << " Steps!\n" << endl;
		placement += effect;
	}

	// They Lose Motivation
	else
	{
		cout << "\n\n" << name << " Was running on a empty stomach! So hungry they LOST " << effect << " Steps...\n" << endl;
		
		if ((placement - effect) <= 0)
			placement = 0;
		else
			placement -= effect;
	}

	return 1;
}

// Sets Data in the class
int monster::set_data()
{
	// Set Parent Data
	if (racer::set_data())
	{
		// Input Validation
		do{
			cout << "\n\nEnter the amount of steps the Monster can fly per move: ";
			cin >> fly; cin.ignore(100, '\n');

			if (fly <= 0)
				cout << "\n\nMust Be at least one!\n" << endl;
		}while (fly <= 0);

		// Input Validation
		do{
			cout << "\n\nEnter the amount of steps the Monster loses per Nap: ";
			cin >> nap; cin.ignore(100, '\n');

			if (nap <= 0)
				cout << "\n\nMust Be at least one!\n" << endl;
		}while (nap <= 0);

		return 1;
	}

	else return 0;
}

// Displays All Data
int monster::display()
{
	if (fly == 0 || nap == 0) throw runtime_error("Missing Data!");

	// Display Parent
	if (racer::display())
	{
		cout << "Steps Per Fly: " << fly << "\nSteps Lost per Nap: " << nap << "\n" << endl;
		return 1;
	}
	else return 0;
}

//--------------------------------------------------------------------------------------------------

/* Bear Class */

// Default Constructor
bear::bear(): crawl(0), snack(0) {}

// How the Bear Moves
int bear::move()
{
	// No Data
	if (crawl == 0 || snack == 0) throw runtime_error("Missing Data!");

	// Crawls this Much
	placement += crawl;

	cout << "\n\n" << name << "  Crawled " << crawl << " Steps!\n" << endl;

	return 1;
}

// When the bear goes for a snack break
int bear::stop()
{
	if (snack == 0) throw runtime_error("Missing Data!");

	// Goes for a Snack Break, loses steps
	
	if ((placement - snack) <= 0)
		placement = 0;
	else
		placement -= snack;

	cout << "\n\n" << name << "  went for a Snack Break! Lost " << snack << " Steps!\n" << endl;

	return 1;
}

// When the Bear Gets motivation
int bear::motivation()
{
	random_device seed;      
	mt19937 gen(seed());	
	uniform_int_distribution<> range(0, 1); // Random Motivation
	uniform_int_distribution<> range2(1, 3); // Motivation Effect to place

	int effect{range2(gen)};

	// They Gain Motivation
	if (range(gen))
	{
		cout << "\n\n" << name << " Remebered his Family is at the Finish Line! Extra Boost!\n" << "Crawled " << effect << " Steps!\n" << endl;
		placement += effect;
	}

	// They Lose Motivation
	else
	{
		cout << "\n\n" << name << " Reflected on how he had no family. So sad they LOST " << effect << " Steps...\n" << endl;
		
		if ((placement - effect) <= 0)
			placement = 0;
		else
			placement -= effect;
	}

	return 1;
}

// RTTI Function, Another Random if the bear got a snack or not
int bear::snack_break()
{
	random_device seed;      
	mt19937 gen(seed());	
	uniform_int_distribution<> range(0, 1); // Random Snack or not
	uniform_int_distribution<> range2(1, 3); // Motivation Effect to place

	int effect{range2(gen)};

	// They Catch a Fish
	if (range(gen))
	{
		cout << "\n\n" << name << " Actually Caught a Salmon During their Snack Break! Extra Energy!!\n" << "Crawled " << effect << " Steps!\n" << endl;
		placement += effect;
	}

	// They Don't Catch a Fish
	else
	{
		cout << "\n\n" << name << " Didn't Catch any fish on their break, So tired they LOST " << effect << " Steps...\n" << endl;
		
		if ((placement - effect) <= 0)
			placement = 0;
		else
			placement -= effect;
	}

	return 1;
}

// Sets Data in Class
int bear::set_data()
{
	// Set Parent Data
	if (racer::set_data())
	{
		// Input Validation
		do{
			cout << "\n\nEnter the amount of steps the Bear can crawl per move: ";
			cin >> crawl; cin.ignore(100, '\n');

			if (crawl <= 0)
				cout << "\n\nMust Be at least one!\n" << endl;
		}while (crawl <= 0);

		// Input Validation
		do{
			cout << "\n\nEnter the amount of steps the bear loses per Snack break: ";
			cin >> snack; cin.ignore(100, '\n');

			if (snack <= 0)
				cout << "\n\nMust Be at least one!\n" << endl;
		}while (snack <= 0);

		return 1;
	}

	else return 0;
}

// Displays Data
int bear::display()
{
	if (crawl == 0 || snack == 0) throw runtime_error("Missing Data!");

	// Display Parent
	if (racer::display())
	{
		cout << "Steps Per Crawl: " << crawl << "\nSteps Lost per Snack Break: " << snack << "\n" << endl;
		return 1;
	}
	else return 0;
}
