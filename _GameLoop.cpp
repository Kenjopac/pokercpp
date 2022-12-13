#include "poker.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;
int LENGTH_OF_LINE = 60; //for spacing messages
int NUM_OF_OPONENTS = 2;

/*
int getIndex(int value, int suit){
  return value * 4 + suit;
} // index of a card given value and suit
*/
vector<Card> SORTED_DECK, playingDeck;
vector<Card> shuffleDeck(vector<Card> UnshuffledDeck){
  random_shuffle(UnshuffledDeck.begin(),UnshuffledDeck.end());
  return UnshuffledDeck;
} //returns shuffled parameter deck
vector<AI> Oponents;
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
string roundNames[5] = {"pre-flop","flop","turn","river","showdown"};
cout<<endl;
CenterMessage(roundNames[roundNum]," ");
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
  int StartCash;
  while (Start == false) {
    int input;
    cout<<endl;
    cout<<"How much money to start with: ";
    cin>>input;
    cout<<endl;
    cin.clear();
    cin.ignore(LARGE_NUMBER, '\n' );
    if (cin.fail() || input < 10){
      CenterMessage("Money must be an integer >= 10", "*");
    } else {
      LeftMessage("Press any key then enter to start", "-");
      string throwaway;
      cin>>throwaway;
      Start = true;
      StartCash = input; 
    }
  };
  Oponents.clear();
  for (int i = 0; i < NUM_OF_OPONENTS;i++){
    Oponents.push_back(AI(StartCash,"thing " + to_string(i)));
  }
  Player player = Player(StartCash, "Kenneth");
  GameLoop(StartCash,player);
} 

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
  vector<Card> emptyhand = {};
  player.currentCards.updateHand(emptyhand);
  
  int DeckIndexer = 0;
  
  for (int i = 0;i <oponents.size() ;i++){
    oponents[i].currentCards.updateHand(emptyhand);
    oponents[i].currentCards.addCard(playingDeck[DeckIndexer]);
    DeckIndexer++;
    oponents[i].currentCards.addCard(playingDeck[DeckIndexer]);
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
      DisplayScreen(tableCards, potAmount, player, roundNum);
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
      
  } 
  
  //if all checked then move on
}

void RoundLoop( Player& player,int& deckIndex, int& roundNumber,vector<Card>& table, int& potAmount){
  int HowManyPlayersFold = 0;
  if (player.roundActive == false){
    HowManyPlayersFold++;
  }
  for (AI oponent: Oponents){
    if (oponent.roundActive == false){
      HowManyPlayersFold++;
    }
  }
  if (HowManyPlayersFold <= 1){
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
  
  } 
  roundNumber++;
}

void getWinner( Player& player,vector<Card> table, int potAmount){
  vector<Card> playerOne = player.currentCards.cardsInHand;
  vector<Card> Oponent0 = Oponents[0].currentCards.cardsInHand;
  vector<Card> Oponent1 = Oponents[1].currentCards.cardsInHand;
  for (Card card: table){
    playerOne.push_back(card);
    Oponent0.push_back(card);
    Oponent1.push_back(card);
  }
  
  player.currentCardsPlusTable.updateHand(playerOne);
  Oponents[0].currentCardsPlusTable.updateHand(Oponent0);
  Oponents[1].currentCardsPlusTable.updateHand(Oponent1);
  
  player.highestHandValue = HighestComboValue(player.currentCardsPlusTable);
  Oponents[0].highestHandValue = HighestComboValue(Oponents[0].currentCardsPlusTable);
  Oponents[1].highestHandValue = HighestComboValue(Oponents[1].currentCardsPlusTable);
  
  float maxVal = 0 ;
  if (player.roundActive == true){
      maxVal = maxVal > player.highestHandValue ? maxVal: player.highestHandValue;
  }
  for (AI oponent : Oponents){
    if (oponent.roundActive == true){
      maxVal = maxVal > oponent.highestHandValue ? maxVal: oponent.highestHandValue;
    }
  }
  cout<<maxVal <<endl;
  int numberOfWinners = 0;
  for (AI oponent: Oponents){
    if (oponent.highestHandValue == maxVal && oponent.roundActive != false){
      numberOfWinners++;
    } 
  }
  if (player.highestHandValue == maxVal && player.roundActive != false){
    numberOfWinners++;
    player.Balance += potAmount / numberOfWinners > player.winnablePot ? player.winnablePot : potAmount / numberOfWinners;
  }

  if (Oponents[0].highestHandValue == maxVal && Oponents[0].roundActive != false){
    Oponents[0].Balance += potAmount / numberOfWinners > Oponents[0].winnablePot ? Oponents[0].winnablePot : potAmount / numberOfWinners;
  }
  if (Oponents[1].highestHandValue == maxVal && Oponents[1].roundActive != false){
    Oponents[1].Balance += potAmount / numberOfWinners > Oponents[1].winnablePot ? Oponents[1].winnablePot : potAmount / numberOfWinners;
  }
  
  cout<<" "<<endl;
  CardDisplay(table);
  LeftMessage(Oponents[0].name + "("+ Oponents[0].getBalance() + "$): " , "-");
  LeftMessage(Oponents[0].currentCards.readHand(), "-");
  RightMessage(to_string(Oponents[0].highestHandValue)," ");
  LeftMessage(Oponents[1].name + "("+ Oponents[1].getBalance() + "$): " , "-");
  LeftMessage(Oponents[1].currentCards.readHand(), "-");
  RightMessage(to_string(Oponents[1].highestHandValue)," ");
  CenterMessage("Your balance is "+ to_string(player.Balance), " ");
  CenterMessage(player.currentCards.readHand(), " ");
  RightMessage(to_string(player.highestHandValue)," ");
  
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
  for (int oponentindex = 0; oponentindex <Oponents.size();oponentindex++){
    if (Oponents[oponentindex].Balance > buyIn){
    Oponents[oponentindex].roundActive = true;
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
  
  GetDecisions(player,roundNum,table,potAmount);
  RoundLoop(player, deckIndexer, roundNum, table,potAmount);
  RoundLoop(player, deckIndexer, roundNum, table,potAmount);
  RoundLoop(player, deckIndexer, roundNum, table,potAmount);
  DisplayScreen(table, potAmount, player, roundNum);
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