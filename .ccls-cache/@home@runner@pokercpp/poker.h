
#include <iostream>
#include <vector>
using namespace std;
//constants
const int NUM_OF_SUITS = 3;
const int NUM_OF_VALUES = 12;
const int CARDS_IN_DECK = 52;

//Card logic
string NameCard(int value, int suit);
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
vector<Card> sortCards(vector<Card> unsortedCards);

//hand struct
struct Hand{
vector<Card> cardsInHand;
int countOfValues[13] = {};
int countOfSuits[4] = {};
void updateData(vector<Card> CurrentHand){
  for (Card card: CurrentHand){ 
    countOfValues[card.value]++;
    countOfSuits[card.suit]++;
  }
};
Hand(){
  cout<<"created empty hand";
}
Hand(vector<Card> InitialHand){
    cardsInHand = sortCards(InitialHand);
    updateData(cardsInHand);
};
void updateHand(vector<Card> CurrentHand){
  cardsInHand = sortCards(CurrentHand);
  updateData(CurrentHand);
};
void addCard(Card card){
  cardsInHand.push_back(card);
  updateData(cardsInHand);
}
string readHand(){
  string allCards;
  for (Card card: cardsInHand){
    allCards.append(" , ");
    allCards.append(card.name);
  }
  return allCards;
};
};

//Return Combos if there is one
Hand Straight(Hand hand);
Hand StraightFlush(Hand hand);
Hand Flush(Hand hand);
Hand OfAKind(int getRepeats, Hand hand);

//Handle Game Logic
void MenuLoop();
void GameLoop(int startCash);
void EndScreen();