#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include "poker.h"
using namespace std;
vector<vector<float>> weightsLayerOne;
int biasLayerOne;
vector<vector<float>> weightsLayerTwo;
int biasLayerTwo;

float sigmoid(float x){
  return (1 / ( 1 + exp(-x)));
}
vector<float> softmax(vector<float> unactivatedLayer){
  vector<float> activatedOutputs;
  float denominator;
  for (float output: unactivatedLayer){
    denominator += exp(output);
  }
  for (float output: unactivatedLayer){
    activatedOutputs.push_back(exp(output)/ denominator); 
  }
  return activatedOutputs;
}

void initWeights(int cards){
  
}

vector<float> ForwardPropogation(int roundnum, int turnnum, int balance, Hand hand, Hand HighestHand, int potvalue){
  
}