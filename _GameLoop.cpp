#include "poker.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;
int LENGTH_OF_LINE = 60; //for spacing messages
int getIndex(int value, int suit){
  return value * 4 + suit;
} // index of a card given value and suit

vector<Card> SORTED_DECK, playingDeck;
vector<Card> shuffleDeck(vector<Card> UnshuffledDeck){
  random_shuffle(UnshuffledDeck.begin(),UnshuffledDeck.end());
  return UnshuffledDeck;
} //returns shuffled parameter deck
vector<AI> Oponents;
int NUM_OF_OPONENTS = 2;
void initCards(){ 
  int cardindex = 0;
    for (int value = 0; value <= NUM_OF_VALUES; value++){
      for (int suit = 0;suit <= NUM_OF_SUITS; suit++){
        SORTED_DECK.push_back(Card(value,suit,cardindex));
        cardindex++;
      }
    }
} //initializes sorted deck of cards in order of value, ie: 3 diamonds, 3 club, 3 heart, 3 spade, 4 diamonds etc...
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

void CardDisplay(vector<Card> tableCards){
  if (tableCards.size() == 0){
    CenterMessage("Table's cards will be", "=");
    CenterMessage("displayed here", "=");
  } 
  if(tableCards.size() >= 3){
    int padLength = LENGTH_OF_LINE;
    for (int cardLooper = 0;cardLooper < 3;cardLooper++){
      padLength -= tableCards[cardLooper].name.length();
    }
    if (padLength < 0){
      padLength =0;
    }
    padLength /= 4;
    for (int cardLooper = 0;cardLooper < 3;cardLooper++){
      for (int i = 0; i< padLength;i++){
        cout<<"=";
      }
      cout<<tableCards[cardLooper].name;
    }
    for (int i = 0; i< padLength;i++){
        cout<<"=";
    }
    cout<<endl;
  }
  if (tableCards.size() == 4){
    LeftMessage(tableCards[3].name, "=");
  } else if (tableCards.size() == 5){
    LeftAndRightMessage(tableCards[3].name,tableCards[4].name,"=");
  }else{
    LeftMessage("", "=");
  }
  
}
void AIDisplay(){
LeftMessage("", "-");
string firstOponentTag = Oponents[0].name;
firstOponentTag += "(";
firstOponentTag += to_string(Oponents[0].Balance);
firstOponentTag += "$)";
string secondOponentTag = Oponents[1].name;
secondOponentTag += "(";
secondOponentTag += to_string(Oponents[1].Balance);
secondOponentTag += "$)";
LeftAndRightMessage(firstOponentTag, secondOponentTag, " ");
LeftAndRightMessage(Oponents[0].decisionMessage, Oponents[1].decisionMessage, " ");
LeftMessage("", "-");
}
void PlayerUI(Player player, int roundNum){
  if (roundNum != 0){
  string displayCards;
  displayCards += player.currentCards.cardsInHand[0].name;
  displayCards += "______";
  displayCards += player.currentCards.cardsInHand[1].name;
  CenterMessage(displayCards, "_");
  
  }else {
  CenterMessage("Your cards will be here", "_");
  }
  CenterMessage("Current Balance: " + to_string(player.Balance), "_");
}

void DisplayScreen(vector<Card> tableCards, int pot, Player player,int roundNum){
CardDisplay(tableCards);
string buyInMessage;
if (roundNum == 0){
buyInMessage = "Buy in: ";
buyInMessage.append(to_string(pot));
} else{
buyInMessage = "Pot Amount: ";
buyInMessage.append(to_string(pot));
}
CenterMessage(buyInMessage , " ");
AIDisplay();
PlayerUI(player, roundNum);
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
  Oponents.clear();
  for (int i = 0; i < NUM_OF_OPONENTS;i++){
    Oponents.push_back(AI(StartCash,"thing " + to_string(i)));
  }
  Player player = Player(StartCash, "Kenneth");
  GameLoop(StartCash,player);
}                                                                           
vector<Card> testTable = {Card(2,2,getIndex(2,2)),Card(3,2,getIndex(3,2)),Card(8,0,getIndex(8,0)),Card(1,3,getIndex(1,3)),Card(5,2,getIndex(5,2)) };

