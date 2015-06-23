#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>

#ifndef NEURALNETWORK_H
#include "NeuralNetwork.h"
#endif

using namespace std;



void NeuralNetwork::Init( int ins, int hidd, int outs ){
  numOfInputs = ins+1;
  numOfHidden = hidd+1;
  numOfOutputs = outs;

  energyThreshold = 0.9;

  randomIHW();
  randomHOW();
}

int NeuralNetwork::save() {
  ofstream fout("nn.dat");
  if( fout.is_open() ) {
    fout << numOfInputs << "\t" << numOfHidden << "\t" << numOfOutputs << endl;
    for( int i=0; i<numOfInputs; i++) {
      for( int j=0; j<numOfHidden; j++) {
	fout << ihw[i][j];
	if (j<numOfHidden-1) {
       
	  fout << "\t";
	}
      }
      fout << endl;
    }

    fout << "\n\n";
    for( int i=0; i<numOfHidden; i++) {
      for( int j=0; j<numOfOutputs; j++){
	fout << how[i][j];
	if (j<numOfOutputs-1){
	  fout << "\t";
	}
      }
      fout << endl;
    }    


    
  }

  return 0;
}

int NeuralNetwork::load(){


  return 0;
}


void NeuralNetwork::randomIHW(){
  
  ihw = vector< vector<float> >(numOfInputs);
  for( int i=0; i<numOfInputs; i++){
    vector<float> v(numOfHidden,1.5);
    ihw[i] = v;
  }

}

void NeuralNetwork::printIHW(){

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

vector< vector<float> > NeuralNetwork::getIHW(){
  return ihw;
}

void NeuralNetwork::randomHOW(){
  how = vector< vector<float> >(numOfHidden);
  for( int i=0; i<numOfHidden; i++){
    vector<float> v(numOfOutputs,2.5);
    how[i] = v;
  }

}

vector< vector<float> > NeuralNetwork::getHOW(){
  return how;
}

void NeuralNetwork::printHOW(){

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
  
  inputs = vector<float>(numOfInputs);
  // Set the bias node
  inputs[numOfInputs-1] = 1.0;
  hidden = vector<float>(numOfHidden);
  outputs = vector<float>(numOfOutputs);

}

float NeuralNetwork::sigmoid(float x){
  return 1.0/(1.0+exp(-1.0*x));
}

float NeuralNetwork::dsigmoid(float x){
  return x*( 1.0 - x );
}

 
vector< float > NeuralNetwork::run( vector< float > inpt){
  resetNodes();
  for( int i=0; i<inpt.size(); i++ ){
    inputs[i] = inpt[i];
  }
  
  vector< float > result = feedForward();
  if (useThreshold == 1){
    return result;
  } else {
    return outputs;
  }
}

vector<float> NeuralNetwork::feedForward(){
  for( int i=0; i<numOfInputs; i++){
    for( int h=0; h<numOfHidden; h++){
      hidden[h] += inputs[i]*ihw[i][h];
    }
  }
  // Sigmoid function all hidden nodes
  for( int h=0; h<numOfHidden; h++){
    hidden[h] = sigmoid( hidden[h] );
  }

  // Sum energies for output nodes
  for( int o=0; o<numOfOutputs; o++ ){
    for( int h=0; h<numOfHidden; h++){
      outputs[o] += hidden[h]*how[h][o];
    }
  }
  
  vector<float> threshOuts(numOfOutputs, 0.0);
  
  for( int o=0; o<numOfOutputs; o++ ){
    outputs[o] = sigmoid( outputs[o] );
    // z = (x > y) ? z : y;
    threshOuts[o] = ( outputs[o] > energyThreshold ) ? 1.0 : 0.0;
  }
  
  return threshOuts;
}


void NeuralNetwork::customIHW(){

  for( int i=0; i<numOfInputs; i++ ){
    vector<float> v {0.0,1.0,2.0};
    ihw[i] = v;
  }
  
  ihw[0] = {-6.43950828, -5.68889739, -0.06042812,  1.31778221};
  ihw[1] = {-6.47674091, -5.65138717, -0.84061472,  1.36687703};
  ihw[2] = {2.37459487,  7.95179358, -5.413775,   -1.06961562};
}

void NeuralNetwork::customHOW(){

  for( int i=0; i<numOfHidden; i++ ){
    vector<float> v {0.0,1.0,2.0};
    how[i] = v;
  }

  how[0] = {-9.95436668};
  how[1] = {6.53150634};
  how[2] = {0.49557118};
  how[3] = {-3.97054856};

}

void print1DVector( vector<float> x){
  //cout << "vector size=" << x.size() << endl;
  for( int i=0; i<x.size(); i++){
    cout << x[i];
    if( i<x.size()-1 ){
      cout << ", ";
    }
  }
  cout << endl;
}

void print2DVector( vector< vector<float> > x){
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

  vector< vector<float>> xorstate;
  xorstate.push_back( {0,1} );
  xorstate.push_back ({1,1} );
  xorstate.push_back( {1,0} );
  xorstate.push_back( {0,0} );

  
  vector<float> expect {1,0,1,0};

  for( int i=0; i<xorstate.size(); i++){   
    vector<float> tmp = nn.run( xorstate[i] );
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
