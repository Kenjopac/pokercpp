#include <iostream>
#include <vector>
#include "poker.h"
using namespace std;

void Hand::updateData(std::vector<Card> CurrentHand){
  for (int i = 0; i < NUM_OF_VALUES;i++){
    Hand::countOfValues[i] = 0;
    if (i < 4){
    Hand::countOfSuits[i] = 0;
    }
  }
  
  for (Card card: CurrentHand){ 
    Hand::countOfValues[card.value]++;
    Hand::countOfSuits[card.suit]++;
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
    allCards.append(" , ");
    allCards.append(card.name);
  }
  return allCards;
};
void Hand::addCard(Card card){
  Hand::cardsInHand.push_back(card);
  updateData(cardsInHand);
};
void Hand::updateHand(std::vector<Card> CurrentHand){
  Hand::cardsInHand = sortCards(CurrentHand);
  updateData(cardsInHand);
};