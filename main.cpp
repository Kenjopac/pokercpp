#include <iostream>
#include <vector>
#include <algorithm>
#include "poker.h"
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
  cout<< Flush(Hand(testcards)).readHand()<<endl;
}
void Tofakind(){
  vector<Card> testcards = { Card(8,0,getindex(8,0)), Card(4,0,getindex(4,0)) , Card(3,2,getindex(3,2)),Card(2,2,getindex(2,2)),Card(8,1,getindex(8,1)), Card(2,3,getindex(2,3)) };
  cout<< OfAKind(2,Hand(testcards)).readHand() ;
}




int main() {
  MenuLoop();
  return 0;
}