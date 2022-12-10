#include "poker.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;
vector<Card> SORTED_DECK, playingDeck;
vector<Card> shuffleDeck(vector<Card> UnshuffledDeck){
  random_shuffle(UnshuffledDeck.begin(),UnshuffledDeck.end());
  return UnshuffledDeck;
} //returns shuffled parameter deck
void initCards(){ 
  int cardindex = 0;
    for (int value = 0; value <= NUM_OF_VALUES; value++){
      for (int suit = 0;suit <= NUM_OF_SUITS; suit++){
        SORTED_DECK.push_back(Card(value,suit,cardindex));
        cardindex++;
      }
    }
} //initializes sorted deck of cards in order of value, ie: 3 diamonds, 3 club, 3 heart, 3 spade, 4 diamonds etc...
int LENGTH_OF_LINE = 46; //for spacing messages
void CenterMessage(string message, string fill){
  int choppedLines = LENGTH_OF_LINE - message.length();
  choppedLines /= 2;
  for (int counter = 0; counter < choppedLines; counter++){
    cout<<fill;
  }
  cout<<message;
  for (int counter = 0; counter< choppedLines;counter++){
    cout<<fill;
  }
  cout<<endl;
} 
void LeftMessage(string message,string fill){
  cout<<message;
  for (int i = 0; i < LENGTH_OF_LINE - message.length();i++){
    cout<<fill;
  }
  cout<<endl;
}
void RightMessage(string message, string fill){
  
  for (int i = 0; i < LENGTH_OF_LINE - message.length();i++){
    cout<<fill;
  }
  cout<<message;
  cout<<endl;
}
void LeftAndRightMessage(string leftMessage, string rightMessage,string fill){
  cout<<leftMessage;
  for (int i = 0; i < LENGTH_OF_LINE - leftMessage.length() - rightMessage.length();i++){
    cout<<fill;
  }
  cout<<rightMessage;
  cout<<endl;
}

void startscreen(vector<Card> tableCards, int buyInAmount, vector<AI> oponents, Player player){
CenterMessage("Cards", "=");
CenterMessage("","=");
string buyInMessage = "Buy in: ";
buyInMessage.append(to_string(buyInAmount));
CenterMessage(buyInMessage , " ");
LeftAndRightMessage(oponents, string rightMessage, string fill)
}


void MenuLoop(){
        //15             16              15
  CenterMessage("Welcome to Poker","-");
  RightMessage("By Kenneth Wu", "-");
  bool Start = false;
  int StartCash  = 0;
  do {
    cout<<"How much money to start with: ";
    cin>>StartCash;
    if (cin.fail() || StartCash < 10){
      CenterMessage("Money must be an integer >= 10", "*");
    } else{
      LeftMessage("Press any key then enter to start", "-");
      string throwaway;
      cin>>throwaway;
      Start = true;
    }
    
  }while (Start == false);
  GameLoop(StartCash);
}                                                                                
void GameLoop(int startCash){
  initCards();
  
  
}


void EndScreen(bool win){
  
}