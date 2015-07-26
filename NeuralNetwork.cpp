#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <fstream>
#include <cstdlib>

#ifndef NEURALNETWORK_H
#include "NeuralNetwork.h"
#endif

using namespace std;



void NeuralNetwork::Init( int ins, int hidd, int nohl, int outs ){

  NUMOFINPUTS = ins+1;
  NUMOFHIDDEN = hidd+1;
  NUMOFHIDDENLAYERS = nohl;
  NUMOFOUTPUTS = outs;

  energyThreshold = 0.9;
  useThreshold = 0;

  RandomIHW();
  RandomHHW();
  RandomHOW();
}

int NeuralNetwork::save(int gen, int id) {
  try{
    char filename[255];
    sprintf(filename, "brains/nn_%04d_%04d.dat",gen,id);
    ofstream fout(filename);
    if( fout.is_open() ) {
      fout << NUMOFINPUTS << "\t" << NUMOFHIDDEN << "\t" << NUMOFHIDDENLAYERS << "\t" << NUMOFOUTPUTS << "\n\n";

      for( int i=0; i<NUMOFINPUTS; i++) {
        for( int j=0; j<NUMOFHIDDEN; j++) {
          fout << ihw[i][j] << "\t";
        }
      }
      fout << "\n\n";

      for( int hl=0; hl<NUMOFHIDDENLAYERS; hl++){
        for( int h1=0; h1<NUMOFHIDDEN; h1++){
          for( int h2=0; h2<NUMOFHIDDEN; h2++){
            fout << hhw[hl][h1][h2] << "\t";
          }
        }
      }
      fout << "\n\n";

      for( int i=0; i<NUMOFHIDDEN; i++) {
        for( int j=0; j<NUMOFOUTPUTS; j++){
          fout << how[i][j] << "\t";
        }
      }
    }
  } catch( const std::exception& e ){
    cout << "Error id: " << id << endl;
    return 1;
  }
  return 0;
}

int NeuralNetwork::load(int gen, int id){
  try{
    char filename[255];
    sprintf(filename, "brains/nn_%04d_%04d.dat",gen,id);
    ifstream fin(filename);
    if( fin.is_open() ) {
      fin >> NUMOFINPUTS >> NUMOFHIDDEN >> NUMOFHIDDENLAYERS >> NUMOFOUTPUTS;
      RandomIHW();
      RandomHHW();
      RandomHOW();

      for( int i=0; i<NUMOFINPUTS; i++) {
        for( int j=0; j<NUMOFHIDDEN; j++) {
          fin >> ihw[i][j];
        }
      }



      for( int hl=0; hl<NUMOFHIDDENLAYERS; hl++){
        for( int h1=0; h1<NUMOFHIDDEN; h1++){
          for( int h2=0; h2<NUMOFHIDDEN; h2++){
            fin >> hhw[hl][h1][h2];
          }
        }
      }

      for( int i=0; i<NUMOFHIDDEN; i++) {
        for( int j=0; j<NUMOFOUTPUTS; j++){
          fin >> how[i][j];
        }
      }
    } else {
      //cout << "File did not exist for id: " << id << endl;
      return 1;
    }
    //cout << "Loaded brain: " << id << endl;
  } catch( const std::exception& e ){
    //cout << "ERROR id: " << id << endl;
    return 1;
  }
  return 0;
}


void NeuralNetwork::RandomIHW(){
  ihw = Random2DList( NUMOFINPUTS, NUMOFHIDDEN );
}

void NeuralNetwork::PertibateBrain(){

  for( int i=0; i<NUMOFINPUTS; i++ ){
    for( int h=0; h<NUMOFHIDDEN; h++ ){
      if( rand()/float(RAND_MAX) >= mutationChance ){
        ihw[i][h] += mutationStrength*(rand()/float(RAND_MAX) - 0.5);
      }
      else{
        ihw[i][h] = rand()/float(RAND_MAX) - 0.5;
      }

    }
  }
  //cout << "did IHW" << endl;

  for( int hl=0; hl<NUMOFHIDDENLAYERS; hl++){
    for( int h1=0; h1<NUMOFHIDDEN; h1++){
      //cout << " **" << hl << " " << h1 << " " << hhw[hl][h1][0] << endl;
      for( int h2=0; h2<NUMOFHIDDEN; h2++){
        if( rand()/float(RAND_MAX) >= mutationChance ){
          hhw[hl][h1][h2] += mutationStrength*(rand()/float(RAND_MAX) - 0.5);
        }
        else {
          hhw[hl][h1][h2] = rand()/float(RAND_MAX);
        }
      }
    }
  }

  //cout << "did HHW" << endl;
  for( int h=0; h<NUMOFHIDDEN; h++ ){
    for( int o=0; o<NUMOFOUTPUTS; o++ ){
      if( rand()/float(RAND_MAX) >= mutationChance ){
        how[h][o] += mutationStrength*(rand()/float(RAND_MAX) - 0.5);
      }
      else {
        how[h][o] = rand()/float(RAND_MAX);
      }
    }
  }
  //cout << "did HOW" << endl;
}


vector< vector<float> > NeuralNetwork::Random2DList( int n, int m){
  vector< vector<float> > tmp = vector< vector<float> >(n);
  //cout << "n: " << n << " m: " << m << endl;
  for( int i=0; i<n; i++){
    vector<float> v(m,0.0);
    for( int j=0; j<m; j++ ){
      // Generate number [-0.5, 0.5)
      v[j] = rand()/float(RAND_MAX) - 0.5;
    }
    tmp[i] = v;
  }
  return tmp;
}



