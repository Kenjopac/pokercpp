
#include <iostream>
#include <vector>

//constants
const int NUM_OF_SUITS = 3;
const int NUM_OF_VALUES = 12;
const int CARDS_IN_DECK = 52;

//Card logic
std::string NameCard(int value, int suit);
struct Card{
Card(int inputValue,int inputSuit ,int Index){
suit = inputSuit;
value = inputValue;
name = NameCard(value,suit);
index = Index;
}
int suit; 
int value;
std::string name;
int index;
};

std::vector<Card> sortCards(std::vector<Card> unsortedCards);


//hand struct
struct Hand{
bool isEmpty = true;
std::vector<Card> cardsInHand;
int countOfValues[NUM_OF_VALUES +1] = {};
int countOfSuits[NUM_OF_SUITS + 1] = {};
void updateData(std::vector<Card> CurrentHand);
void updateHand(std::vector<Card> CurrentHand);
void addCard(Card card);
std::string readHand();
void removeCard(Card removeThisCard);
Hand(){
  isEmpty = true;
}
Hand(std::vector<Card> InitialHand){
    cardsInHand = sortCards(InitialHand);
    updateData(cardsInHand);
    isEmpty = false;
};
};

struct Player{
int Balance;
Hand currentCards;
Hand highestHand;
void PayAmount(int MoneyOut);
void GainAmount(int MoneyIn);
int MakeDecision(int amount);
Player(int balance, Hand hand){
Balance = balance; 
currentCards = hand;
};
};

struct AI {
bool active;
int Balance;
Hand currentCards;
Hand highestHand; 
Hand tableCards;
void updateData(Card NewCard);
void buyIn(int buyIn);
int MakeDecision(int pendingCall,int potAmount, int roundCounter, std::vector<int> bets);
/*
void PreFlopDecision(int potAmount, int roundCounter, std::vector<int> bets);
void FlopDecision(int potAmount, int roundCounter, std::vector<int> bets);
void TurnDecision(int potAmount, int roundCounter, std::vector<int> bets);
void RiverDecision(int potAmount, int roundCounter, std::vector<int> bets);
void ShowdownDecision(int potAmount, int roundCounter, std::vector<int> bets);
*/
AI(int balance, Hand hand){
  Balance = balance;
  currentCards = hand;
}
};


//Return Highest Combo
Hand HighestCombo(Hand hand);

//Handle Game Logic
void MenuLoop();
void GameLoop(int startCash);
void EndScreen();