bool checkWin( vector<AI> oponents, int buyIn){
  if (oponents[0].Balance < buyIn && oponents[1].Balance < buyIn){
    return true;
  } else{
    return false;
  }
};
bool checkLoss(Player player, int buyIn){
  if (player.Balance < buyIn){
    return true;
  } else {
    return false;
  }
};
void DealCards(vector<AI>& oponents, Player& player){
  int DeckIndexer = 0;
  
  for (AI a : oponents){
    a.currentCards.addCard(playingDeck[DeckIndexer]);
    DeckIndexer++;
    a.currentCards.addCard(playingDeck[DeckIndexer]);
    DeckIndexer++;
  }
  player.currentCards.addCard(playingDeck[DeckIndexer]);
  DeckIndexer++;
  player.currentCards.addCard(playingDeck[DeckIndexer]);
  DeckIndexer++;
}

void GetDecisions(Player& player, int roundNum, vector<Card> tableCards, int& potAmount){
  int pendingAmount = 0;
  if (player.roundActive){
    player.hasChecked = false;
  } 
  for (AI oponent: Oponents){
    if (oponent.roundActive){
      player.hasChecked = false;
    }
  }
  while(!(player.hasChecked && Oponents[0].hasChecked && Oponents[1].hasChecked)){
      pendingAmount = player.PendingDecision(roundNum, pendingAmount);
      if (player.hasChecked == false){
        player.hasChecked = true;
        Oponents[0].hasChecked = false;
        Oponents[1].hasChecked = false;
      }
      potAmount += pendingAmount;
      pendingAmount = Oponents[0].MakeDecision(pendingAmount, potAmount, roundNum);
      if (Oponents[0].hasChecked == false){
        Oponents[0].hasChecked = true;
        Oponents[1].hasChecked = false;
        player.hasChecked = false;
      }
      potAmount += pendingAmount;
      pendingAmount = Oponents[1].MakeDecision(pendingAmount, potAmount, roundNum);
      if (Oponents[1].hasChecked == false){
        Oponents[1].hasChecked = true;
        Oponents[0].hasChecked = false;
        player.hasChecked = false;
      }
      potAmount += pendingAmount;
      DisplayScreen(tableCards, potAmount, player, roundNum);
  } 
  
  //if all checked then move on
}

void RoundLoop( Player& player,int& deckIndex, int& roundNumber,vector<Card>& table, int& potAmount){
  int currentDeckIndex = deckIndex;
  if (roundNumber == 1){
    
    while (deckIndex < currentDeckIndex + 3){
      table.push_back(playingDeck[deckIndex]);
      deckIndex++;
    }
    GetDecisions(player, roundNumber,table, potAmount);
  } else if (roundNumber == 2 || roundNumber == 3){
    table.push_back(playingDeck[deckIndex]);
    deckIndex++;
    GetDecisions(player, roundNumber,table, potAmount);
  }
  roundNumber++;
}

