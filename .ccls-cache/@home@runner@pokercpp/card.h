#ifndef CARD_H
#define CARD_H


#include <iostream>
using namespace std;

class Card{
private:
  int Cvalue,Csuit;
  string Cname;  
public: 
  Card(int value, int suit);
  int getsuit() { return Csuit; }
  int getvalue() { return Cvalue; }
  string getname() { return Cname; }
};

#endif