//Jeff Reeve
//10/8/2019

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class stack {
private:
	int *A;
	int Top;
	int Size;
	bool enlarged;
	int largest;
public:

	/*
	stack constructor: initializes array of ints and sets top
	*/
	stack() {
		Size = 100;
		A = new int[Size];
		Top = 0;
		enlarged = false;
		largest = Size;
	}

	/*
	constructor: initializes to specified size and sets top
	paramaters: s = int size
	*/
	stack(int s) {
		Size = s;
		A = new int[Size];
		Top = -1;
		enlarged = false;
		largest = Size;
	}

	/*
	GetNum method: gets the number at an index
	Paramaters: int i : index to return
	Returns: int: number at index
	*/
	int getNum(int i) {
		return A[i];
	}

	/*
	GetTop method: get the top number
	Paramaters: void
	Returns: int: top index of array
	*/
	int getTop() {
		return Top;
	}

	/*
	GetSize method: get the size
	Paramaters: void
	Returns: int: size of array
	*/
	int getSize() {
		return Size;
	}

	/*
	GetLargest method: get the largest size of the array
	Paramaters: void
	Returns: int: largest size of array
	*/
	int getLargest() {
		return largest;
	}

	/*
	Push method: adds item to top of stack
	Paramaters: int val: integer size
	Returns: bool: true = success
	*/
	bool Push(int val) {
			Top++;
			A[Top] = val;
			checkResize(false);
			cout << " *** " << Top << " *** ";
			return true;
	}

	/*
	Pop fucntion: removes top of stack and returns it
	Paramaters: void
	Returns: int: item removed from stack
	*/
	int Pop() {
		if (!Empty()) {
			int temp = 0;
			temp = A[Top];
			Top--;
			checkResize(true);
			return temp;
		}
		else {
			cout << "Cannot remove item from empy stack\n";
		}
		return 0;
	}

	/*
	Print method: prints stack
	Paramaters: void
	Returns: void
	*/
	void Print() {
		cout << "\n-------\n";
		for (int i = Top; i >= 0; i--) {
			cout << A[i] << endl;
		}
	}

	/*
	Empty method: checks for empty stack
	Paramaters: void
	Returns: bool: true = empty stack
	*/
	bool Empty() {
		return Top < 0;
	}

	/*
	Full method: checks for full stack
	Paramaters: void
	Returns: bool: true = full stack
	*/
	bool Full() {
		return (Top == Size - 1);
	}

	/*
	checkResize method: checks how full the stack is
	Paramaters: bool: pop: checks if a number is being popped
	Returns: void
	*/
	void checkResize(bool pop) {
		int twenty = Size / 5;//finds twenty percent of size
		//checks if top is less than 20% and checks to see if the array has
		//grown and that the array is getting smaller
		if (twenty >= Top && enlarged && pop) {
			Reduce();
		}
		//checks to see if top is above 80%
		else if (Size - twenty <= Top) {
			Enlarge();
			enlarged = true;
		}
	}

	/*
	Reduce method: shrinks the array by 50%
	Paramaters: void
	Returns: void
	*/
	void Reduce() {
		int newSize;

		//ensures a smallest array size of 5
		if ((Size / 2) <= 5) {
			newSize = 5;
		}
		else {
			newSize = Size / 2;
		}

		//new temp array
		int *array3 = new int[newSize];

		//copies numbers to new array
		for (int i = 0; i < Top; i++) {
			array3[i] = A[i];
		}
		//sets main array to new array
		int *temp = A;
		A = array3;
		delete[] temp;
		//sets the main size equal to new size
		Size = newSize;
		//prints message for debuging not final file
		cout << "\nThe size has shrunk to: " << newSize << endl;
	}

	/*
	Enlarge method: grows the array by 150%
	Paramaters: void
	Returns: void
	*/
	void Enlarge() {
		//creates new size and array
		int newSize = Size * 1.5;
		int *array2 = new int[newSize];

		//copies numbers to new array
		for (int i = 0; i < Size; i++) {
			array2[i] = A[i];
		}

		//sets main array to new array
		int *temp = A;
		A = array2;
		delete[] temp;
		//sets the main size equal to new size
		Size = newSize;
		//prints message for debuging not final file
		cout << "\nThe size has grown to: " << newSize << endl;
		//checks for new largest size
		if (largest < Size)
			largest = Size;
	}

};


int main() {

	ifstream fin;
	fin.open("input_data.txt");
	ofstream fout;
	fout.open("stack_out.dat");

	//creates main stack
	stack s(10);

	//reads reads in all the data from a file
	while (!fin.eof()) {
		string action = "";
		int num;

		fin >> action >> num;

		if (action == "+") {
			s.Push(num);
		}
		else if (action == "-") {
			s.Pop();
		}
		else {
			cout << "Error reading from file. \n";
		}
	}

	//prints info to the file
	fout << "Jeff Reeve \n10/8/19 \nHomework 2\n \nStack Size: " << s.getSize()
		<< "\nLargest Size: " << s.getLargest() << "\nValues: ";
	for (int i = 0; i <= s.getTop(); i++) {
		 fout << s.getNum(i) << " ";
	}

	s.Print();


	fin.close();
	fout.close();
	//system("pause");
	return 0;
}
