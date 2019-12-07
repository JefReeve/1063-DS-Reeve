#include <iostream>
#include <string>
#include "termgame.h"

using namespace TermGame;
using namespace std;

class card {
public:
  card* next;
  int cnum;
  int face;
  int suit;
//public:

  card(){
    next = NULL;
    cnum = 0;
    face = 0;
    suit = 0;
  }
  card(int num){
    next = NULL;
    cnum = num;
    face = (num % 13) + 1;
    suit = num / 13.1;
  }
  
  int getface(){
    return face;
  }
  int getSuit(){
    return suit;
  }
/*
┌────┐
│■■■■│
│■■■■│
└────┘
*/
  void printCard(){
    string crd = "";
    crd += "┌────┐\n│";
      switch (suit){
        case 0:
        crd += "♥ ";
        break;
        case 1:
        crd += "♦ ";
        break;
        case 2:
        crd += "♣ ";
        break;
        case 3:
        crd += "♠ ";
        break;
      } 
      switch (face){
        case 1:
        crd += "A │\n";
        break;
        case 11:
        crd += "J │\n";
        break;
        case 12:
        crd += "Q │\n";
        break;
        case 13:
        crd += "K │\n";
        break;
        case 10:
        crd += "10│\n";
        break;
        default: 
        crd += to_string(face);
        crd += " │\n";
        break;
      }
      crd += "│    │\n";
      crd += "└────┘\n";
  
  cout << crd;
  //TermPrint::print(crd,2,8,false);
  //return crd;
  }
};

class deck {
private:
card* top;
int decksize;

public:

deck(){
  top = new card(1);
  card* temp = top;
  for(int i = 2; i < 53; i++){
    temp->next = new card(i);
    temp = temp->next;
  }
  decksize = 52;
}

/*
IDK WTF IS GOING ON HERE IDK IF RAND IS DUMB AS SHIT OR ITS REPLIT OR WHAT, TEST MORE ON NOT REPLIT.
*/
  void shuffle(){
    srand(time(NULL));
    int num1;
    int num2;
   // cout << num;
    card* temp = top;
    card* temp2 = top;
    for(int i=0;i<1000;i++){
      temp = top;
      temp2 = top;
      num1 = rand() % decksize;
      for(int i = 0; i <= num1; i++){
          temp = temp->next;
      }
      num2 = rand() % decksize;
      for(int i = 1; i <= num2; i++){
          temp2 = temp2->next;
      }
      swap(temp, temp2);
    } 
  }

void swap(card* a , card* b){
    if (a == b){
       return;  
    }
    card *prevA = NULL;
    card *currA = top;  
    while (currA != a)  
    {  
        prevA = currA;  
        currA = currA->next;
    }  
    card *prevB = NULL;
    card *currB = top;  
    while (currB != b)  
    {  
        prevB = currB;  
        currB = currB->next;  
    }  

    if (currA == NULL || currB == NULL)  
        return;  
      
    if (prevA != NULL)  
        prevA->next = currB;  
    else 
        top = currB;  
      
    if (prevB != NULL)  
        prevB->next = currA;  
    else
        top = currA;  
      

    card* temp = currB->next;  
    currB->next = currA->next;  
    currA->next = temp;  
}

void push(int A) {
    // allocate new memory
    card *anode = new card(A);        // Allocate new memory
    cout << anode->suit;

    // check if list is empty
    if (!top) {
        top = anode;                  // If empty stack just point to new node
    } 
    else {
        anode->next = top;            // Link new node by point its next to old top
        top = anode;                  // Now update top to point to the new node
    }
    decksize++;
}

card* pop() {
    if (!top) {
        return NULL;        // Return NULL for empty stack
    } 
    else {
        card *Temp = top;   // Point to top with temp pointer

        card *a = top; 

        top = top->next;    // Move top of stack 

        delete Temp;        // Delete old top node

        decksize--;
        return a;
    }

}

void print() {
    card *Temp = top;

    while (Temp != NULL) {
      Temp->printCard();
        // cout << "cnum: " << Temp->cnum << " suit: " << Temp->suit << " face: " << Temp->face << endl;
         Temp = Temp->next;
    }
    cout << "Decksize: " << decksize << endl;
    cout << "---------------\n";
}

};

class opponent{
  private:
    card* left;

  public:

