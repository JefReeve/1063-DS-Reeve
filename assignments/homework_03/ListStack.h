/**
Homework 3
Jeff Reeve
10/14/2019
 */
#include <iostream>

using namespace std;

/**
 * Animal Type
 */
struct Animal {
	string name;
	double weight;
	double scary;

	// Default constructor
	Animal() {
		name = "";
		weight = 0.0;
		scary = 99.0;
	}

	// overloaded constructor
	Animal(string tempName, double tempWeight, double tempScary) {
		name = tempName;
		weight = tempWeight;
		scary = tempScary;
	}
};

// Overload "<<" operator for animals
//ostream &operator<<(ostream &, const Animal *);

/**
 * Node type.
 *
 * We seperate Animal from Node so we can return an "Animal"
 * when we pop the stack, and don't have to return a "node"
 */
struct Node {
	Animal *A;
	Node *Next;

	// Needs a default constructor

	Node(Animal *a) {
		A = a;
		Next = NULL;
	}
};

/**
 * ListStack
 *
 * List based stack implementation
 *
 */
class ListStack {
private:
	Node *Top;

public:
	ListStack();          // constructor
	void Push(Animal *);  // stack gets Animals
	Animal *Pop();        // Pop returns top animal
	void Print();         // print stack for debugging
};
