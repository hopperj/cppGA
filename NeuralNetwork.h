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
  vector<float> inputs;
  vector< vector<float> > hidden;
  vector<float> outputs;

  vector< vector<float> > ihw;
  vector< vector< vector<float> > > hhw;
  vector< vector<float> > how;

  int useThreshold;
  float energyThreshold;
  float mutationChance = 0.05;
  float mutationStrength = 0.05;

  void Init( int ins, int hidd, int nohl, int outs );

  int setIHW( vector< vector<float> > nihw );
  int setHOW( vector< vector<float> > nhow );

  vector< vector<float> > getIHW();
  vector< vector<float> > getHOW();


  void customIHW();
  void customHOW();

  void PrintIHW();
  void PrintHOW();
  void PrintHHW();

  void PertibateBrain();

  //int save();
  //int load();
  int save(int gen, int id);
  int load(int gen, int id);

  vector< float > run( vector< float> inpt );
  vector< float > run( float *inpt);

private:
  float sigmoid(float x);
  float dsigmoid(float x);

  vector< vector<float> > Random2DList( int n, int m);

  void RandomIHW();
  void RandomHOW();
  void RandomHHW();

  void resetNodes();

  void print2DVector( vector< vector<float> > a2d);

  void feedForward();
};
