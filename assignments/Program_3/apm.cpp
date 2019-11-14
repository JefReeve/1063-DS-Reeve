//////////////////////////////////////////////////////////////////////////
//
// Author:           JEFFREY REEVE
// Assignment:       Program_03
// Date:             13 November 2019
// Title:            Program 3 - Arbitrary Precision Math
// Semester:         Fall 2019
// Course:           CMPS 1063 
// 
// Files:            main.cpp
//                   input_data.txt 
//                   output.num
// Description:
//       Program to hold arbitrarily long numbers and do basic math with them.
//			Reads in a declared number of problems from a file.
//
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>

using namespace std;

/*
  node struct to hold individual digits
*/
struct node {
	node* prev;
	node* next;
	int data;
	/*
	  constuctor without a previous node.
	*/
	node(int d) {
		prev = NULL;
		next = NULL;
		data = d;
	}
	/*
	 overloaded constuctor with a previous node to connect to.
	*/
	node(int d, node* p) {
		prev = p;
		next = NULL;
		data = d;
	}
};
/*
 list class to hold and connect nodes of individual digits.
*/
class num {
private:
	node* head;
	node* tail;

public:
	/*
	  Constructor for num class, sets head and tail to NULL.
	 */
	num() {
		head = tail = NULL;
	}
	
	/**
	 * getTail
	 *
	 * Description:
	 *      gets the tail of the list since its private
	 *
	 * Params:
	 *      
	 *
	 * Returns:
	 *     node* tail : last digit in a list
	 */
	node* getTail() {
		return tail;
	}
	node* getHead() {
		return head;
	}
	/**
	 * fill
	 *
	 * Description:
	 *      Fills a list with a number from a string.
	 *
	 * Params:
	 *      string s : number in string form to be insterted 1 digit at a time.
	 *
	 * Returns:
	 *     void
	 */
	void fill(string s) {
		head = tail = NULL;
		for (int i = 0; i < s.length(); i++) {
			// inserts individual digits one at a time. -48 to account for ascii values in a string.
			endSert(s[i] - 48);
		}
	}
	/**
	 * isEmpty
	 *
	 * Description:
	 *      checks for an empty list.
	 *
	 * Params:
	 *
	 * Returns:
	 *      bool : true for empty, false for not empty
	 */
	bool isEmpty() {
		if (head == NULL || tail == NULL)
			return true;
		else
			return false;
	}
	/**
	 * endSert
	 *
	 * Description:
	 *      inserts a number at the end of the list
	 *
	 * Params:
	 *      int n : number to be inserted
	 *
	 * Returns:
	 *      void
	 */
	void endSert(int n) {
		//if there is an empty list head and tail equal the same node.
		if (isEmpty()) {
			node* temp = new node(n);
			head = temp;
			tail = temp;
		}
		else {
			//uses overloaded constructor to assign prev
			node* temp = new node(n, tail);
			node* traverse = head;
			while (traverse->next) {
				traverse = traverse->next;
			}
			traverse->next = temp;
			tail = temp;
		}
	}
	/**
	 * frontSert
	 *
	 * Description:
	 *      Inserts an int to the front of the list.
	 *
	 * Params:
	 *      int n : A number to be inserted.
	 *
	 * Returns:
	 *      void
	 */
	void frontSert(int n) {
		//if there is an empty list head and tail equal the same node.
		if (isEmpty()) {
			node* temp = new node(n);
			head = temp;
			tail = temp;
		}
		else {
			//does not uses overloaded constructor since prev will be NULL
			node* temp = head;
			head = new node(n);
			head->next = temp;
			temp->prev = head;
		}
	}
	/**
	 * sub
	 *
	 * Description:
	 *      subtracts two arbitrarily long numbers using doubly linked lists.
	 *
	 * Params:
	 *      node* temp2 : pointer to the tail of a list
	 *
	 * Returns:
	 *      Node* : a list with subtraction results
	 */
	node* sub(node* temp2) {

		node* temp = tail;
		//third list to store the answer
		num list3;
		//tempNum is to hold individual digits untill they are added to the list
		int tempNum;
		//loops while the first list has digits
		while (temp != NULL) {
			//checks if the second list has a digit
			if (temp2 == NULL) {
				//if the digit has been borrowed from to below 0 then borrow from the next digit
				if (temp->data < 0) {
					temp->prev->data -= 1;
					temp->data += 10;
				}
				//move the digit to tempNum
				tempNum = temp->data;
			}
			else {
				//if the first number isnt big enough to subract from, then borrow from the next digit
				if ((temp->data - temp2->data) < 0) {
					temp->prev->data -= 1;
					temp->data += 10;
					tempNum = temp->data - temp2->data;
				}
				//if no borrowing is needed then just assign to tempNum
				else {
					tempNum = temp->data - temp2->data;
				}
			}
			//insert the subtracted digit to the front of the new list
			list3.frontSert(tempNum);
			temp = temp->prev;
			//if the second number has no more digits don't decrement
			if (temp2 != NULL) {
				temp2 = temp2->prev;
			}
			else
				temp2 = NULL;
		}
		//loop to delete extra zeros at the start of the number
		while (list3.head->data == 0) {
			node* temp = list3.head;
			list3.head = list3.head->next;
			delete temp;
		}
		//returns pointer to first digit of answer
		return list3.head;
	}
	/**
	 * mul
	 *
	 * Description:
	 *      multiplies two arbitrarily long numbers using doubly linked lists.
	 *
	 * Params:
	 *      node* temp2 : pointer to the tail of a list
	 *
	 * Returns:
	 *      Node* : a list with multiplication results
	 */
	node* mul(node* temp2) {

		//carry variable to hold carries to the next digit
		int carry = 0;
		//count variable to count how many times the outer loop loops
		int count = 0;

		node* temp;
		//tlist (or temp list) holds a temporary list to be added to final list
		num tlist;
		//flist (or final list) holds the final list that will be added to
		num flist;
		flist.frontSert(0);
		int tempNum;
		
	//loops through second number
		while (temp2 != NULL) {
			//sets temp to the last digit for each of the second numbers digits
			temp = tail;
			//resets the carry
			carry = 0;
			//loops through the first number
			while (temp != NULL) {
				//multiplies the digits and adds the carry if there is any
				tempNum = temp->data * temp2->data + carry;
				//divies by ten to get the first digit if multiple
				carry = tempNum / 10;
				//stores the far right digit
				tempNum = tempNum % 10;
				tlist.frontSert(tempNum);
				temp = temp->prev;
			}
			//inserts the carry if any remains
			if(carry != 0)
			tlist.frontSert(carry);

			//adds the temp list to the final list
			flist.head = flist.add(tlist.tail);

			//resets temp list
			tlist.head = NULL;
			tlist.tail = NULL;

			//adds as many zeroes to the end of tlist as needed
			count++;
			for (int i = 0; i < count; i++) {
				tlist.frontSert(0);
			}
			temp2 = temp2->prev;
		}
		return flist.head;
	}
	/**
	 * add
	 *
	 * Description:
	 *      Adds two arbitrarily long numbers using doubly linked lists.
	 *
	 * Params:
	 *      node* list2 : pointer to the tail of the second number
	 *
	 * Returns:
	 *      Node* : a pointer to the head of a list with addition results
	 */
	node* add(node* list2) {
		node* temp = head;
		
		//loop to start from the end of the list
			while (temp->next && temp) {
				temp = temp->next;
			}
		
		node* temp2 = list2;
		//third list to store the answer in
		num list3;

		int tempNum;
		int carry = 0;


		//loops as long as either number has another digit
		while (temp != NULL || temp2 != NULL) {
			//checks if either number is out of digits
			if (temp == NULL) {
				//adds the carry from the previous addition
				tempNum = temp2->data + carry;
				temp2 = temp2->prev;
			}
			else if (temp2 == NULL) {
				//adds the carry from the previous addition
				tempNum = temp->data + carry;
				temp = temp->prev;
			}
			else {
				//adds the carry from the previous addition with the two added digits
				tempNum = temp->data + temp2->data + carry;
				temp = temp->prev;
				temp2 = temp2->prev;
			}
			carry = 0;
			//if the sum is over 9 then it is 2 digits and part gets carried to the next digit
			if (tempNum > 9) {
				carry = 1;
				tempNum = tempNum % 10;
			}
			list3.frontSert(tempNum);
		}
		//after the addition if there is still a carry, add it to the front of the list
		if (carry == 1) {
			list3.frontSert(1);
		}
		//returns a pointer to the first digit of the list
		return list3.head;
	}
	/**
	 * PrintResult
	 *
	 * Description:
	 *      Prints a linked list from a pointer to the first value.
	 *
	 * Params:
	 *     node* n : pointer to the first value in a list.
	 *
	 * Returns:
	 *      void : results are printed.
	 */
	void printResult(node* n) {
		node* temp = n;
		//travers the list and prints each digit
		while (temp) {
			cout << temp->data;
			temp = temp->next;
		}
		cout << endl;
	}
};

