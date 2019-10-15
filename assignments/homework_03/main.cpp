/**
Homework 3
Jeff Reeve
10/14/2019
 */
#include "ListStack.h"    // include our stack definition
#include <fstream>        
#include <iostream>
#include <string>

using namespace std;

int main() {
	ifstream fin("animals.txt");  // input file of animal info                   
	Animal *a;                    // animal pointer used to hold popped animals
	ListStack LS;                 // List based stack object
	string name;
	double weight, scary;

	// While still animals in the file
	while (!fin.eof()) {
		fin >> name >> weight >> scary;		  // load file data
		a = new Animal(name, weight, scary);  // load a new animal with file data
		LS.Push(a);                           // push animal onto the stack
	}


	LS.Print();             // Print the stack

	cout << endl;           // ummm
	cout << endl;           // ummm


	a = LS.Pop();           // get animal off top of stack

	//cout << a << endl;    // print animal (cout operator overloaded)

	a = LS.Pop();			// get animal off top of stack again

	//cout << a << endl;    // print animal (cout operator overloaded)

LS.Print();					// print the stack

system("pause");
return 0;
}
