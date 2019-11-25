///////////////////////////////////////////////////////////////////////////////
//
// Author:           Jeff Reeve
// Assignment:       Program_04
// Date:             25 November 2019
// Title:            Program 4 - Cipher
// Semester:         Fall 2019
// Course:           CMPS 1063 
// 
// Files:            cipher.cpp
//                   encrypted.txt
//                   decrypted.txt
//                   newEncrypted.txt
// Description:
//       Program will read in an encrypted file and decrypt it into another file.
//		 Then, it will encrypt the new file into a third file at a new cipher
//		 shift value, default 13. The program also has a menu to encrypt or
//		 dycrypt strings.
//
/////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class ceaserCipher {
private:
	int shift;
public:
	//constructor just sets shift amount to a default 13
	ceaserCipher() {
		shift = 13;
	}

/**
 * encrypt
 *
 * Description:
 *      reads in a string and shifts the letters by the shift variable.
 *
 * Params:
 *      string s: any string to be encrypted
 *
 * Returns:
 *      string : encrypted string
 */
	string encrypt(string s) {
		int intVal = 0;
		char letter;
		string temp = "";

		for (int i = 0; i < s.length(); i++) {
			if (s[i] >= 65 && s[i] <= 96) {
				letter = s[i];
				intVal = (int)letter - 65;
				intVal += shift;
				intVal %= 26;
				letter = intVal + 65;
				temp += letter;
			}
			else
				temp += s[i];
		}
		return temp;
	}
/**
 * decrypt
 *
 * Description:
 *      decrypts string by the value in variable shift
 *
 * Params:
 *      string s : string to be decrypted
 *
 * Returns:
 *      string : plain text string
 */
	string decrypt(string s) {
		int intVal = 0;
		char letter;
		string temp = "";

		for (int i = 0; i < s.length(); i++) {
			if (s[i] >= 65 && s[i] <= 96) {
				letter = s[i];
				intVal = (int)letter - 65;
				intVal -= shift;
				if (intVal < 0)
					intVal += 26;

				intVal %= 26;
				letter = intVal + 65;
				temp += letter;
			}
			else
				temp += s[i];
		}
		return temp;
	}
	/**
	 * upperCase
	 *
	 * Description:
	 *      makes all letters in string upper case
	 *
	 * Params:
	 *      string s : string of letters, punctuation doesn't matter.
	 *
	 * Returns:
	 *      string : same string as input but with capital letters
	 */
	string upperCase(string s) {
		string temp = "";
		for (int i = 0; i < s.length(); i++) {
			//checks for letters
			if (s[i] >= 97 && s[i] <= 122) {
				temp += s[i] - 32;
			}
			else
				temp += s[i];
		}
		return temp;
	}
