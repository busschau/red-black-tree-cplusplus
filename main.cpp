/* Abe Busschau -- busschau@pdx.edu -- Progam #3
 *
 * 11/17/25
 *
 * This program runs a virtual race between different types of racers!!
 * The types of racers can be a child, monster, or bear! These racers are stored in a 
 * Red/Black Balanced Tree. The race is ran in the race class.
 *
 * This file is where Main is stored. This is where the program will start and 
 * call the needed functions
*/

#include "tree.h"

int main()
{
	int choice{}; // If they want to run the race again
	race course; // The race

	// Run Race as many times as wanted
	while (choice != 2)
	{
		// Run Race
		if (course.run_race())
			cout << "\n\nCongrats on the Successful Race!\n" << endl;
		else
			cout << "\n\nRace Ended Early, Better Luck Next Time!\n" << endl;

		// Input Validation
		do {
			// Race Again?
			cout << "\n\nWould You like to run a brand new race again?"
			     << "\n\t1. Yes\n\t2. No\nEnter (1 or 2): ";
			cin >> choice; cin.ignore(100, '\n');

			if (choice != 1 && choice != 2)
				cout << "\n\nMust Enter One or Two!\n" << endl;
		}while (choice != 1 && choice != 2);
	}

	return 0;
}
