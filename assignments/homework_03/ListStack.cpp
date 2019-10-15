#include "ListStack.h"
#include <iostream>
#include <string>

using namespace std;

/**
 * ListStack
 * Purpose:
 *     constructs the object
 * Params:
 *     void
 * Returns:
 *     void
 */
ListStack::ListStack() {
	Top = NULL;
}

/**
 * Push
 * Purpose:
 *     Adds an animal to the top of stack
 * Params:
 *     Animal* A : an animal type
 * Returns:
 *     void
 */
void ListStack::Push(Animal *A) {
	// allocate new memory
	Node *anode = new Node(A);      // Allocate new memory

	// check if list is empty
	if (!Top) {
		Top = anode;                // If empty stack just point to new node
	}
	else {
		anode->Next = Top;          // Link new node by point its next to old top
		Top = anode;                // Now update top to point to the new node
	}
}

/**
 * Pop
 * Purpose:
 *     Removes an item from top of stack
 * Params:
 *     void
 * Returns:
 *     Animal* : top animal
 */
Animal *ListStack::Pop() {
	if (!Top) {
		return NULL;        // Return NULL for empty stack
	}
	else {
		Node *Temp = Top;   // Point to top with temp pointer

		Animal *a = Top->A; // Pull animal out of top (to return)

		Top = Top->Next;    // Move top of stack 

		delete Temp;        // Delete old top node

		return a;           // Return our animal
	}
}


/**
 * Print
 * Purpose:
 *     Print for debugging purposes
 * Params:
 *     void
 * Returns:
 *     void
 */
void ListStack::Print() {
	Node *Temp = Top;

	while (Temp != NULL) {
		cout << Temp->A->name << " \nWeight: " << Temp->A->weight
			<< " Scariness: " << Temp->A->scary << endl;
		Temp = Temp->Next;
	}
}
