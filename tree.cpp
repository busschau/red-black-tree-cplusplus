/* Abe Busschau -- busschau@pdx.edu -- Progam #3 
 *
 * 11/17/25
 *
 * This program runs a virtual race between different types of racers!!
 * The types of racers can be a child, monster, or bear! These racers are stored in a 
 * Red/Black Balanced Tree. The race is ran in the race class.
 *
 * This file holds the implementation of the Node and Tree class. 
*/

#include "tree.h"

/* NODE CLASS */

// Default Constructor
Node::Node(): data(nullptr), left(nullptr), right(nullptr), red(true), parent(nullptr) {}

// Copy Constructor
Node::Node(const Node & src): data(nullptr), left(nullptr), right(nullptr), red(true), parent(nullptr)
{
	data = src.data ? copy(*src.data) : nullptr;
	red = src.red;
}

// Assignment Operator
Node & Node::operator=(const Node & src)
{
	if (this == &src) return *this;

	// If Data, Delete it
	if (data)
		delete data;

	// Copy
	data = src.data ? copy(*src.data) : nullptr;
	red = src.red;

	return *this;
}

// Helps with a deep copy
racer* Node::copy(const racer & src)
{
	// If we are copying a child Racer
	const child* temp = dynamic_cast<const child*>(&src); 
	if (temp) return new child(*temp);

	// If we are copying a Monster Racer
	const monster* temp2 = dynamic_cast<const monster*>(&src);
	if (temp2) return new monster(*temp2);

	// If we are copying a Bear Racer
	const bear* temp3 = dynamic_cast<const bear*>(&src);
        if (temp3) return new bear(*temp3);
	
	// Error, None 
	return nullptr;
}

// Destructor
Node::~Node()
{
	if (data)
	{
		delete data;
		data = nullptr;
	}
}

// Get Left Child
Node *& Node::get_left() { return left; }

// Get Right Child
Node *& Node::get_right() { return right; }

// Get Data
racer *& Node::get_data() { return data; }

// Set Left Child
void Node::set_left(Node *& add) { left = add; }

// Set Right Child
void Node::set_right(Node *& add) { right = add; }

// Set Data
void Node::set_data(racer * add) 
{ 
	if (data)
		delete data;

	// Deep Copy Data
	data = add ? copy(*add) : nullptr; 
}

// Gets Color
bool Node::is_red() const { return red; }

// Sets Color, Red = True, Black = False
void Node::set_red(bool value) { red = value; }

// If we need to go right or not
bool Node::go_right(racer *& src)
{
	if (data->name_compare(src)) return true;
	else return false;
}

// Get Parent
Node * Node::get_parent() { return parent; }

// Set Parent
void Node::set_parent(Node * add) { parent = add; }

//---------------------------------------------------------------------------

// TREE CLASS 

// Default Constructor
tree::tree(): root(nullptr) {}

// Copy Constructor
tree::tree(const tree & src): root(nullptr)
{
	Node * parent = nullptr;
	if (!copy(root, src.root, parent))
		throw underflow_error("Empty Tree!"); // No data in src
}

// Assignment Operator
tree & tree::operator=(const tree & src)
{
	if (this == &src) return *this;

	// Delete Existing Tree
	if (root)
	{
		if (!remove_all(root))
			throw runtime_error("Operation Remove_all Failed!"); // Error Deleting
	}

	// Copy new tree
	Node * parent = nullptr;
	if (!copy(root, src.root, parent))
		throw runtime_error("Operation Copy Tree Failed!"); // Error Deleting
	
	return *this;
}

// Copy RBT, for CC and AO
int tree::copy(Node *& root, Node * src, Node * parent)
{
	// Base Case
	if (!src)
	{
		root = nullptr;
		return 0;
	}

	// Preorder, Copy Node
	root = new Node(*src);
	root->set_parent(parent);

	// Go Left
	int left = copy(root->get_left(), src->get_left(), root);

	// Go Right
	int right = copy(root->get_right(), src->get_right(), root);
		
	return left + right + 1;
}

// Destructor
tree::~tree()
{
	if (root)
	{
		if (!remove_all(root))
			cout << "\n\nError Deleting Tree!\n" << endl; // Error Deleteing
	}
	root = nullptr;
}

// Remove Entire tree (Wrapper)
int tree::remove_all()
{
	if (!root) throw underflow_error("Empty Tree!");

	return remove_all(root);
}

