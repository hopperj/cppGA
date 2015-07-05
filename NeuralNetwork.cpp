#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include <cstdlib>

#ifndef NEURALNETWORK_H
#include "NeuralNetwork.h"
#endif

using namespace std;



void NeuralNetwork::Init( int ins, int hidd, int nohl, int outs ){
  numOfInputs = ins+1;
  numOfHidden = hidd+1;
  numOfHiddenLayers = nohl;
  numOfOutputs = outs;

  energyThreshold = 0.9;
  useThreshold = 0;

  RandomIHW();
  RandomHHW();
  RandomHOW();
}

int NeuralNetwork::save() {
  ofstream fout("nn.dat");
  if( fout.is_open() ) {
    fout << numOfInputs << "\t" << numOfHidden << "\t" << numOfHiddenLayers << "\t" << numOfOutputs << "\n\n";

    for( int i=0; i<numOfInputs; i++) {
      for( int j=0; j<numOfHidden; j++) {
      	fout << ihw[i][j] << "\t";
      }
    }
    fout << "\n\n";

    for( int hl=0; hl<numOfHiddenLayers; hl++){
      for( int h1=0; h1<numOfHidden; h1++){
        for( int h2=0; h2<numOfHidden; h2++){
          fout << hhw[hl][h1][h2] << "\t";
        }
      }
    }
    fout << "\n\n";

    for( int i=0; i<numOfHidden; i++) {
      for( int j=0; j<numOfOutputs; j++){
      	fout << how[i][j] << "\t";
      }
    }
  }
  return 0;
}

int NeuralNetwork::load(){


  return 0;
}


void NeuralNetwork::RandomIHW(){
  ihw = Random2DList( numOfInputs, numOfHidden );
}

void NeuralNetwork::PertibateBrain(){

  for( int i=0; i<numOfInputs; i++ ){
    for( int h=0; h<numOfHidden; h++ ){
      ihw[i][h] += 0.1*(rand()/float(RAND_MAX) - 0.5);
    }
  }

  for( int hl=0; hl<numOfHiddenLayers; hl++){
    for( int h1=0; h1<numOfHidden; h1++){
      for( int h2=0; h2<numOfHidden; h2++){
        hhw[hl][h1][h2] += 0.1*(rand()/float(RAND_MAX) - 0.5);
      }
    }
  }

  for( int h=0; h<numOfHidden; h++ ){
    for( int o=0; o<numOfOutputs; o++ ){
      how[h][o] += 0.1*(rand()/float(RAND_MAX) - 0.5);
    }
  }

}


vector< vector<double> > NeuralNetwork::Random2DList( int n, int m){
  vector< vector<double> > tmp = vector< vector<double> >(n);
  //cout << "n: " << n << " m: " << m << endl;
  for( int i=0; i<n; i++){
    vector<double> v(m,0.0);
    for( int j=0; j<m; j++ ){
      // Generate number [-0.5, 0.5)
      v[j] = rand()/float(RAND_MAX) - 0.5;
    }
    tmp[i] = v;
  }
  return tmp;
}



void NeuralNetwork::RandomHHW(){
  hhw = vector< vector< vector<double> > >(numOfHiddenLayers);
  for( int i=0; i<numOfHiddenLayers; i++){
    hhw[i] = Random2DList( numOfHidden, numOfHidden );
  }
}

void NeuralNetwork::print2DVector(vector< vector<double> > a2d){
  for( int n=0; n<a2d.size(); n++){
    for( int m=0; m<a2d[n].size(); m++){
      cout << a2d[n][m] << " ";
    }
    cout << endl;
  }
}

void NeuralNetwork::PrintHHW(){
  for( int hl=0; hl<numOfHiddenLayers; hl++){
    print2DVector( hhw[hl] );
    cout << "\n\n";
  }
}


void NeuralNetwork::PrintIHW(){
  for( int i=0; i<numOfInputs; i++){
    for( int j=0; j<numOfHidden; j++){
      cout << ihw[i][j];
      if (j<numOfHidden-1){
	       cout << ", ";
      }
    }
    cout << endl;
  }
}

vector< vector<double> > NeuralNetwork::getIHW(){
  return ihw;
}

void NeuralNetwork::RandomHOW(){
  how = Random2DList(numOfHidden, numOfOutputs);
}

vector< vector<double> > NeuralNetwork::getHOW(){
  return how;
}

void NeuralNetwork::PrintHOW(){
  for( int i=0; i<numOfHidden; i++){
    for( int j=0; j<numOfOutputs; j++){
      cout << how[i][j];
      if (j<numOfOutputs-1){
	       cout << ", ";
      }
    }
    cout << endl;
  }
}