int main() {

	ofstream outfile("output.txt");
	outfile << "Jeff Reeve\nProgram 3\nArbitrary Precision Math\n\n";
	ifstream fin("input_data.txt");
	int howMany;
	char operation;
	string number1;
	string number2;
	num list1;
	num list2;
	node* answer = NULL;

	//reads the first number to find out how any problems there are
	fin >> howMany;

	for (int i = 1; i <= howMany; i++) {
		fin >> operation >> number1 >> number2;
		//methods to fill lists with the strings' number
		list1.fill(number1);
		list2.fill(number2);
		outfile << "Operation " << i << ": ";
		switch (operation) {
		case '+':
			answer = list1.add(list2.getTail());
			outfile << "Addition\nAnswer: \n\n";
			break;
		case '-':
			answer = list1.sub(list2.getTail());
			outfile << "Subtraction\nAnswer: \n\n";
			break;
		case '*':
			answer = list1.mul(list2.getTail());
			outfile << "Multiplication\nAnswer: \n\n";
			break;
		default:
			outfile << "\n Error! Unexpected operation! \n";
			cout << "\n Error! Unexpected operation! \n";
			break;
		}
		node* temp = answer;
		while (temp) {
			outfile << temp->data;
			temp = temp->next;
		}
		outfile << endl;
		list1.printResult(answer);
		outfile << endl;
	}
	system("pause");
	return 0;
}