// Remove All (Recursive)
int tree::remove_all(Node *& root)
{
	if (!root) return 1;

	// Go Left
	int left = remove_all(root->get_left());

	// Go right 
	int right = remove_all(root->get_right());

	// Post Order
	delete root;
	root = nullptr;

	return left + right;
}

// Removes List without messages back
void tree::remove_quiet()
{
	if (!root) return;

	if (remove_all(root)) return;
	return;
}

// Display Tree (Wrapper)
int tree::display() const
{
	if (!root) throw underflow_error("Empty Tree!"); // No Data

	return display(root);
}

// Display (Recursive)
int tree::display(Node * root) const
{
	if (!root) return 1;

	// Go Left
	int left = display(root->get_left());

	if (!root->get_data()->display())
		return 0; // Error Displaying

	cout << "Node Color: " << (root->is_red() ? "Red\n" : "Black\n") << endl;

	// Go Right
	int right = display(root->get_right());

	return left + right;
}

// Insert a Racer (Wrapper)
int tree::insert(racer *& to_add)
{
	// Empty Tree, Case 1
	if (!root)
	{
		root = new Node;
		root->set_data(to_add);
		root->set_red(false);
		return 1;
	}

	Node * recent{nullptr}; // Node that gets added
	Node * parent{nullptr}; // Link Parent Node

	// Get Node we inserted to Fix the tree
	recent = insert(root, parent, to_add);

	// Fix the violations we made inserting
	return fix(recent);
}

// Inster a Racer (Recursive)
Node *& tree::insert(Node *& root, Node * parent, racer *& to_add)
{
	// Add end of List
	if (!root)
	{
		root = new Node;
		root->set_data(to_add);
		root->set_parent(parent);
		return root;
	}

	// Update Parent
	parent = root;

	// Go Right
	if (root->go_right(to_add))
		return insert(root->get_right(), parent, to_add);
	// Go Left
	else
		return insert(root->get_left(), parent, to_add);
}

// Rotate Sub-Tree Left
void tree::rotate_left(Node * parent)
{
	// We are nullptr
	if (!parent) return;

	// Get Right, new subtree root
	Node * temp = parent->get_right();

	// No right child
	if (!temp) return;

	parent->set_right(temp->get_left());

	// Update Parent
	if (temp->get_left())
		temp->get_left()->set_parent(parent);

	// Update Parent
	temp->set_parent(parent->get_parent());

	// Root Case, Attatch grandparent
	if (!parent->get_parent())
		root = temp;
	else if (parent == parent->get_parent()->get_left())
		parent->get_parent()->set_left(temp);
	else
		parent->get_parent()->set_right(temp);

	// Final, parent becomes left child of temp
	temp->set_left(parent);
	parent->set_parent(temp);
}

// Rotate Sub-Tree Right
void tree::rotate_right(Node * parent)
{
	// We are nullptr
	if (!parent) return;

	// Get Left, new subtree root
	Node * temp = parent->get_left();

	// No Left Child
	if (!temp) return;


	parent->set_left(temp->get_right());

	// Update temp parent
	if (temp->get_right())
		temp->get_right()->set_parent(parent);

	temp->set_parent(parent->get_parent());

	// Root case, attatch grandparent
	if (!parent->get_parent())
		root = temp;
	else if (parent == parent->get_parent()->get_right())
		parent->get_parent()->set_right(temp);
	else
		parent->get_parent()->set_left(temp);

	// Final, parent becomes right child of temp
	temp->set_right(parent);
	parent->set_parent(temp);
}

