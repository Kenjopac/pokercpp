#include "poker.h"
#include <iostream>
#include <vector>
using namespace std;


int PromptLoop(int pendingAmount, int& Balance, bool& hasChecked, bool& roundActive){ 
  while(true){
  char input;
  cout<<pendingAmount<<"$ Pending.   F to fold, C to call, R to raise: ";
  cin>>input;
  cin.clear();
  cin.ignore(LARGE_NUMBER, '\n' );
if (cin.fail()){
  cout<<"Must be single letter F, C, or R"<<endl;
}else{
    switch(input){
      case 'F': case 'f':
        hasChecked = true;
        roundActive = false;
        return pendingAmount;
      case 'C': case 'c':
        Balance -= pendingAmount;
        if (Balance < 0 ){
          Balance = 0;
        }
        hasChecked = true;
        return pendingAmount;
      case 'R':case 'r':
        cout<<"Raise how much: ";
        if (Balance <= pendingAmount){
          cout<<"Balance must be greater than "<<pendingAmount<<"$ to raise"<<endl;
          break;
        } else{
          int raiseAmount;
          cin>>raiseAmount;
          if (cin.fail() || raiseAmount > Balance - pendingAmount){
            cout<<"Raise must be integer greater than Balance of: "<<Balance - pendingAmount<<"$"<<endl;
            break;
          } else{
            hasChecked = false;
            Balance -= raiseAmount;
            Balance -= pendingAmount;
            return raiseAmount + pendingAmount;
          }
        }
      default:
        cout<<"input must be single letter F, C, or R"<<endl;
    }
}
  }
};
int Player::PendingDecision(int roundNum, int pendingAmount){
  if (roundActive){
  if (roundNum == 0){
      char input;
      cout<<"Press any key to buy in: ";
      cin>>input;
      Balance -= pendingAmount;
      return pendingAmount;
  } else{
    return PromptLoop(pendingAmount, Balance,hasChecked,roundActive);
  }
  } else {
    hasChecked = true;
    return pendingAmount;
  }
};