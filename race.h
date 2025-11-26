/* Abe Busschau -- busschau@pdx.edu -- Progam #3 
 *
 * 11/17/25
 *
 * This program runs a virtual race between different types of racers!!
 * The types of racers can be a child, monster, or bear! These racers are stored in a 
 * Red/Black Balanced Tree. The race is ran in the race class.
 *
 * This File is the header file for the these 4 classes: Racer(Base), child, monster, and
 * bear. Please see the prototypes down below
*/

#include <iostream>
#include <string>
#include <random>
#include <array>
#include <stdexcept>

using namespace std;

// Base Class! Racer Commons
class racer
{
	public:
		racer(); // Default Constructor
		virtual ~racer(); // Virtual Destructor
		virtual int move() = 0; // My Pure virtual Function
		virtual int stop(); // How the Racer takes a "break"
		virtual int motivation(); // If the racer has motivation from friends or family!

		virtual int set_data(); // Sets Data in class
		virtual int display(); // Displays Data

		bool place_check(int win); // Returns if they are past the winning placement
		bool name_compare(const racer * src) const; // Decides where it should go in the tree

	protected:
		string name; // Name of Racer
		int id; // ID tag of the racer
		int placement; // Place they are in the race
};


// Derived, Child! Child Racer
class child : public racer
{
	public:
		child(); // Default Constructor
		int move(); // How the Racer Moves
		int stop(); // How the Racer takes a "break"
		int motivation(); // If the racer has motivation from friends or family!

		int set_data(); // Sets Data in class
		int display(); // Displays Data

	protected:
		int run; // Child Runs/walks
		int rest; // Child Takes a quick break before going again
};

// Derived, Monster! Monster Racer
class monster : public racer
{
	public:
		monster(); // Default Constructor
		int move(); // How the Racer Moves
		int stop(); // How the Racer takes a "break"
		int motivation(); // If the racer has motivation from friends or family!

		int set_data(); // Sets Data in class
		int display(); // Displays Data
			      
	protected:
		int fly; // Monster Flies during the race!!
		int nap; // Has to take a good nap though
};

// Derived, Bear! Bear Racer
class bear : public racer
{
	public:
		bear(); // Default Constructor
		int move(); // How the Racer Moves
		int stop(); // How the Racer takes a "break"
		int motivation(); // If the racer has motivation from friends or family!
		int snack_break(); // If the bear caught a snack, gets extra boost if he does!! RTTI Function

		int set_data(); // Sets Data in class
		int display(); // Displays Data

	protected:
		int crawl; // Bear Crawl to be specific!
		int snack; // Bear's need their snack breaks!
};


