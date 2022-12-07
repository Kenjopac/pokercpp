
#include <iostream>
#include <vector>
using namespace std;

const int NUM_OF_SUITS = 3;
const int NUM_OF_VALUES = 12;
const int CARDS_IN_DECK = 52;

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
struct Card{
Card(int inputValue,int inputSuit ,int Index){
suit = inputSuit;
value = inputValue;
name = NameCard(value,suit);
index = Index;
}
int suit; 
int value;
string name;
int index;
};

vector<Card> sortCards(vector<Card> unsortedCards){
  vector<Card> sortedCards;
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
} 
struct Hand{
vector<Card> cardsInHand;
int countOfValues[13] = {};
int countOfSuits[4] = {};
void updateData(vector<Card> CurrentHand){
  for (Card card: CurrentHand){
    countOfValues[card.value] ++;
    countOfValues[card.suit]++;
  }
}
Hand(vector<Card> InitialHand){
    cardsInHand = sortCards(InitialHand);
    updateData(cardsInHand);
}
void updateHand(vector<Card> CurrentHand){
  cardsInHand = sortCards(CurrentHand);
  updateData( CurrentHand);
}
};