#include <iostream>
#include <vector>
#include "poker.h"
using namespace std;


void AI::buyIn(int buyIn, int& potAmount){
  if (roundActive == true){
    potAmount += buyIn;
    Balance -= buyIn;
  }
}
//factor in current balance, factor in current hand, factorin table hand
int AI::MakeDecision(int pendingCall,int potAmount, int roundCounter){
    if (roundActive){
    if (Balance < pendingCall){
      roundActive = false;
      decisionMessage = "I fold :(";
      return pendingCall;
    } else {
      Balance -= pendingCall;
      decisionMessage = "I call!";
      hasChecked = true;
      return pendingCall;
    }
      } else{
      return pendingCall;
      }
};

//active is round active, at the end of each game reactive all AI if they are above buy in amount