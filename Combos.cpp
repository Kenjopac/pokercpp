#include <iostream>
#include <vector>
#include "poker.h"
using namespace std;
vector<Card> blankHand = {};
void Straight(Hand hand,Hand& rethand){
  vector<Card> straight; 
      int cardCounterReversed = hand.cardsInHand.size() - 1;
      for (int valueCounterReverse = NUM_OF_VALUES  ; valueCounterReverse >= 0 ;valueCounterReverse--){
        if (hand.countOfValues[valueCounterReverse] >=  1){
          straight.push_back(hand.cardsInHand[cardCounterReversed]);
          cardCounterReversed -= hand.countOfValues[valueCounterReverse];
        } else{
          straight.clear();
        }
        if (straight.size() == 5){          
          rethand.updateHand(straight);
        }
      }
}; // returns highest value of straight,
void Flush(Hand hand, Hand& rethand){
  for (int suit = 0; suit < sizeof(hand.countOfSuits);suit++){
    if (hand.countOfSuits[suit] >=5){
      vector<Card> cardsOfSameSuit;
      for (int cardCounterReversed = hand.cardsInHand.size(); cardCounterReversed >= 0; cardCounterReversed--){
        if (hand.cardsInHand[cardCounterReversed].suit == suit){
          cardsOfSameSuit.push_back(hand.cardsInHand[cardCounterReversed]);
        }
        if (cardsOfSameSuit.size() == 5){
          rethand.updateHand(cardsOfSameSuit);
        }
      }
    }
  }
};
void StraightFlush(Hand hand,Hand&rethand){ // add highest value...
  for (int suit = 0; suit < sizeof(hand.countOfSuits); suit++){
    if (hand.countOfSuits[suit] >= 5){ // first test if there are enough of the suit, not enough cards for multiple straight flushes, in order is fine
      //then make new hand of only same suited cards
      vector<Card> cardsOfSameSuit;
      
      for (Card card: hand.cardsInHand){
        if(card.suit == suit){
          cardsOfSameSuit.push_back(card);
        }
      }
      Straight(Hand(cardsOfSameSuit),rethand); // assumes cards are sorted and all of same suit, if next card is one less, then add to straight counter until straight counter is nSpacesInBetweenStraightLong, start from back of sorted array to return largest straight. 
      
    }
  }
  
}; //returns index of highest card if straight flush
void OfAKind(int getRepeats, Hand hand, Hand& rethand){ 
  vector<Card> sameValue;
  for (int valueCounterReversed = NUM_OF_VALUES;valueCounterReversed >= 0;valueCounterReversed --){
    if (hand.countOfValues[valueCounterReversed] == getRepeats){
      for (Card card: hand.cardsInHand){
        
        if (card.value == valueCounterReversed){
          
          sameValue.push_back(card);
        }
      }
      rethand.updateHand(sameValue);
    }
  }
};//returns value of a repeated card 
void FullHouse(Hand hand,Hand& rethand){
  vector<Card> fullHouse;
  
  bool hastwo = false;
  bool hasthree = false;
  for (int i = NUM_OF_VALUES; i >= 0; i--){
    if (hand.countOfValues[i] == 3){
      
      hasthree = true;
    } else if (hand.countOfValues[i] == 2){
      hastwo = true;
    } 
  }
  if (hasthree && hastwo){
    OfAKind(3, hand, rethand); //add triple
    Hand twoOfAKind  = Hand();
    OfAKind(2, hand,twoOfAKind);
    for (Card card: twoOfAKind.cardsInHand){
      rethand.addCard(card);
    }
  }else {
  rethand.updateHand(blankHand);
  }
  
};
void TwoPair(Hand hand, Hand& rethand){
  int pairs = 0;
  for (int value: hand.countOfValues){
    if (value == 2){
      pairs++;
    }
  }
  if (pairs >= 2){
    OfAKind(2, hand,rethand);
    for (Card card: rethand.cardsInHand){
      hand.removeCard(card);
    }
    Hand newTwoPair = Hand();
    OfAKind(2,hand,newTwoPair);
    for (Card card: newTwoPair.cardsInHand){
      rethand.addCard(card);
    }
  } else{
  rethand.updateHand(blankHand);
  }
};
/*
Hand HighestCombo(Hand hand){
  if (StraightFlush(hand).isEmpty == false ){
    return StraightFlush(hand);
  } else if (OfAKind(4,hand).isEmpty == false ){
    return OfAKind(4,hand);
  } else if (FullHouse(hand).isEmpty == false){
    return FullHouse(hand);
  } else if (Flush(hand).isEmpty == false){
    return Flush(hand);
  } else if (Straight(hand).isEmpty == false){
    return Straight(hand);
  } else if (OfAKind(3,hand).isEmpty == false){
    return OfAKind(3,hand);
  } else if (TwoPair(hand).isEmpty == false){
    return TwoPair(hand);
  } else if (OfAKind(2,hand).isEmpty == false){
    return OfAKind(2,hand);
  } else {
    return hand;
  }
};
*/
float HighestComboValue(Hand hand){
  if (hand.isEmpty == true){
    return 0;
  } else{
  Hand rethand = Hand();
  StraightFlush(hand,rethand);
  int LAST_CARD_COMBO = 4;
  int MIDDLE_CARD_COMBO = 2;
  int FIRST_CARD = 0;
  if (rethand.isEmpty == false) {
    return 8 + (float)rethand.cardsInHand[LAST_CARD_COMBO].value / 100;
  } else{
    rethand.updateHand(blankHand);
  } 
  OfAKind(4, hand, rethand);
  if (rethand.isEmpty == false) {
    return 7 + (float)rethand.cardsInHand[FIRST_CARD].value / 100;
  } else{
    rethand.updateHand(blankHand);
  } 
  FullHouse(hand, rethand);
  if (rethand.isEmpty == false) {
    return 6 + (float)rethand.cardsInHand[MIDDLE_CARD_COMBO].value / 100;
  } else{
    rethand.updateHand(blankHand);
  } 
  Flush(hand,rethand);
  if (rethand.isEmpty == false){
    return 5 + (float)rethand.cardsInHand[LAST_CARD_COMBO].value / 100;
  }else{
    rethand.updateHand(blankHand);
  } 
  Straight(hand,rethand);
  if (rethand.isEmpty == false){
    return 4 + (float)rethand.cardsInHand[LAST_CARD_COMBO].value / 100;
  }else{
    rethand.updateHand(blankHand);
  } 
  OfAKind(3, hand, rethand);
  if (rethand.isEmpty == false){
    return 3 + (float)rethand.cardsInHand[FIRST_CARD].value / 100;
  }else{
    rethand.updateHand(blankHand);
  } 
  TwoPair(hand, rethand);
  if (rethand.isEmpty == false) {
    return 2 + (float)rethand.cardsInHand[rethand.cardsInHand.size() - 1].value / 100;
  } else{
    rethand.updateHand(blankHand);
  } 
  OfAKind(2, hand, rethand);
  if (rethand.isEmpty == false) {
    return 1 + (float)rethand.cardsInHand[0].value / 100;
  } else{
    rethand.updateHand(blankHand);
  } 
  return (float) hand.cardsInHand[hand.cardsInHand.size() - 1].value / 100;
  }
};