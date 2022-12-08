#include <iostream>
#include <vector>
#include "poker.h"
using namespace std;
int getindex(int value, int suit){
  return value  * 4 + suit;
}
void Tstraightflush(){
  vector<Card> testcards = {Card(8,0,getindex(8,0)),Card(9,0,getindex(9,0)),Card(10,0,getindex(10,0)),Card(11,0,getindex(11,0)),Card(12,0,getindex(12,0))};
  cout<< HighestCombo(Hand(testcards)).readHand()<<endl;
}
void Tofakind(){
  vector<Card> testcards = { Card(9,0,getindex(9,0)), Card(4,0,getindex(4,0)) , Card(3,2,getindex(3,2)),Card(2,2,getindex(2,2)),Card(8,1,getindex(8,1)), Card(2,3,getindex(2,3)) };
  cout<< HighestCombo(Hand(testcards)).readHand() ;
}
void TFullHouse(){
  vector<Card> testcards = { Card(8,0,getindex(8,0)), Card(2,0,getindex(2,0)) , Card(3,2,getindex(3,2)),Card(2,2,getindex(2,2)),Card(8,1,getindex(8,1)), Card(2,3,getindex(2,3)) };
  cout<<HighestCombo(testcards).readHand();
}
void Ttwopair(){
  vector<Card> testcards = { Card(8,0,getindex(8,0)), Card(4,0,getindex(4,0)) , Card(3,2,getindex(3,2)),Card(2,2,getindex(2,2)),Card(8,1,getindex(8,1)), Card(2,3,getindex(2,3)) };
  cout<< HighestCombo(Hand(testcards)).readHand() ;
}


int main() {
  Tstraightflush();
  cout<<endl;
  Tofakind();
  cout<<endl;
  TFullHouse();
  cout<<endl;
  Ttwopair();
  return 0;
}