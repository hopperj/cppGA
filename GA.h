
#define NUMOFPLAYERS 1000
#define TESTINGPOOLSIZE 200
#define NUMOFGENERATIONS 100


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>

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

using namespace std;


class GA
{

public:

  GA();
  void PlayGame(Player *p1, Player *p2, TTT *game);
  void PlayHumanGame(Player *p1);
  void PlayTournament(int startNum, int endNum, vector< Player > opponent);

  void RunSimulation();
  int indexOf( vector<double>& v, double element );
  void SortPopulation();
  void Breed();
  void GenPopulation();


  double breedFraction = 0.25;
  double killFraction = 0.25;
  bool perfectScore = false;

  int numOfThreads = 1;


  int playerId;
  int oppId;
  //Player population[ NUMOFPLAYERS ];
  vector<Player> population;

  vector< vector<double> > scores;


  vector< double > fitness;
  vector< double > sortedFitness;
  vector< Player > newPopulation;
  //Player newPopulation[ NUMOFPLAYERS ];

};
