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
  vector<double> inputs;
  vector<double> hidden;
  vector<double> outputs;

  vector< vector<double> > ihw;
  vector< vector<double> > how;

  int useThreshold;
  double energyThreshold;

  void Init( int ins, int hidd, int outs );

  int setIHW( vector< vector<double> > nihw );
  int setHOW( vector< vector<double> > nhow );

  vector< vector<double> > getIHW();
  vector< vector<double> > getHOW();


  void customIHW();
  void customHOW();

  void printIHW();
  void printHOW();

  int save();
  int load();
  
  vector< double > run( vector< double> inpt );
  
private:
  double sigmoid(double x);
  double dsigmoid(double x);

  void randomIHW();
  void randomHOW();

  void resetNodes();

  vector< double > feedForward();
};