void NeuralNetwork::resetNodes(){
  inputs = vector<double>(numOfInputs);
  // Set the bias node
  inputs[numOfInputs-1] = 1.0;
  hidden = Random2DList( numOfHidden, numOfHidden);
  outputs = vector<double>(numOfOutputs);
}

double NeuralNetwork::sigmoid(double x){
  return 1.0/(1.0+exp(-1.0*x));
}

double NeuralNetwork::dsigmoid(double x){
  return x*( 1.0 - x );
}

vector< double > NeuralNetwork::run( vector< double > inpt){
  resetNodes();
  for( int i=0; i<inpt.size(); i++ ){
    inputs[i] = inpt[i];
  }

  vector< double > result = feedForward();
  if (useThreshold == 1){
    return result;
  } else {
    return outputs;
  }
}

vector<double> NeuralNetwork::feedForward(){
  for( int i=0; i<numOfInputs; i++){
    for( int h=0; h<numOfHidden; h++){
      hidden[0][h] += inputs[i]*ihw[i][h];
    }
  }
  // Sigmoid function all hidden nodes
  for( int h=0; h<numOfHidden; h++){
    hidden[0][h] = sigmoid( hidden[0][h] );
  }

  for( int hl=1; hl<numOfHiddenLayers; hl++){

    for( int h1=0; h1<numOfHidden; h1++){
      for( int h2=0; h2<numOfHidden; h2++){
        hidden[ hl ][h1] += hidden[hl-1][ h2 ]*hhw[hl][h1][h2];
      }
      hidden[ hl ][ h1 ] = sigmoid(hidden[hl][h1]);
    }
  }

  // Sum energies for output nodes
  for( int o=0; o<numOfOutputs; o++ ){
    for( int h=0; h<numOfHidden; h++){
      outputs[o] += hidden[numOfHiddenLayers-1][h]*how[h][o];
    }
    outputs[o] = sigmoid( outputs[o] );
  }

  vector<double> threshOuts(numOfOutputs, 0.0);

  for( int o=0; o<numOfOutputs; o++ ){
    // z = (x > y) ? z : y;
    threshOuts[o] = ( outputs[o] > energyThreshold ) ? 1.0 : 0.0;
  }

  return threshOuts;
}


void NeuralNetwork::customIHW(){

  for( int i=0; i<numOfInputs; i++ ){
    vector<double> v {0.0,1.0,2.0};
    ihw[i] = v;
  }

  ihw[0] = {-6.43950828, -5.68889739, -0.06042812,  1.31778221};
  ihw[1] = {-6.47674091, -5.65138717, -0.84061472,  1.36687703};
  ihw[2] = {2.37459487,  7.95179358, -5.413775,   -1.06961562};
}

void NeuralNetwork::customHOW(){

  for( int i=0; i<numOfHidden; i++ ){
    vector<double> v {0.0,1.0,2.0};
    how[i] = v;
  }

  how[0] = {-9.95436668};
  how[1] = {6.53150634};
  how[2] = {0.49557118};
  how[3] = {-3.97054856};

}

void print1DVector( vector<double> x){
  //cout << "vector size=" << x.size() << endl;
  for( int i=0; i<x.size(); i++){
    cout << x[i];
    if( i<x.size()-1 ){
      cout << ", ";
    }
  }
  cout << endl;
}

void print2DVector( vector< vector<double> > x){
  //cout << "printing 2D vector" << endl;
  for( int i=0; i<x.size(); i++){
    for( int j=0; j<x[i].size(); j++) {
      cout << x[i][j];
      if( j<x[i].size()-1 ){
	cout << ", ";
      }
    }
    cout << endl;
  }
}

/*
int main(){


  NeuralNetwork nn = NeuralNetwork(2,3,1);

  nn.useThreshold = 1.0;

  nn.customIHW();
  nn.customHOW();

  vector< vector<double>> xorstate;
  xorstate.push_back( {0,1} );
  xorstate.push_back ({1,1} );
  xorstate.push_back( {1,0} );
  xorstate.push_back( {0,0} );


  vector<double> expect {1,0,1,0};

  for( int i=0; i<xorstate.size(); i++){
    vector<double> tmp = nn.run( xorstate[i] );
    cout << "\nInput:" << endl;
    print1DVector(xorstate[i]);
    cout << "Result:";
    print1DVector(tmp);
    cout << "Expected:";
    cout << expect[i] << endl;
  }
  cout << "IHW" << endl;
  nn.printIHW();
  cout << "\n\nHOW\n" << endl;
  nn.printHOW();


  nn.save();


  return 0;
}
*/
