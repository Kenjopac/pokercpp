#include <iostream>
#include <vector>
#include "poker.h"
using namespace std;
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
  for (int suit = 0; suit < sizeof(hand.countOfSuits); suit++){
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
Hand FullHouse(Hand hand){
  vector<Card> fullHouse;
  
  bool hastwo, hasthree;
  for (int i = NUM_OF_VALUES; i >= 0; i--){
    if (hand.countOfValues[i] == 3){
      hasthree = true;
    } else if (hand.countOfValues[i] == 2){
      hastwo = true;
    } 
  }
  if (hasthree && hastwo){
    Hand FullHouse = OfAKind(3, hand);
    Hand twoOfAKind = OfAKind(2, hand);
    for (Card card: twoOfAKind.cardsInHand){
      FullHouse.addCard(card);
    }
    return FullHouse;
  }else {
    return Hand();
  }
  
};
Hand TwoPair(Hand hand){
  int pairs = 0;
  for (int value: hand.countOfValues){
    if (value == 2){
      pairs++;
    }
  }
  if (pairs >= 2){
    Hand twopairHand = OfAKind(2, hand);
    for (Card card: twopairHand.cardsInHand){
      hand.removeCard(card);
    }
    for (Card card: OfAKind(2, hand).cardsInHand){
      
      twopairHand.addCard(card);
    }
    return twopairHand;
  } else{
    return Hand();
  }
};

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

float HighestComboValue(Hand hand){
  if (StraightFlush(hand).isEmpty == false ){
    return 9 + StraightFlush(hand).cardsInHand[4].value / 100;
  } else if (OfAKind(4,hand).isEmpty == false ){
    return 8 + OfAKind(4,hand).cardsInHand[2].value/100;
  } else if (FullHouse(hand).isEmpty == false){
    return 7 + FullHouse(hand).cardsInHand[2].value/100;
  } else if (Flush(hand).isEmpty == false){
    return 6 + Flush(hand).cardsInHand[4].value/ 100;
  } else if (Straight(hand).isEmpty == false){
    return 5 + Straight(hand).cardsInHand[4].value/100;
  } else if (OfAKind(3,hand).isEmpty == false){
    return 4 + OfAKind(3,hand).cardsInHand[0].value/100;
  } else if (TwoPair(hand).isEmpty == false){
    return 3 + TwoPair(hand).cardsInHand[0].value/100;
  } else if (OfAKind(2,hand).isEmpty == false){
    return 2 + OfAKind(2,hand).cardsInHand[0].value/100;
  } else {
    return hand.cardsInHand[0].value/10;
  }
};