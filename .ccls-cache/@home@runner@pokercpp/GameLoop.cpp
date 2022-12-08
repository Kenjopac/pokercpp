#include "poker.h"
#include <iostream>
#include <vector>
#include <iomanip>

int LENGTH_OF_LINE = 46;
void CenterMessage(string message, string fill){
  int choppedLines = LENGTH_OF_LINE - message.length();
  choppedLines /= 2;
  for (int counter = 0; counter < choppedLines; counter++){
    cout<<fill;
  }
  cout<<message;
  for (int counter = 0; counter< choppedLines;counter++){
    cout<<fill;
  }
  cout<<endl;
}
void LeftMessage(string message,string fill){
  cout<<message;
  for (int i = 0; i < LENGTH_OF_LINE - message.length();i++){
    cout<<fill;
  }
  cout<<endl;
}
void RightMessage(string message, string fill){
  
  for (int i = 0; i < LENGTH_OF_LINE - message.length();i++){
    cout<<fill;
  }
  cout<<message;
  cout<<endl;
}
void MenuLoop(){
        //15             16              15
  CenterMessage("Welcome to Poker","-");
  RightMessage("By Kenneth Wu", "-");
  bool Start = false;
  int StartCash  = 0;
  do {
    cout<<"How much money to start with: ";
    cin>>StartCash;
    if (cin.fail() || StartCash < 10){
      CenterMessage("Money must be an integer >= 10", "*");
    } else{
      LeftMessage("Press any key then enter to start", "-");
      string throwaway;
      cin>>throwaway;
      Start = true;
    }
    
  }while (Start == false);
  GameLoop(StartCash);
}
void GameLoop(int startCash){
  
  
}
void EndScreen(){
  
}