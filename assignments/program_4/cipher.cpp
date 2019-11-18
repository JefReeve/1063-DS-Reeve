#include <iostream>
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
      letter = s[i];
      intVal = (int)letter - 65;
      intVal += shift % 26;
      letter = intVal + 65;
      temp += letter;
    }
    return temp;
  }

  // string decrypt(string s){

  // }

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
    shift = num;
  }

  // string readCipherText(){

  // }

  // void writeCipherText(){

  // }

  // string readPlainText(){

  // }

  // void writePlainText(){

  // }


};


int main() {
  ceaserCipher lul;
  string temp = "aabbcc";
  string crypt;
  temp = lul.upperCase(temp);
  crypt = lul.encrypt(temp);
  cout << crypt << temp;
}
