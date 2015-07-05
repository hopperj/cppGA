#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>
#include <vector>
#include <fstream>
#include <vector>

#ifndef GA_H
#define GA_H
#endif

#ifndef TTT_H
#include "TTT.h"
#endif

#ifndef NEURALNETWORK_H
#include "NeuralNetwork.h"
#endif

#ifndef PLAYER_H
#include "Player.h"
#endif

//#define NUMOFPLAYERS 100

using namespace std;


class GA
{

public:

  GA();
  void PlayGame(int p1Num, int p2Num, TTT *game);
  void PlayTournament();
  void RunSimulation();
  int indexOf( vector<double>& v, double element );
  void SortPopulation();
  void Breed();

  int NUMOFPLAYERS = 100;
  int numOfGenerations = 100;
  double breedFraction = 0.4;
  double killFraction = 0.6;

  //Player population[ NUMOFPLAYERS ];
  vector<Player> population;
  vector< vector<double> > scores;


  vector< double > fitness;
  vector< double > sortedFitness;
  vector< Player > newPopulation;
  //Player newPopulation[ NUMOFPLAYERS ];

};
