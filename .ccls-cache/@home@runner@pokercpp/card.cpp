#include "card.h"
using namespace std;
class card{
  
  static string writename(int value,int suit){
    string suitname;
    switch(suit){
      case 0: suitname = "diamonds";
      case 1: suitname = "clubs";
      case 2: suitname = "hearts";
      case 3: suitname = "spades";
    }
    string valuename;
    switch(value){
      case 9: valuename = "Jack";
      case 10: valuename = "Queen";
      case 11: valuename = "King";
      case 12: valuename = "Ace";
      default: valuename = to_string(value + 2);
      
    }
    return valuename + " of " + suitname;
  }
}; 