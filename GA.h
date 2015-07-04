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


using namespace std;


class GA
{

public:

  GA();
  void PlayGame( Player *p1, Player *p2);
  void RunSimulation();

  int numOfPlayers = 1000;
  vector<Player> population;
  vector< vector<double> > scores;
};
