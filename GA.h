
#define NUMOFPLAYERS 1000
#define TESTINGPOOLSIZE 100
#define NUMOFGENERATIONS 150


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

  int numOfThreads = 2;


  GA();
  void PlayGame(Player *p1, Player *p2, TTT *game, int playerNum);
  void PlayHumanGame(Player *p1);
  void PlayTournament(int startNum, int endNum, vector< Player > opponent);

  void PlayHumanTournament(Player *allStar);

  void Resume();

  void RunSimulation();
  int indexOf( vector<float>& v, float element );
  void SortPopulation();
  void Breed();
  void GenPopulation();


  float breedFraction = 0.25;
  float killFraction = 0.25;
  bool perfectScore = false;



  int playerId;
  int oppId;
  //Player population[ NUMOFPLAYERS ];
  vector<Player> population;

  vector< vector<float> > scores;


  vector< float > fitness;
  vector< float > sortedFitness;
  vector< Player > newPopulation;
  //Player newPopulation[ NUMOFPLAYERS ];

};
