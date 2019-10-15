/**
Homework 4
Jeff Reeve
10/14/2019
 */
#include <iostream>
#include <fstream>
#include "ListQueue.hpp"
#include <string>

using namespace std;


int main() {

	ifstream fin("animals.txt");  // input file of animal info

	Animal *a;                    // animal pointer used to hold popped animals

	string name;
	double weight, scary;

	ListQueue LQ;                 // Queue instance 


	while (!fin.eof()) {        // Load file values onto the queue
		fin >> name >> weight >> scary;		  // load file data
		a = new Animal(name, weight, scary);  // load a new animal with file data
		LQ.Push(a);                           // push animal onto the stack
	}

	cout << endl;                     

	LQ.Print();                     // print queue to see where values are


	for (int i = 0; i < 3; i++) {           // remove 3 items
		if (!LQ.Empty()) {
			Animal* t = LQ.Pop();
			cout << "Item removed: " << t->name << endl;    // print out items
		}
		else {
			cout << "Empty queue!" << endl;
		}

	}

	cout << endl;
	LQ.Print();                     // print again to show front removal
	LQ.PrintPointers();
	
	system("pause");
	return 0;
}

