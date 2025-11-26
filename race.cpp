/* Abe Busschau -- busschau@pdx.edu -- Progam #3 
 *
 * 11/17/25
 *
 * This program runs a virtual race between different types of racers!!
 * The types of racers can be a child, monster, or bear! These racers are stored in a 
 * Red/Black Balanced Tree. The race is ran in the race class.
 *
 * This file holds the implementation of the Race Heiarchy. Shows Racer, child
*/

#include "tree.h"

/* Racer Class */

// Default Constructor
racer::racer() : id(0), placement(0) {}

// Virtual Destructor
racer::~racer()
{
	name.clear();
	id = 0;
	placement = 0;
}


// Decides where it should go in the list, True if right of tree
bool racer::name_compare(const racer * src) const
{
	if (name <= src->name) return true;
	else return false;
}

// Returns True if they won the race
bool racer::place_check(int win)
{
	if (win <= placement)
	{
		cout << "\n\n" << name << " Won the Race!\n" << endl;
		return true;
	}
	else return false;
}

// Break of the racer
int racer::stop()
{
	cout << "\n\nSomeone is Taking a break!\n" << endl;

	// This Function should never be called
	throw logic_error("Called Base Stop()"); return -1;
}

// Sends Motivation
int racer::motivation()
{
	cout << "\n\nSomeone is Getting Motivation!\n" << endl;

	// Funciton Should not be getting called
	throw logic_error("Called Base Motivation()"); return -1;
}

// Sets Data in the class
int racer::set_data()
{
	cout << "\n\nEnter Name of Racer: ";
	getline(cin, name);

	// Input Validation
	do{ 
		cout << "\nEnter ID of Racer: ";
		cin >> id; cin.ignore(100,'\n');

		if (id <= 0)
			cout << "\n\nID Must be above Zero!\n" << endl;
	}while (id <= 0);

	return 1;
}

// Displays Data
int racer::display()
{
	cout << "\n\nName: " << name << "\nID: " << id << "\nCurrent Placement: " << placement << endl;
	return 1;
}

//------------------------------------------------------------------------

/* Child Racer */

// Default Constructor
child::child(): run(0), rest(0) {}

// How the Child Moves
int child::move()
{
	// No Data
	if (run == 0 || rest == 0) throw runtime_error("Missing Data!");

	// Runs this Much
	placement += run;

	cout << "\n\n" << name << " Ran " << run << " Steps!\n" << endl;

	return 1;
}

// How The Child taks a break
int child::stop()
{
	if (rest == 0) throw runtime_error("Missing Data!");

	// Takse a break, loses steps
	if ((placement - rest) <= 0)
		placement = 0;
	else
		placement -= rest;

	cout << "\n\n" << name << "  took a break! Lost " << rest << " Steps!\n" << endl;

	return 1;
}

// If the racer gets motivation
int child::motivation()
{
	random_device seed;      
	mt19937 gen(seed());	
	uniform_int_distribution<> range(0, 1); // Random Motivation
	uniform_int_distribution<> range2(1, 3); // Motivation Effect to place

	int effect{range2(gen)};

	// They Get Motivation
	if (range(gen))
	{
		cout << "\n\n" << name << " Saw Their Parents! Extra Boost!\n" << "Moved " << effect << " Steps!\n" << endl;
		placement += effect;
	}

	// They Lose Motivation
	else
	{
		cout << "\n\n" << name << " Saw Nobody today :( So sad they lost " << effect << " Steps...\n" << endl;
		
		if ((placement - effect) <= 0)
			placement = 0;
		else
			placement -= effect;
	}

	return 1;
}

// Sets Data in Class
int child::set_data()
{
	// Set Parent Data
	if (racer::set_data())
	{
		// Input Validation
		do{
			cout << "\n\nEnter the amount of steps the child can walk per move: ";
			cin >> run; cin.ignore(100, '\n');

			if (run <= 0)
				cout << "\n\nMust Be at least one!\n" << endl;
		}while (run <= 0);

		// Input Validation
		do{
			cout << "\n\nEnter the amount of steps the child loses per break: ";
			cin >> rest; cin.ignore(100, '\n');

			if (rest <= 0)
				cout << "\n\nMust Be at least one!\n" << endl;
		}while (rest <= 0);

		return 1;
	}

	else return 0;
}

// Displays Data
int child::display()
{
	if (run == 0 || rest == 0) throw runtime_error("Missing Data!");

	// Display Parent
	if (racer::display())
	{
		cout << "Steps Per Move: " << run << "\nSteps Lost per Break: " << rest << "\n" << endl;
		return 1;
	}
	else return 0;
}
