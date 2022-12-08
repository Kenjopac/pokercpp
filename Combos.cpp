#include <iostream>
#include <vector>
#include "poker.h"

Hand Straight(Hand hand){
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
          return Hand(straight);
        }
      }
  return Hand();
}; // returns highest value of straight,
Hand Flush(Hand hand){
  for (int suit = 0; suit < sizeof(hand.countOfSuits);suit++){
    if (hand.countOfSuits[suit] >=5){
      vector<Card> cardsOfSameSuit;
      for (int cardCounterReversed = hand.cardsInHand.size(); cardCounterReversed >= 0; cardCounterReversed--){
        if (hand.cardsInHand[cardCounterReversed].suit == suit){
          cardsOfSameSuit.push_back(hand.cardsInHand[cardCounterReversed]);
        }
        if (cardsOfSameSuit.size() == 5){
          return cardsOfSameSuit;
        }
      }
    }
  }
  return Hand();
};
Hand StraightFlush(Hand hand){ // add highest value...
  for (int suit = 0; suit <  sizeof(hand.countOfSuits); suit++){
    
    if (hand.countOfSuits[suit] >= 5){ // first test if there are enough of the suit, not enough cards for multiple straight flushes, in order is fine
      //then make new hand of only same suited cards
      vector<Card> cardsOfSameSuit;
      
      for (Card card: hand.cardsInHand){
        if(card.suit == suit){
          cardsOfSameSuit.push_back(card);
        }
      }
      return Straight(Hand(cardsOfSameSuit)); // assumes cards are sorted and all of same suit, if next card is one less, then add to straight counter until straight counter is nSpacesInBetweenStraightLong, start from back of sorted array to return largest straight. 
    }
  }
  return Hand();
}; //returns index of highest card if straight flush
Hand OfAKind(int getRepeats, Hand hand){ 
  vector<Card> sameValue;
  for (int valueCounterReversed = NUM_OF_VALUES;valueCounterReversed >= 0;valueCounterReversed --){
    if (hand.countOfValues[valueCounterReversed] == getRepeats){
      for (Card card: hand.cardsInHand){
        if (card.value == valueCounterReversed){
          sameValue.push_back(card);
        }
      }
      return Hand(sameValue);
    }
  }
  return Hand();
};//returns value of a repeated card 

Hand HighestCombo(Hand hand){
  vector <Card> NoCards;
  if (NoCards == StraightFlush(hand.cardsInHand).cardsInHand){
    
  }
    
};