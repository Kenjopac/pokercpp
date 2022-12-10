
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

//Set of cards
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
//Player class
struct Player{
std::string name;
bool roundActive;
int Balance;
Hand currentCards;
float highestHandValue;
Hand currentCardsPlusTable;
int winnablePot; //called each gameloop
bool hasChecked;//condition for checking if Checked
int PendingDecision(int roundNum, int pendingAmount);
Player(int balance, std::string inputName){
Balance = balance; 
name = inputName;
roundActive = true;
currentCards = Hand();
}
};
//oponent class
struct AI {
int winnablePot;
std::string name;
bool roundActive;
int Balance;
Hand currentCards;
float highestHandValue; 
Hand currentCardsPlusTable;
bool hasChecked;//condition for checking if Checked1
std::string decisionMessage = "\"time to win!\"";
void buyIn(int buyIn, int& potAmount);
int MakeDecision(int pendingCall,int potAmount, int roundCounter);
/*
void PreFlopDecision(int potAmount, int roundCounter, std::vector<int> bets);
void FlopDecision(int potAmount, int roundCounter, std::vector<int> bets);
void TurnDecision(int potAmount, int roundCounter, std::vector<int> bets);
void RiverDecision(int potAmount, int roundCounter, std::vector<int> bets);
void ShowdownDecision(int potAmount, int roundCounter, std::vector<int> bets);
*/
AI(int balance, std::string inputName){
  Balance = balance;
  name = inputName;
  roundActive =true;
  currentCards = Hand();
}
};

//Return Highest Combo
float HighestComboValue(Hand hand);

//Handle Game Logic
void MenuLoop();
void GameLoop(int startCash,Player& player);
void EndScreen(bool win);