/**
 * setShift
 *
 * Description:
 *      sets the shift variable that is private
 *
 * Params:
 *      int num : number to be the new shift value
 *
 * Returns:
 *      void
 */
	void setShift(int num) {
		//mod 26 since the alphebet is 26 charecters long
		num %= 26;
		shift = num;
	}
	/**
	 * readCipherText
	 *
	 * Description:
	 *      reads in a file of encrypted text and outputs decrypted text
	 *
	 * Params:
	 *      string file : file name of encrypted text
	 *		string outfile : file name of output
	 *
	 * Returns:
	 *      void
	 */
	void readCipherText(string file, string outFile) {
		string fnl = "";
		int howMany = 0;
		int shift = 0;
		ofstream fout(outFile);
		fout << "JEFF REEVE\n11/25/2019\nProgram 4 decrypted output\n\n";
		//reads in first number to tell how many lines to read in
		ifstream fin(file);
		fin >> howMany;

		for (int i = 0; i < howMany; i++) {
			fin >> shift;
			setShift(shift);
			//double getline to skip down to the text
			getline(fin, fnl);
			getline(fin, fnl);
			fnl = upperCase(fnl);
			fnl = decrypt(fnl);
			writePlainText(fout, fnl);
		}
		fin.close();
	}
	/**
	 * writePlainText
	 *
	 * Description:
	 *      writes text to a file
	 *
	 * Params:
	 *      ofstream &fout : pointer to opened file
	 *		string msg : text to be put in file
	 *
	 * Returns:
	 *      void
	 */
	void writePlainText(ofstream &fout, string msg) {
		for (int i = 0; i < msg.length(); i++) {
			fout << msg[i];
		}
		fout << endl << endl;
	}
	/**
	 * readPlainText
	 *
	 * Description:
	 *      reads in plain text from a file and outputs encrypted text
	 *
	 * Params:
	 *      string file : file name of plain text
	 *		string outfile : file name of output
	 *
	 * Returns:
	 *      void
	 */
	void readPlainText(string file, string outFile) {
		string fnl = "";
		ofstream fout(outFile);
		fout << "JEFF REEVE\n11/25/2019\nProgram 4 encrypted output\n\n";
		ifstream fin(file);
		
		//loops as long as there is a line to read
		while(getline(fin, fnl)){
			fnl = upperCase(fnl);
			fnl = encrypt(fnl);
			writeCipherText(fout, fnl);
		}
		fin.close();
	}
	/**
	 * writeCipherText
	 *
	 * Description:
	 *      writes text to a file
	 *
	 * Params:
	 *      ofstream &fout : pointer to opened file
	 *		string msg : text to be put in file
	 *
	 * Returns:
	 *      void
	 */
	void writeCipherText(ofstream &fout, string msg) {
		for (int i = 0; i < msg.length(); i++) {
			fout << msg[i];
		}
		fout << endl;
	}
};
int main() {
	ceaserCipher ceaser;
	string crypt;
	string dcrypt;
	int choice = 0;
	int shift = 13;

	ceaser.readCipherText("encrypted.txt", "decrypted.txt");
	ceaser.setShift(13);
	ceaser.readPlainText("decrypted.txt", "newEncrypted.txt");

	cout << "encrypted.txt has been decrypted into decrypted.txt\n";
	cout << "decrypted.txt has been reencrypted into newEncrypted.txt ";
	cout << "with a shift of 13\n";
	//start of menu loop, do while for first iteration to happen everytime
	do {
		cout << "\nCurrent shift amout: " << shift << "\nPlease select a choice:";
		cout << "\n1) Encrypt a string\n2) Decrypt a string\n3)";
		cout << "Change shift amount\n4) Quit";
		cout << "\nChoice: ";
		cin >> choice;
		//checks for non int inputs
		while (!cin.good()){
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "\nError! Please enter a number between 1 and 4.\n";
			cin >> choice;
		}
		switch (choice) {
		case 1:
			cout << "Please enter a string to be encrypted at ";
			cout << "current shift value : \n";
			cin >> crypt;
			crypt = ceaser.upperCase(crypt);
			crypt = ceaser.encrypt(crypt);
			cout << "\n\nYour encrypted string is: " << crypt << "\n\n";
			break;
		case 2:
			cout << "Please enter a string to be decrypted at current ";
			cout << "shift value : \n";
			cin >> dcrypt;
			dcrypt = ceaser.upperCase(dcrypt);
			dcrypt = ceaser.decrypt(dcrypt);
			cout << "\n\nYour decrypted string is: " << dcrypt << "\n\n";
			break;
		case 3:
			cout << "\nPlease enter a shift amount: ";
			cin >> shift;
			cout << endl;
			//checks for non int inputs
			while (!cin.good()) {
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cout << "\nError! Please enter an integer.\n";
				cin >> shift;
			}
			ceaser.setShift(shift);
			break;
		case 4:
			//doesn't need to do anything
			break;
		default:
			cout << "\nError! Please enter a number between 1 and 4.\n";
			break;
		}
	} while (choice != 4);
	//system("pause");
	return 0;
}