void NeuralNetwork::RandomHHW(){
  hhw = vector< vector< vector<float> > >(NUMOFHIDDENLAYERS);
  for( int i=0; i<NUMOFHIDDENLAYERS; i++){
    hhw[i] = Random2DList( NUMOFHIDDEN, NUMOFHIDDEN );
  }
}

void NeuralNetwork::print2DVector(vector< vector<float> > a2d){
  //cout << a2d.size() << endl;
  for( unsigned int n=0; n<a2d.size(); n++){
    //cout << "row: " << n << endl;
    for( unsigned int m=0; m<a2d[n].size(); m++){
      //cout << a2d[n][m] << " ";
    }
    //cout << endl;
  }
}

void NeuralNetwork::PrintHHW(){
  for( int hl=0; hl<NUMOFHIDDENLAYERS; hl++){
    //cout << "HL: " << hl << endl;
    print2DVector( hhw[hl] );
    //cout << "\n\n";
  }
}


void NeuralNetwork::PrintIHW(){
  for( int i=0; i<NUMOFINPUTS; i++){
    for( int j=0; j<NUMOFHIDDEN; j++){
      cout << ihw[i][j];
      if (j<NUMOFHIDDEN-1){
	       cout << ", ";
      }
    }
    cout << endl;
  }
}

vector< vector<float> > NeuralNetwork::getIHW(){
  return ihw;
}

void NeuralNetwork::RandomHOW(){
  how = Random2DList(NUMOFHIDDEN, NUMOFOUTPUTS);
}

vector< vector<float> > NeuralNetwork::getHOW(){
  return how;
}

void NeuralNetwork::PrintHOW(){
  for( int i=0; i<NUMOFHIDDEN; i++){
    for( int j=0; j<NUMOFOUTPUTS; j++){
      cout << how[i][j];
      if (j<NUMOFOUTPUTS-1){
	       cout << ", ";
      }
    }
    cout << endl;
  }
}

void NeuralNetwork::resetNodes(){
  inputs = vector<float>(NUMOFINPUTS);
  // Set the bias node
  inputs[NUMOFINPUTS-1] = 1.0;
  hidden = Random2DList( NUMOFHIDDEN, NUMOFHIDDEN);
  for( int i=0; i<NUMOFHIDDEN; i++){
    hidden[i][ NUMOFHIDDEN-1 ] = 1.0;
  }
  outputs = vector<float>(NUMOFOUTPUTS);
}

float NeuralNetwork::sigmoid(float x){
  return 1.0/(1.0+exp(-1.0*x));
}

float NeuralNetwork::dsigmoid(float x){
  return x*( 1.0 - x );
}

vector< float > NeuralNetwork::run( float *inpt){
  resetNodes();
  for( int i=0; i<NUMOFINPUTS-1; i++ ){
    inputs[i] = inpt[i];
    //cout << inpt[i] << "\t";
  }
  //cout << " run\n";

  feedForward();
  if (useThreshold == 1){
    vector< float > result;
    for( int o=0; o<NUMOFOUTPUTS; o++ ){
      // z = (x > y) ? z : y;
      result[o] = ( outputs[o] > energyThreshold ) ? 1.0 : 0.0;
    }
    return result;
  } else {
    return outputs;
  }
}

void NeuralNetwork::feedForward(){
  for( int i=0; i<NUMOFINPUTS; i++){
    for( register int h=0; h<NUMOFHIDDEN; h++){
      hidden[0][h] += inputs[i]*ihw[i][h];
    }
  }
  // Sigmoid function all hidden nodes
  for( int h=0; h<NUMOFHIDDEN; h++){
    hidden[0][h] = sigmoid( hidden[0][h] );
  }

  for( int hl=1; hl<NUMOFHIDDENLAYERS; hl++){

    for( int h1=0; h1<NUMOFHIDDEN; h1++){
      for( int register h2=0; h2<NUMOFHIDDEN; h2++){
        hidden[ hl ][h1] += hidden[hl-1][ h2 ]*hhw[hl][h1][h2];
      }
      hidden[ hl ][ h1 ] = sigmoid(hidden[hl][h1]);
    }
  }

  // Sum energies for output nodes
  for( int o=0; o<NUMOFOUTPUTS; o++ ){
    for( int register h=0; h<NUMOFHIDDEN; h++){
      outputs[o] += hidden[NUMOFHIDDENLAYERS-1][h]*how[h][o];
    }
    outputs[o] = sigmoid( outputs[o] );
  }

  //vector<float> threshOuts(NUMOFOUTPUTS, 0.0);



  //return threshOuts;
}


void NeuralNetwork::customIHW(){

  for( int i=0; i<NUMOFINPUTS; i++ ){
    vector<float> v {0.0,1.0,2.0};
    ihw[i] = v;
  }

  ihw[0] = {-6.43950828, -5.68889739, -0.06042812,  1.31778221};
  ihw[1] = {-6.47674091, -5.65138717, -0.84061472,  1.36687703};
  ihw[2] = {2.37459487,  7.95179358, -5.413775,   -1.06961562};
}

void NeuralNetwork::customHOW(){

  for( int i=0; i<NUMOFHIDDEN; i++ ){
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
  for( unsigned int i=0; i<x.size(); i++){
    cout << x[i];
    if( i<x.size()-1 ){
      cout << ", ";
    }
  }
  cout << endl;
}

void print2DVector( vector< vector<float> > x){
  //cout << "printing 2D vector" << endl;
  for( unsigned int i=0; i<x.size(); i++){
    for( unsigned int j=0; j<x[i].size(); j++) {
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
