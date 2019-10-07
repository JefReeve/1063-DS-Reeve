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
    stack(){
        Size = 100;
        A = new int [Size];
        Top = -1;
        enlarged = false;
        largest = Size;
    }
    
/*
constructor: initializes to specified size and sets top
paramaters: s = int size
*/
    stack(int s){
        Size = s;
        A = new int [Size];
        Top = -1;
        enlarged = false;
        largest = Size;
    }

/*
GetSize method: get the size
Paramaters: void
Returns: int: size of array
*/
int getSize(){
    return Size;
}

/*
GetLargest method: get the largest size of the array
Paramaters: void
Returns: int: largest size of array
*/
int getLargest(){
    return largest;
}

/*
Push method: adds item to top of stack
Paramaters: int val: integer size
Returns: bool: true = success
*/
bool Push(int val){
  //  if(!Full()){
        Top++;
        A[Top] = val;
        checkResize();
        return true;
        /*
    }else{
        return false;
    }
    */
}

/*
Pop fucntion: removes top of stack and returns it
Paramaters: void
Returns: int: item removed from stack
*/
int Pop(){
    if(!Empty()){
        int temp = 0;
        temp = A[Top];
        Top--;
        checkResize();
        return temp;
    }else{
        cout << "Cannot remove item from empy stack\n";
    }
    return 0;
}

/*
Print method: prints stack
Paramaters: void
Returns: void
*/
void Print(){
    cout << "\n-------\n";
    for(int i = Top; i >= 0; i--){
        cout << A[i] << endl;
    }
}

/*
Empty method: checks for empty stack
Paramaters: void
Returns: bool: true = empty stack
*/
bool Empty(){
    return Top < 0;
}

/*
Full method: checks for full stack
Paramaters: void
Returns: bool: true = full stack
*/
bool Full(){
    return (Top == Size -1);
}

/*
checkResize method: checks how ful the stack is
Paramaters: void
Returns: int: 0 for no action, 1 for shrink, 2 for grow
*/
int checkResize(){
    int twenty = Size/5;//finds twenty percent of size
    if(twenty > Top && enlarged){
        Shrink();
        return 1;//shrink
    }
    else if(Size-twenty <= Top){
        Enlarge();
        enlarged = true;
        return 2;//englarge
    }
    else{
        return 0;// do nothing
    }
}

/*
Shrink method: shrinks the array by 50%
Paramaters: void
Returns: void
*/
void Shrink(){
    int newSize;

    if(Size/2 <= 2){
    newSize = 2;
    }
    else{
    newSize = Size * .5;
    }

    int *array2 = new int[newSize];

    for (int i = 0; i < Size; i++){
        array2[i] = A[i];
    }
    int *temp = A;
    A = array2;
    delete[] temp;
    Size = newSize;
    cout << "\nThe size has shrunk to: " << newSize << endl;
}

/*
Enlarge method: grows the array by 150%
Paramaters: void
Returns: void
*/
void Enlarge(){
    int newSize = Size * 1.5;
    int *array2 = new int[newSize];

    for (int i = 0; i < Size; i++){
        array2[i] = A[i];
    }
    int *temp = A;
    A = array2;
    delete[] temp;
    Size = newSize;
    cout << "\nThe size has grown to: " << newSize << endl;
    if(largest < Size)
    largest = Size;
}

};


int main() {

ifstream fin;
fin.open("input.txt");
ofstream fout;
fout.open("output.dat");

stack s(10);


while(!fin.eof()) {
string action = "";
int num;

fin >> action >> num;

if(action == "+"){
    s.Push(num);
}
else if (action == "-"){
    s.Pop();
}
else{
    cout << "Error reading from file. \n";
}
}

fout << "Jeff Reeve \n10/6/19 \nHomework 2\n \nStack Size: " << s.getSize()
     << "\nLargest Size: " << s.getLargest() << "\nValues: ";
     for(int i = 0;i < s.getSize(); i++){
        // fout << s.A[i] << " ";
     }

s.Print();




return 0;
}