void getWinner( Player& player,vector<Card> table, int potAmount){
  for (Card card: table){
    player.currentCardsPlusTable.addCard(card);
    Oponents[0].currentCardsPlusTable.addCard(card);
    Oponents[1].currentCardsPlusTable.addCard(card);
  }
  player.highestHandValue = HighestComboValue(player.currentCardsPlusTable);
  Oponents[0].highestHandValue = HighestComboValue(Oponents[0].currentCardsPlusTable);
  Oponents[1].highestHandValue = HighestComboValue(Oponents[1].currentCardsPlusTable);
  int maxVal = player.highestHandValue > Oponents[0].highestHandValue ? player.highestHandValue : Oponents[0].highestHandValue;
  maxVal = maxVal > Oponents[1].highestHandValue ? maxVal: Oponents[1].highestHandValue;
  
  int numberOfWinners = 0;
  for (AI oponent: Oponents){
    if (oponent.highestHandValue == maxVal){
      numberOfWinners++;
    } 
  }
  if (player.highestHandValue == maxVal){
    numberOfWinners++;
    player.Balance += potAmount / numberOfWinners > player.winnablePot ? player.winnablePot : potAmount / numberOfWinners;
  }
  for (AI oponent: Oponents){
    if (oponent.highestHandValue == maxVal){
      oponent.Balance += potAmount / numberOfWinners  > oponent.winnablePot? player.winnablePot: potAmount / numberOfWinners;
    }
  }
  cout<<" split wins "<<numberOfWinners<<endl;
  cout<<"max value: "<<maxVal<<" player value: "<<player.highestHandValue<<endl;
  cout<<" op0 value: "<<Oponents[0].highestHandValue<<endl;
  cout<<" op1 value: "<<Oponents[1].highestHandValue<<endl;
  cout<<"pot amount: " <<potAmount<<endl;
  cout<<" "<<endl;
  CardDisplay(table);
  LeftMessage(Oponents[0].name + "("+ to_string(Oponents[0].Balance) + "$): " , "-");
  CenterMessage(Oponents[0].currentCards.readHand(), "-");
  LeftMessage(Oponents[1].name + "("+ to_string(Oponents[1].Balance) + "$): " , "-");
  CenterMessage(Oponents[1].currentCards.readHand(), "-");
  CenterMessage("Your balance is "+ to_string(player.Balance), " ");
  CenterMessage(player.currentCards.readHand(), " ");
  
}

void GameLoop(int startCash, Player& player){
  
  initCards();
  int buyIn = 10;
  int roundNum = 0;
  int deckIndexer = 0;
  int potAmount = 0;
  playingDeck = SORTED_DECK;
  
  do{
  if (player.Balance > buyIn){
    player.roundActive = true;
  }
  for (AI oponent: Oponents){
    if (oponent.Balance > buyIn){
    oponent.roundActive = true;
    }
  }
  roundNum = 0;
  vector<Card> table = {};
  playingDeck = shuffleDeck(playingDeck);
  DealCards(Oponents,player);
  deckIndexer = 6;
    
  DisplayScreen(table, buyIn, player, roundNum);
  
  potAmount = player.PendingDecision(roundNum, buyIn);
    
  Oponents[0].buyIn(buyIn, potAmount);
    
  Oponents[1].buyIn(buyIn, potAmount);
  
  roundNum++;
    
  player.winnablePot = player.Balance;
  Oponents[0].winnablePot = Oponents[0].Balance;
  Oponents[1].winnablePot = Oponents[1].Balance;
  GetDecisions(player, roundNum, table, potAmount);
  RoundLoop(player, deckIndexer, roundNum, table,potAmount);
  RoundLoop(player, deckIndexer, roundNum, table,potAmount);
  RoundLoop(player, deckIndexer, roundNum, table,potAmount);
  getWinner(player,table, potAmount);
  cout<<endl;
  cout<<"enter any Key to Continue (X to restart): ";
  char ThrowAway;
  cin>>ThrowAway;
  if (ThrowAway == 'X' || ThrowAway == 'x'){
    break;
  } else{
  buyIn += 2;
  }
  }while(!checkWin(Oponents, buyIn) || !checkLoss(player,buyIn));
  EndScreen(checkLoss(player,buyIn));
}


void EndScreen(bool lost){
  if (lost){
    CenterMessage("You Lost!", " ");
    CenterMessage("", "*");
  } else{
    CenterMessage("You Won!", " ");
    CenterMessage("", "*");
  }
  MenuLoop();
}