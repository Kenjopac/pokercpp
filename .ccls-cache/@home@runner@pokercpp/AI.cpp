#include <iostream>
#include <vector>
#include "poker.h"
using namespace std;

void AI::updateData(Card NewCard){
  if (active == true){
  currentCards.addCard(NewCard);
  highestHand = HighestCombo(currentCards);
  }
}
void AI::buyIn(int buyIn){
  if (active == true){
    Balance -= buyIn;
  }
}
//factor in current balance, factor in current hand, factorin table hand
int AI::MakeDecision(int pendingCall,int potAmount, int roundCounter, std::vector<int> bets){
    
};

//active is round active, at the end of each game reactive all AI if they are above buy in amount