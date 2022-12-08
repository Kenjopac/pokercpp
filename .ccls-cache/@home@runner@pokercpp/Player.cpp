#include "poker.h"
#include <iostream>
#include <vector>

void Player::PayAmount(int MoneyOut){
  Player::Balance -= MoneyOut;
};

void Player::GainAmount(int MoneyIn){
  Player::Balance += MoneyIn;
}
int Player::MakeDecision(int amount){
  if (amount > 0 ){
    Player::PayAmount(amount);
    return amount;
  } else if (amount== 0){
    
  } else {
    return -1;
  }
} // assumes amount is above player balance,