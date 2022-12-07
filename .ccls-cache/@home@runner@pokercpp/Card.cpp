#include "Card.h"
using namespace std;

Card::Card(int value, int suit){
  Cvalue = value;
  Csuit = suit;
  Cname = NameCard (value,suit);
};



