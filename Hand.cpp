#include <iostream>
#include <vector>
#include "poker.h"
using namespace std;

void Hand::updateData(std::vector<Card> CurrentHand){
  for (int i = 0; i < NUM_OF_VALUES;i++){
    countOfValues[i] = 0;
    if (i < 4){
    countOfSuits[i] = 0;
    }
  }
  
  for (Card card: CurrentHand){ 
    countOfValues[card.value]++;
    countOfSuits[card.suit]++;
  }
  if (CurrentHand.size() == 0){
    isEmpty = true;
  } else {
    isEmpty = false;
  }
};
void Hand::removeCard(Card removeThisCard){
  std::vector<Card> newHand;
  for (Card card: cardsInHand){
    if (card.index != removeThisCard.index){
      newHand.push_back(card);
    }
  }
  Hand::updateHand(newHand);
};
std::string Hand::readHand(){
  std::string allCards;
  for (Card card: Hand::cardsInHand){
    allCards.append(" ");
    allCards.append(card.name);
    allCards.append(" ");
  }
  return allCards;
};
void Hand::addCard(Card card){
  Hand::cardsInHand.push_back(card);
  Hand::cardsInHand = sortCards(cardsInHand);
  updateData(cardsInHand);
  isEmpty = false;
};
void Hand::updateHand(std::vector<Card> CurrentHand){
  cardsInHand = sortCards(CurrentHand);
  updateData(cardsInHand);
  
};