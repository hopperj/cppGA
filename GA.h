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
  void PlayGame2(int p1Num, int p2Num, TTT *game);
  void PlayGame(Player *p1, Player *p2, TTT *game);
  void PlayTournament();
  void RunSimulation();
  int indexOf( vector<double>& v, double element );
  void SortPopulation();
  void Breed();
  void GenPopulation();

  int NUMOFPLAYERS = 1000;
  int numOfGenerations = 500;
  int testingPool = 200;

  double breedFraction = 0.5;
  double killFraction = 0.5;
  bool perfectScore = false;
  //Player population[ NUMOFPLAYERS ];
  vector<Player> population;

  vector<Player> opponent;
  vector< vector<double> > scores;


  vector< double > fitness;
  vector< double > sortedFitness;
  vector< Player > newPopulation;
  //Player newPopulation[ NUMOFPLAYERS ];

};
