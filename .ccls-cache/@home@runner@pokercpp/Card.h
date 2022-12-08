#ifndef CARD_H
#define CARD_H


#include <iostream>
#include <vector>
using namespace std;

class Card{
private:
  int Cvalue,Csuit;
  string Cname;
  static string NameCard(int value, int suit);
public: 
  Card(int value, int suit);
  int getsuit() { return Csuit; }
  int getvalue() { return Cvalue; }
  string getname() { return Cname; }
};

vector<Card> sortedCards,shuffledDeck;
#endif