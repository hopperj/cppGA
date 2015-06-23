#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>
#include <vector>
#include <fstream>

#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H
#endif
using namespace std;

class NeuralNetwork
{
public:
  int numOfInputs, numOfHidden, numOfOutputs;
  vector<float> inputs;
  vector<float> hidden;
  vector<float> outputs;

  vector< vector<float> > ihw;
  vector< vector<float> > how;

  int useThreshold;
  float energyThreshold;

  void Init( int ins, int hidd, int outs );

  int setIHW( vector< vector<float> > nihw );
  int setHOW( vector< vector<float> > nhow );

  vector< vector<float> > getIHW();
  vector< vector<float> > getHOW();


  void customIHW();
  void customHOW();

  void printIHW();
  void printHOW();

  int save();
  int load();
  
  vector< float > run( vector< float> inpt );
  
private:
  float sigmoid(float x);
  float dsigmoid(float x);

  void randomIHW();
  void randomHOW();

  void resetNodes();

  vector< float > feedForward();
};