// Function to fix the RED/BLACK tree violations
int tree::fix(Node *& current)
{
	// Base Case, If we are root or parent is black, nothing to do
	if (current == root || !current->get_parent() || !current->get_parent()->is_red())
	{
		root->set_red(false);
		return 1;
	}

	// If Uncle the right side of Grandparent
	if (current->get_parent() == current->get_parent()->get_parent()->get_left())
	{
		// Get our uncle
		Node * uncle = current->get_parent()->get_parent()->get_right();

		// Check Color, Red: Change colors around
		if (uncle && uncle->is_red())
		{
			// Set Parent and Uncle to Black
			current->get_parent()->set_red(false);
			uncle->set_red(false);

			// Set Grandparent to Red
			current->get_parent()->get_parent()->set_red(true);

			// Move up the tree
			current = current->get_parent()->get_parent();

			// Recurse
			return fix(current);
		}

		// Color Black, Rotations and color changes
		else
		{
			// Rotate Left if we right child
			if (current == current->get_parent()->get_right())
			{
				current = current->get_parent();
				rotate_left(current);
			}

			// Recolor
			current->get_parent()->set_red(false);
			current->get_parent()->get_parent()->set_red(true);

			// Rotate Right
			rotate_right(current->get_parent()->get_parent());

			// Recurse
			return fix(current);
		}
	}

	// Uncle on left side
	else
	{
		// Get Uncle
		Node * uncle = current->get_parent()->get_parent()->get_left();

		// Check Uncle Color, Red: Change colors
		if (uncle && uncle->is_red())
		{
			// Uncle/Parent to Black
			current->get_parent()->set_red(false);
			uncle->set_red(false);

			// Grandparent to Red
			current->get_parent()->get_parent()->set_red(true);

			current = current->get_parent()->get_parent();

			// Done, Move up
			return fix(current);
		}

		// Uncle Black, Rotations and Recolors
		else
		{
			// If Current is left child
			if (current == current->get_parent()->get_left())
			{
				current = current->get_parent();
				rotate_right(current);
			}

			// Set Colors
			current->get_parent()->set_red(false);
			current->get_parent()->get_parent()->set_red(true);

			rotate_left(current->get_parent()->get_parent());

			// Recurse, Move up
			return fix(current);
		}
	}
}

// Move all Racers
int tree::move()
{
	// No Data
	if (!root) throw underflow_error("Empty Tree!");

	return move(root);
}

// Move (Recursive)
int tree::move(Node * root)
{
	if (!root) return 1;

	// Doing In-order Traversal
	int left = move(root->get_left());

	// Move Racer, Throw if couldn't move
	if (!root->get_data()->move())
		throw runtime_error("Operation Move Racer Failed!");

	int right = move(root->get_right());

	return left + right;
}

// Placement Check (Wrapper)
int tree::place_check(int target) const
{
	if (!root) throw underflow_error("Empty Tree!");

	return place_check(root, target);
}

// Placement Check (Recursive)
int tree::place_check(Node * root, int target) const
{
	if (!root) return 0;

	// Flag
	int i {};

	// Doing In-order Traversal
	int left = place_check(root->get_left(), target);

	// Check if racer won
	if (root->get_data()->place_check(target))
		++i;

	int right = place_check(root->get_right(), target);

	return left + right + i;
}

// Make All Racers take a Break (Wrapper)
int tree::stop()
{
	if (!root) throw underflow_error("Empty Tree!");

	return stop(root);
}

// Make All Racers take a Break (Recursive)
int tree::stop(Node * root)
{
	if (!root) return 1;

	// Doing In-order Traversal
	int left = stop(root->get_left());

	// Make Racers take a break
	if (!root->get_data()->stop())
		throw runtime_error("Operation Stop Racers Failed!");

	int right = stop(root->get_right());

	return left + right;
}

// See if any racers gained or lost motivation (Wrapper)
int tree::motivation()
{
	if (!root) throw underflow_error("Empty Tree!");

	return motivation(root);
}

// See if any racers gained or lost motivation (Recursive)
int tree::motivation(Node * root)
{
	// Base Case
	if (!root) return 1;

	// Doing In-order Traversal
	int left = motivation(root->get_left());

	// See what racers motivation is like
	if (!root->get_data()->motivation())
		throw runtime_error("Operation Motivation Failed!");

	int right = motivation(root->get_right());

	return left + right;
}

// See if Any bears catch a snack (Wrapper & RTTI)
int tree::snack()
{
	if (!root) throw underflow_error("Empty Tree!");

	return snack(root);
}

// See if Any bears catch a snack (Recursive & RTTI)
int tree::snack(Node * root)
{
	if (!root) return 0;

	// Flag
	int i{};

	// Doing In-order Traversal
	int left = snack(root->get_left());

	// See if the bears caught a snack! RTTI & Down Casting
	bear * temp = dynamic_cast<bear*>(root->get_data());
        if (temp)
	{
		if (!temp->snack_break())
			throw runtime_error("Operation Snack Break Failed!");
		++i;
	}
	
	int right = snack(root->get_right());

	return left + right + i;
}
