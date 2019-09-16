#include <iostream>
#include <fstream>

using namespace std;

struct Employee{
    string emp_id; 
    string first_name;
    string last_name;
    string gender;
    string email;
    double hourly_pay;
    Employee *Next;

    Employee(){
        emp_id = "";
        first_name = "";
        last_name = "";
        gender = "";
        email = "";
        hourly_pay = 0.0;
    }

    Employee(string id,string first,string last,string sex,string mail, double pay){
        emp_id = id;
        first_name = first;
        last_name = last;
        gender = sex;
        email = mail;
        hourly_pay = pay;
    }
};

class LinkedList{
private:
    Employee* Head;

public:
    LinkedList(){
        Head = NULL;
    }

        void Push(string id,string first,string last,string sex,string mail, double pay){
        Employee* Temp = new Employee(id,first,last,sex,mail,pay);

        if(Head == NULL){
            Head = Temp;
        }else{
            Employee* Temp2 = Head;

            while(Temp2->Next != NULL){

                Temp2 = Temp2->Next;
            }

            Temp2->Next = Temp;
        }
    }

    bool find(string searchEmail){
      Employee* Temp = Head;

              while(Temp != NULL){
                if(substringMatch(Temp->email, searchEmail)){
                   cout<<"\n" << Temp->emp_id<<", "<<Temp->first_name<<", "<<Temp->last_name<<", "<<Temp->email<<", "<<Temp->gender<<", "<<Temp->hourly_pay << endl;
                   return true;
                }
            Temp = Temp->Next;
        }
      return false;
    }

  bool deleted(string searchEmail){
     Employee* Temp = Head;

              while(Temp->Next != NULL){
                if(substringMatch(Temp->Next->email, searchEmail)){
                   cout<<"\n" << Temp->Next->emp_id<<", "<<Temp->Next->first_name<<", "<<Temp->Next->last_name<<", "<<Temp->Next->email<<", "<<Temp->Next->gender<<", "<<Temp->Next->hourly_pay << endl;
                  // Temp->Next = Temp->Next->Next

                    Employee* Next = Temp->Next->Next; 
  
                    // Unlink the node from linked list 
                    free(Temp->Next);  // Free memory 
                  
                    Temp->Next = Next;  // Unlink the deleted node from list 

                   return true;
                }
            Temp = Temp->Next;
        }
  return false;
  }

    void print(){
        Employee* Temp = Head;

        while(Temp != NULL){
            cout<<Temp->emp_id<<", "<<Temp->first_name<<", "<<Temp->last_name<<", "<<Temp->email<<", "<<Temp->gender<<", "<<Temp->hourly_pay;
            if(Temp->Next){
                cout<<"->";
            }
            Temp = Temp->Next;
        }
    }

    bool substringMatch(string macro, string micro){
    return (macro.find(micro) != std::string::npos);
}

  void load(LinkedList L){
    string emp_id; 
    string first_name;
    string last_name;
    string gender;
    string email;
    double hourly_pay;

      ifstream fin;
    	fin.open("employees.dat");
      while(!fin.eof()){
        fin >> emp_id;
        fin >> first_name;
        fin >> last_name;
        fin >> gender;
        fin >> email;
        fin >> hourly_pay;
        Push(emp_id, first_name, last_name, gender, email, hourly_pay);
      }
    }

};

int menu(){
    int choice = 0;
    while(choice < 1 || choice > 4){
        cout<<"\nMenu of Operations:\n";
        cout<<"    1 - Find Employee\n";
        cout<<"    2 - Add Employee\n";
        cout<<"    3 - Delete Employee\n";
        cout<<"    4 - Quit\n";
        cout<<"Choice: ";
        cin>>choice;
    }
    return choice;
}

bool substringMatch(string macro, string micro){
    return (macro.find(micro) != std::string::npos);
}

int main(){
   

    string inputEmail = "";
    bool Result = false;

    string tempID = "";
    string tempFirst = "";
    string tempLast= "";
    string tempGender = "";
    string tempEmail = "";
    double tempPay = 0;

    LinkedList L;
    L.load(L);

    //L.print();

    int choice = 0;

    while(choice != 4){
        choice = menu();
        if(choice == 1){
          cout << "Please enter an email to search for: ";
          cin >> inputEmail;
          Result = L.find(inputEmail);
          if(Result == true)
          cout << "Search Completed\n";
          else{
            cout << "The search did not yield any results. \n";
          }
        }
        else if(choice == 2){
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
        else if(choice == 3){
          cout << "\nEnter the email of the account you want to delete: ";
          cin >> inputEmail;
          Result = L.deleted(inputEmail);
          if(Result == true)
          cout << "\nSuccesfully deleted\n";
          else{
            cout << "\nThat email was not found. \n";
          }
        }
    }

    string test = "ENDING programo";
    for(auto& c : test)
    {
    c = tolower(c);
    }

    cout<<test<<endl;
    return 0;
}
