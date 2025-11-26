/* Abe Busschau -- busschau@pdx.edu -- Progam #3 
 *
 * 11/17/25
 *
 * This program runs a virtual race between different types of racers!!
 * The types of racers can be a child, monster, or bear! These racers are stored in a 
 * Red/Black Balanced Tree. The race is ran in the race class.
 *
 * This file will hold the implementation of the race class.
 * This is where the actual race will be ran and all the functions for that.
*/

#include "tree.h"

// Default Constructor
race::race() {}


// Welcome Function
void race::welcome()
{
	cout << "\n\nWelcome to THE RACE! Please Start by entering in some racers and "
	     << "\nfinalizing all the people! After that, we will start the race!!\n" << endl;
}

// Menu To choose what to do 
int race::menu()
{
	int choice{}; // Choice the User Makes

	cout << "\n\nRacer Menu:\n\t1. Add Racer\n\t2. Display Racer(s)\n\t3. Remove All Racer(s)\n\t4. Quit";

	// Input Validation
	do{
		cout << "\nEnter (1 - 4): ";
		cin >> choice; cin.ignore(100, '\n');

		if (choice <= 0 || choice >= 5)
			cout << "\n\nAnswer Must be between One and Four!\n" << endl;
	} while (choice <= 0 || choice >= 5);

	return choice;
}

// Menu to Change Racer Pool
int race::change_racer()
{
	int choice{}; // Choice of User

	while (choice != 4)
	{
		// Get Choice
		choice = menu();

		// Add Racer
		if (choice == 1)
		{
			// Input Validation
			do{
				cout << "\n\nWhat Type of Racer to add:\n\t1. Child\n\t2. Monster\n\t3. Bear\nEnter: ";
				cin >> choice; cin.ignore(100, '\n');

				if (choice < 1 || choice > 3)
					cout << "\n\nMust Enter Between 1 and 3!\n" << endl;
			}while(choice < 1 || choice > 3);

			// Add Racer
			racer * object{nullptr};

			// Child
			if (choice == 1)
			{
				object = new child;

				// Set The Data
				if (object->set_data())
				{
					if (pool.insert(object))
						cout << "\n\nRacer Added!\n" << endl;
				}

				else
					cout << "\n\nError Setting Data!\n" << endl;
				
			}

			// Monster
			else if (choice == 2)
			{
				object = new monster;

				// Set The Data
				if (object->set_data())
				{
					// Add Data to Tree
					if (pool.insert(object))
						cout << "\n\nRacer Added!\n" << endl;
				}

				else
					cout << "\n\nError Setting Data!\n" << endl;
			}

			// Bear
			else if (choice == 3)
			{
				object = new bear;

				// Set The Data
				if (object->set_data())
				{
					// Add Data to Tree
					if (pool.insert(object))
						cout << "\n\nRacer Added!\n" << endl;
				}

				else
					cout << "\n\nError Setting Data!\n" << endl;
			}

			// Bad Error
			else
			{
				cout << "\n\nError Adding Data, Ending Race...\n" << endl;
				choice = 4;
			}

			// Delete Data Used to Insert
			delete object;
		}

		// Display All Racers
		else if (choice == 2)
		{
			// Try For Display
			try{
				// Display racers
				if (!pool.display())
					cout << "\n\nError Displaying Racer's!\n" << endl;
			}

			// Catch for Empty Data
			catch(const exception& error)
			{
				cout << "\n\n" << error.what() << "\n" << endl;
			}

		}

		// Remove All Racers
		else if (choice == 3)
		{
			// Try For Remove All
			try{
				// Remove All Racers
				if (!pool.remove_all())
					cout << "\n\nRacer Pool Empty!\n" << endl;
				else
					cout << "\n\nRacer Pool Now Empty!\n" << endl;
			}

			// Catch for Empty Data
			catch(const exception& error)
			{
				cout << "\n\n" << error.what() << "\n" << endl;
			}
		}

		// Chose to Quit
		else
			cout << "\n\nExiting Race Edit...\n" << endl;
	}
	return 1;
}

// Runs the race
int race::run_race()
{
	int choice{}; // Choice of the user in what they want to do with the race
	int won{}; // If a Racer Won the race
	int target{50}; // The Amount a racer needs to win


	// Welcome Message
	welcome();

	// Edit Racer Pool	
	if (change_racer())
		cout << "\n\nNow Starting Race!\n" << endl;
	else 
	{
		cout << "\n\nError Adding racer(s), ending Race...\n" << endl;
		choice = -1;
	}

	// Race Loop, How the race is ran. Either the choose to quit or someone wins the race
	while (choice != -1 && !won)
	{
		// Always Try every Function
		try{
			// Step 1, Racers Move!
			cout << "\n\n----------------------------------"
			     << "\n\nRacer(s) Moving!\n" << endl;

			if (pool.move())
			{
				cout << "\n\nSee how the racers moved!\n" << endl;
				cout << "\n\n----------------------------------------";
			}

			// See if any racers won
			if (pool.place_check(target))
			{
				cout << "\n\nRace Ending... See above for the Winners!\n" << endl;
				++won;
			}

			// If someone won the race, quit all
			if (!won)
			{
				// Step 2, Racers take a break
				cout << "\n\nRacer(s) Taking a Break!\n" << endl;
				if (pool.stop())
				{
					cout << "\n\nLook Above to see who take a break!\n" << endl;	
					cout << "\n\n-----------------------------------------";
				}
			
				// Step 3, See if any bears caught a snack on the break
				if (pool.snack())
				{
					cout << "\n\nLook above to see how the Bear racer(s) did on their break!\n" << endl;
					cout << "\n\n-----------------------------------------";
				}

				// See if any bears won
				if (pool.place_check(target))
				{
					cout << "\n\nRace Ending... See above for the Winners!\n" << endl;
					++won;
				}
			
				// If any bears won, stop	
				if (!won)
				{
					// Step 4, See if any racers got motivation or lost any
					cout << "\n\nRacer(s) Gaining or Losing Motivation!\n" << endl;
					if (pool.motivation())
					{
						cout <<	"\n\nLook Above to see who lost and gain Motivation!\n" << endl;
						cout << "\n\n-----------------------------------------";
					}
					
					// See if any racers won
					if (pool.place_check(target))
					{
						cout << "\n\nRace Ending... See above for the Winners!\n" << endl;
						++won;
					}

					// If Any racer won off of motivation, stop
					if (!won)
					{
						// Step 5
						// Ask if the user want to go to next leg of race or quit the whole race
					
						do{
							cout << "\n\nQuit race or continue?\n\t-1. Quit\n\t 1. Continue\nEnter: ";
							cin >> choice; cin.ignore(100,'\n');

							if (choice != -1 && choice != 1)
								cout << "\n\nMust Enter 1 or -1!\n" << endl;
						}while(choice != -1 && choice != 1);
					}
				}
			}
		}

		// Catch for Empty Data or Other Errors
		catch(const exception& error)
		{
			cout << "\n\n" << error.what() << "\n" << endl;
			choice = -1;
		}
	}

	// Silently Delete racer pool so it is empty if the run the race again
	pool.remove_quiet();

	// -1 if they chose to quit early, otherwise someone won!
	if (choice == -1) return 0;
	else return 1;
}
