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


  int NUMOFINPUTS = 10;
  int NUMOFHIDDEN = 19;
  int NUMOFHIDDENLAYERS = 19;
  int NUMOFOUTPUTS = 9;


  //int numOfInputs, numOfHidden, numOfOutputs, numOfHiddenLayers;
  vector<double> inputs;
  vector< vector<double> > hidden;
  vector<double> outputs;

  vector< vector<double> > ihw;
  vector< vector< vector<double> > > hhw;
  vector< vector<double> > how;

  int useThreshold;
  double energyThreshold;
  double mutationChance = 0.05;
  double mutationStrength = 0.05;

  void Init( int ins, int hidd, int nohl, int outs );

  int setIHW( vector< vector<double> > nihw );
  int setHOW( vector< vector<double> > nhow );

  vector< vector<double> > getIHW();
  vector< vector<double> > getHOW();


  void customIHW();
  void customHOW();

  void PrintIHW();
  void PrintHOW();
  void PrintHHW();

  void PertibateBrain();

  int save();
  int load();

  vector< double > run( vector< double> inpt );
  vector< double > run( double *inpt);

private:
  double sigmoid(double x);
  double dsigmoid(double x);

  vector< vector<double> > Random2DList( int n, int m);

  void RandomIHW();
  void RandomHOW();
  void RandomHHW();

  void resetNodes();

  void print2DVector( vector< vector<double> > a2d);

  void feedForward();
};
