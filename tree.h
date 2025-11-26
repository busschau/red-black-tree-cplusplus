/* Abe Busschau -- busschau@pdx.edu -- Progam #3
 *
 * 11/17/25
 *
 * This program runs a virtual race between different types of racers!!
 * The types of racers can be a child, monster, or bear! These racers are stored in a 
 * Red/Black Balanced Tree. The race is ran in the race class.
 *
 * This File is the header file for the these 3 classes: Red/Black tree and it's Node's.
 * Also the class that runs the race
 * Please see the prototypes down below
*/

#include "race.h"

/* NODE CLASS Red/Black */
class Node
{
	public:
		Node(); // Default Constructor
		Node(const Node &); // Copy Constructor
		Node & operator=(const Node &); // Assignment Operator
		racer* copy(const racer & src); // Helps with deep copy of node data
		~Node(); // Destructor

		Node *& get_left(); // Get Left Child
		Node *& get_right(); // Get Right Child
		racer *& get_data(); // Get Data

		void set_left(Node *& add); // Set Left Child
		void set_right(Node *& add); // Set Right Child
		void set_data(racer * add); // Set Data

		Node * get_parent(); // Get Parent 
		void set_parent(Node * add); // Set Parent 

		bool is_red() const; // Gets color
		void set_red(bool value); // Sets Color
		bool go_right(racer *& src); // If we need to go right of the tree or not

	protected:
		racer * data; // Data
		Node * left; // Left Child
		Node * right; // Right Child
		bool red; // True = red, False = black
		Node * parent; // Parent Pointer
};

//-----------------------------------------------------------------------------

// Tree Class
class tree
{
	public:
		tree(); // Default Constructor
		tree(const tree &); // Copy Constructor
		tree & operator=(const tree & src); // Assignment Operator
		~tree(); // Destructor

		int insert(racer *& to_add); // Add a Racer
		int display() const; // Display Tree
		int remove_all(); // Remove Entire tree
		void remove_quiet(); // Removes list without messages back
				  
		int move(); // Move All Racers
		int place_check(int target) const; // Placement Check
		int stop(); // Make all racers take a break
		int motivation(); // See if any racers gained or lost motivation
		int snack(); // See if any bears get a snack!

	protected:
		Node * root; // Holds the Tree

		int copy(Node *& root, Node * src, Node * parent); // For Copy Constructor and AO
		Node *& insert(Node *& root, Node * parent, racer *& to_add); // recursive Insert
		int display(Node * root) const; // Recursive display
		int remove_all(Node *& root); // Recursive Delete All

		int fix(Node *& current); // Fix the damage done from insert
		void rotate_left(Node * parent); // Rotate the sub-tree left
		void rotate_right(Node * parent); // Rotate the sub-tree right

		int move(Node * root); // Recursive Move
		int place_check(Node * root, int target) const; // Recursive Placement Check
		int stop(Node * root); // Make all racers take a break
		int motivation(Node * root); // Recursive, See if any racers gained or lost motivation
		int snack(Node * root); // Recursive, See if any bears get a snack!
};

//----------------------------------------------------------------------------------------
// Class that runs the race
class race
{
	public:
		race(); // Default Constructor
		void welcome(); // Welcome Function
		int run_race(); // Runs the race
		
	protected:
		tree pool; // The Pool of racers running the race
		int change_racer(); // The Menu to change the racer pool if wanted
		int menu(); // Returns the option the user wants to do
};


//--------------------------------------------------------------------------------
