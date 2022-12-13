#include <iostream>
#include <vector>
#include "poker.h"
using namespace std;
string NameCard(int value, int suit){
    string suitname;
    switch(suit){
      case 0: suitname = "diamonds"; break;
      case 1: suitname = "clubs"; break;
      case 2: suitname = "hearts";break;
      case 3: suitname = "spades";break;
      default: suitname = "none";break;
    }
    string valuename;
    switch(value){
      case 9: valuename = "Jack";break;
      case 10: valuename = "Queen";break;
      case 11: valuename = "King";break;
      case 12: valuename = "Ace";break;
      default: valuename = std::to_string(value + 2); break;
      
    }
    return valuename + " of " + suitname;
  };
vector<Card> sortCards(vector<Card> unsortedCards){
  vector<Card> sortedCards = {};
  int onehotvec[52] = {};
  
  for (int i = 0; i <unsortedCards.size();i++){
    onehotvec[unsortedCards[i].index] = i+1; 
  }
  for (int i : onehotvec){
    if (i != 0){
      sortedCards.push_back(unsortedCards[i-1]);
    }
  }
  return sortedCards;
};

