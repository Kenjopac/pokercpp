#include <iostream>
#include <vector>
#include <algorithm>
#include "poker.h"
using namespace std;
int Straight(Hand hand){
  int straightCounter = 0; 
      for (int i = NUM_OF_VALUES ; i > 0 ;i--){
        if(hand.countOfValues[i] == hand.countOfValues[i - 1] + 1){
          straightCounter++;
          
        } else{
          straightCounter = 0;
        }
        if (straightCounter == 4){
          return hand.countOfValues[i+3];
        }
      }
  return -1;
}
int StraightFlush(Hand hand){ //assumes cards in hand are sorted
  for (int suit : hand.countOfSuits){
    if (suit >= 5){ // first test if there are enough of the suit, not enough cards for multiple straight flushes, in order is fine
      //then make new hand of only same suited cards
      vector<Card> cardsOfSameSuit;
      for (Card card: hand.cardsInHand){
        cout<<suit<<endl;
        cout<<card.suit<<endl;
        if(card.suit == suit){
          
          cardsOfSameSuit.push_back(card);
          
        }
      }
      return Straight(Hand(cardsOfSameSuit)); // assumes cards are sorted and all of same suit, if next card is one less, then add to straight counter until straight counter is nSpacesInBetweenStraightLong, start from back of sorted array to return largest straight. 
    }
  }
  return -1;
}; //returns index of highest card if straight flush
int OfAKind(int getRepeats, Hand hand){ 
  for(int value:hand.countOfValues){
    if (value == getRepeats){
      return value;
    }
  }
  return -1;
}//returns value of a repeated card 
vector<Card> SORTED_DECK, playingDeck;
 // returns card name given value and suit
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
int getindex(int value, int suit){
  return value  * 4 + suit;
}
void TestFunc(){
  vector<Card> testhand = {playingDeck[0],       playingDeck[1],playingDeck[2],playingDeck[3],playingDeck[4]};
  for (Card card: testhand){
    cout<<card.name<<" ";
  }
  cout<<endl;
  vector<Card>sortedTestHand = sortCards(testhand);
  for (Card card : sortedTestHand){
    cout<<card.name<<" ";
  }
  cout<<endl;
}
void Tstraightflush(){
  vector<Card> testcards = {Card(8,0,getindex(8,0)),Card(9,0,getindex(9,0)),Card(10,0,getindex(10,0)),Card(11,0,getindex(11,0)),Card(12,0,getindex(12,0))};
 
  cout<< StraightFlush( Hand(testcards))<<endl;
}
int main() {
  initCards();
  playingDeck = shuffleDeck(SORTED_DECK);
  TestFunc();
  Tstraightflush();
  return 0;
  
}