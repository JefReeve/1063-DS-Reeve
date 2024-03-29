//This program has a list class that stores employee information, one per node.
//There is a basic menu to navigate and perform actions. Information is loaded
//from the employees.txt file and some information is printed to the screen, and
//some is printed to a file called output.txt

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Employee {
	string emp_id;
	string first_name;
	string last_name;
	string gender;
	string email;
	double hourly_pay;
	Employee *Next;

	//employee constructer if nothing is passed to it
	Employee() {
		emp_id = "";
		first_name = "";
		last_name = "";
		gender = "";
		email = "";
		hourly_pay = 0.0;
		Next = NULL;
	}

	//overloaded employee constructer with information passed to it
	Employee(string id, string first, string last, string sex, string mail,
		double pay) {
		emp_id = id;
		first_name = first;
		last_name = last;
		gender = sex;
		email = mail;
		hourly_pay = pay;
		Next = NULL;
	}
};

//main linked list class
class LinkedList {

public:
	Employee* Head = NULL;

	//push class to add a node to the front of the list
	void Push(string id, string first, string last, string sex, string mail, 
		double pay) {

			Employee* Temp = new Employee(id, first, last, sex, mail, pay);

			//checks for an empty list
			if (Head == NULL) {
				Head = Temp;
			}
			else {
				Employee* Temp2 = Head;

					while (Temp2->Next != NULL) {

						Temp2 = Temp2->Next;
					}
				
				Temp2->Next = Temp;
			}
	}

	//method to search the list for an email returns the amount of results
	int find(string searchEmail) {
		Employee* Temp = Head;
		int count = 0;

		while (Temp != NULL) {
			//uses another method to check for partial matches
			if (substringMatch(Temp->email, searchEmail)) {
				//if there is a match it prints the account to the screen
				cout << "\n" << Temp->emp_id << ", " << Temp->first_name << ", "
					<< Temp->last_name << ", " << Temp->email << ", " 
					<< Temp->gender << ", " << Temp->hourly_pay << endl;
				count++;
			}
			Temp = Temp->Next;
		}
		//if nothing in the list matches then it returns NULL
		if (count > 0)
			return count;
		else
			return NULL;
	}

	//method to pop the first item out of the list and return it
	Employee* pop() {
		Employee* temp = Head;
		//checks for an empty list
		if (Head != NULL) {
			//replaces the front of the list with the second
			Head = Head->Next;
		}
		return temp;
	}

	//method to delete a specific account, searched via email
	bool deleted(string searchEmail) {
		//checks for an empty list
		if (Head != NULL) {
			Employee* Temp = Head;

			while (Temp->Next != NULL) {
				//uses another method to search for partial matches 
				if (substringMatch(Temp->Next->email, searchEmail)) {
					cout << "\n" << Temp->Next->emp_id << ", " 
						<< Temp->Next->first_name << ", " << Temp->Next->last_name
						<< ", " << Temp->Next->email << ", " << Temp->Next->gender
						<< ", " << Temp->Next->hourly_pay << endl;

					//stores the node 2 spots ahead
					Employee* ahead = Temp->Next->Next;

					// Unlink the next node from list 
					free(Temp->Next);  // Free memory 

					Temp->Next = ahead;  // Unlink the deleted node from list 

					return true;
				}
				Temp = Temp->Next;
			}
		}
		return false;
	}

	//method to find partial matches in strings
	bool substringMatch(string macro, string micro) {
		return (macro.find(micro) != std::string::npos);
	}

	//method to load a list from data in a file
	void load(LinkedList L) {
		string emp_id;
		string first_name;
		string last_name;
		string gender;
		string email;
		double hourly_pay;

		ifstream fin;
		fin.open("employees.txt");
		while (!fin.eof()) {
			// reads in data in order so if a piece of data is missing from the
			// file then it will all be wrong
			fin >> emp_id;
			fin >> first_name;
			fin >> last_name;
			fin >> gender;
			fin >> email;
			fin >> hourly_pay;
			// uses another method to put the incoming data to the front
			Push(emp_id, first_name, last_name, gender, email, hourly_pay);
		}
		fin.close();
	}

};

//function to put a menu on screen for the user
int menu() {
	int choice = 0;
	while (choice < 1 || choice > 4) {
		cout << "\nMenu of Operations:\n";
		cout << "    1 - Find Employee\n";
		cout << "    2 - Add Employee\n";
		cout << "    3 - Delete Employee\n";
		cout << "    4 - Quit\n";
		cout << "Choice: ";
		cin >> choice;
	}
	return choice;
}

int main() {
	string inputEmail = "";
	bool Result = false;
	int searchResult = NULL;
	Employee* popResult;

	string tempID = "";
	string tempFirst = "";
	string tempLast = "";
	string tempGender = "";
	string tempEmail = "";
	double tempPay = 0;

	ofstream fout;
	fout.open("output.txt");

	//makes the main list and loades it with data from a file
	LinkedList L;
	L.load(L);
	popResult = L.pop();

	//L.print();

	int choice = 0;

	//loop to keep the user in the menu
	while (choice != 4) {
		choice = menu();

		//choice 1 to use search method to find an account in the list
		if (choice == 1) {
			cout << "Please enter an email to search for: ";
			cin >> inputEmail;
			searchResult = L.find(inputEmail);
			//the method prints the account if found, so it doesnt need to be
			//printed here
			if (searchResult != NULL) {
				cout << "Search Completed\n";
				
			}
			else {
				cout << "The search did not yield any results. \n";
			}
		}
		//choice 2 creates an account and pushes it to the front of the list
		else if (choice == 2) {
			cout << "\nPlease enter an employee id: ";
			cin >> tempID;
			cout << "\nPlease enter a first name: ";
			cin >> tempFirst;
			cout << "\nPlease enter a last name: ";
			cin >> tempLast;
			cout << "\nPlease enter a gender(m or f): ";
			cin >> tempGender;
			cout << "\nPlease enter an email: ";
			cin >> tempEmail;
			cout << "\nPlease enter how much pay per hour: ";
			cin >> tempPay;
			L.Push(tempID, tempFirst, tempLast, tempGender, tempEmail, tempPay);
		}
		//choice 3 deletes an account if it is in the list
		else if (choice == 3) {
			cout << "\nEnter the email of the account you want to delete: ";
			cin >> inputEmail;
			Result = L.deleted(inputEmail);
			//the account is printed in the method if found
			if (Result == true)
				cout << "\nSuccesfully deleted\n";
			else {
				cout << "\nThat email was not found. \n";
			}
		}
	}

	Employee* Temp = L.Head;
	int count = 0;

	//loop to print the first 30 ids in the list
	while (Temp != NULL && count < 30) {
		fout << Temp->emp_id << "\n";

		Temp = Temp->Next;
		count++;
	}
	
	//prints the search results to the file
	if (searchResult != NULL) {
		fout << "There are " << searchResult << " results for the search : "
			<< inputEmail << endl;
	}

	//prints the poppped email
	fout << "The popped email was : " << popResult->email << endl;
	string test = "ENDING PROGRAM";

	fout.close();
	cout << test << endl;
	system("pause");
	return 0;
}