    opponent(){
      left = NULL;
    }

void push(card* anode) {

    // check if list is empty
    if (!left) {
        left = anode;  // If empty stack just point to new node
        left->next = NULL;
    } else {
        anode->next = left;            // Link new node by point its next to old top
        left = anode;                  // Now update top to point to the new node
    }

}

int getScore(){
  card* temp = left;
  int score = 0;
  int ace = 0;

  if(left == NULL)
  return score;
  
  while(temp){
    if(temp->face == 1){
       score += 11;
       ace += 1;

    }
    else if(temp->face == 11 || temp->face == 12 || temp->face == 13){
      score += 10;
    }
    else{
    score += temp->face;
    }

    temp = temp->next;
  }

  for(int i = 0;i < ace;i++){
    if(score > 21){
      score -= 10;
    }
  }
  score = 21 - score;
  return score;
}

void print() {
    card *Temp = left;
    while (Temp != NULL) {
      Temp->printCard();
        // cout << "cnum: " << Temp->cnum << " suit: " << Temp->suit << " face: " << Temp->face << endl;
         Temp = Temp->next;
    }
    cout << "---------------\n";
}

void printHide(){
  left->printCard();
    // string cd = "┌────┐\n│■■■■│\n│■■■■│\n└────┘\n";
    // TermPrint::print(cd,2,8,false);
  cout << "┌────┐\n│■■■■│\n│■■■■│\n└────┘\n";
}

void startHand(deck* D){
  push(D->pop());
  push(D->pop());
}

int play(deck* D, int pScore){
  int score = getScore();

  bool risk = true;
  if(pScore < 0){
    risk = false;
  }
  // cout << "--\n";
  // cout << 21-score << endl;
   while(score > pScore && risk){
     push(D->pop());
     score = getScore();
    //  cout << 21-score << endl;
   }
// print();
return getScore();
}

};

class player{
  private:
    card* left;

  public:

    player(){
      left = NULL;
    }

void push(card* anode) {

    // check if list is empty
    if (!left) {
        left = anode;                  // If empty stack just point to new node
        left->next = NULL;
    } else {
        anode->next = left;            // Link new node by point its next to old top
        left = anode;                  // Now update top to point to the new node
    }
}

int getScore(){
  card* temp = left;
  int score = 0;
  int ace = 0;

  if(left == NULL)
  return score;
  
  while(temp){
     if(temp->face == 1){
       score += 11;
       ace += 1;
    }
    else if(temp->face == 11 || temp->face == 12 || temp->face == 13){
      score += 10;
    }
    else{
    score += temp->face;
    }
    temp = temp->next;
  }

  for(int i = 0;i < ace;i++){
    if(score > 21){
      score -= 10;
    }
  }
  score = 21 - score;

  return score;
}

void print() {
    card *Temp = left;

    while (Temp != NULL) {
      Temp->printCard();
        // cout << "cnum: " << Temp->cnum << " suit: " << Temp->suit << " face: " << Temp->face << endl;
         Temp = Temp->next;
    }
    cout << "---------------\n";
}

int play(deck* D, opponent* dealer){
  int score;
  card* selected = left;
  bool fold = false;
  char move;

  cout << "Dealer hand: \n";

  dealer->printHide();

  push(D->pop());
  push(D->pop());

  while(!fold && getScore() >= 0){
    cout << "Current hand: \n";
    print();

  cout << "What do you want to do?(F = fold, H = hit,D = see dealers hand)\n";
  move = getch();
  move = toupper(move);
  TermPrint::clear();
  if(move == 'F')
    fold = true;
  else if(move == 'H'){
  push(D->pop());
  }
  else if(move == 'D'){
  cout << "Dealers hand: \n";
  dealer->printHide();
  }
  else
  cout << "Wrong input.\n";

  }

  if(getScore() == 0){
  cout << "21!\n";
  }
cout << "Your Hand: \n";
print();

  return score;
}

};

int main() {
  deck xd;
  player human;
  opponent cmp;
  // xd.push(26);
  // xd.push(45);
  // xd.push(33);
  // xd.push(20);
  // xd.pop();
  // xd.push(2);
  // xd.push(52);
  // xd.pop();
  // xd.pop();
  // xd.pop();
  // xd.pop();
  // xd.pop();
  // xd.pop();
  // xd.pop();
  // xd.push(52);
  // xd.pop();
  //xd.push(19);

  xd.shuffle();

  //xd.print();
  cmp.startHand(&xd);

  human.play(&xd, &cmp);

  // human.print();

  int playerScore = human.getScore();
  int cmpScore;

  // cout << 21-playerScore << endl;
  // cout << 21-cmp.play(&xd,playerScore) << endl;

  cmpScore = cmp.play(&xd,playerScore);

  cout << "Dealers hand: \n";
  cmp.print();

cout << "Your score: " << 21-playerScore << endl;
cout << "Dealer score: " << 21-cmpScore << endl;

if(playerScore < 0){
  cout << "BUST!\n";
}
else if(cmpScore < 0){
  cout << "DEALER BUST!\n";
}
else{
  if(cmpScore < playerScore){
    cout << "LOSE!\n";
  }
  else if(cmpScore == playerScore){
    cout << "TIE!\n";
  }
  else{
    cout << "WIN!\n";
  }
}
}
