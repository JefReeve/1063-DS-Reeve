#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class ceaserCipher{
  private:
  int shift;

  public:

  string encrypt(string s){
    int intVal=0;
    char letter;
    string temp = "";

    for(int i = 0; i < s.length();i++){
      if(s[i] >= 65 && s[i] <= 96){
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

   string decrypt(string s){
    int intVal=0;
    char letter;
    string temp = "";

    for(int i = 0; i < s.length();i++){
      if(s[i] >= 65 && s[i] <= 96){
      letter = s[i];
      intVal = (int)letter - 65;
      intVal -= shift;
      if(intVal < 0)
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

  string upperCase(string s){
    string temp = "";
    for(int i = 0; i < s.length(); i++){
      if(s[i] >= 97 && s[i] <= 122){
        temp += s[i] - 32;
      }
      else
      temp += s[i];
    }
    return temp;
  }

  void setShift(int num){
    num %= 26;
    shift = num;
  }

   void readCipherText(string file,string outFile){
    string fnl = "";
    int howMany = 0;
    int shift = 0;
    ofstream fout(outFile);
    ifstream fin(file);
    fin >> howMany;

    for(int i = 0; i < howMany; i++){
      fin >> shift;
      setShift(shift);
      getline(fin, fnl);
      getline(fin, fnl);
      fnl = upperCase(fnl);
      cout << "Test: " << fnl << endl;
      fnl = decrypt(fnl);
      cout << "Test: " << fnl << endl;
      writeCipherText(fout, fnl);
    }
    fin.close();
   }

   void writeCipherText(ofstream &fout, string msg){
    string temp = "";
    string fnl = "";
    //ofstream fout(file);
    for(int i = 0; i < msg.length(); i++){
      fout << msg[i];
    }
    fout << endl;
   }

   string readPlainText(string file){
    string temp = "";
    string fnl = "";
    ifstream fin(file);
    while(getline(fin, temp)){
      fnl += temp;
      fnl += " ";
    }
    fin.close();
    return fnl;
   }

   void writePlainText(string file, string msg){
    string temp = "";
    string fnl = "";
    ofstream fout(file);
    for(int i = 0; i < msg.length(); i++){
      fout << msg[i];
    }
   }


};


int main() {
  ceaserCipher lul;
  string temp = "abz!";
  string crypt;
  string dcrypt;

  lul.setShift(6);

  lul.readCipherText("encFile.txt", "output.txt");
  // cout << lul.readPlainText("encFile.txt");

  temp = lul.upperCase(temp);
  crypt = lul.encrypt(temp);
  dcrypt = lul.decrypt(crypt);

  //cout << temp << " -> " << crypt << " -> " << dcrypt;
}
