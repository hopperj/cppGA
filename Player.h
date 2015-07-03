#ifndef PLAYER_H
#define PLAYER_H
#endif

#ifndef NEURALNETWORK_H
#include "NeuralNetwork.h"
#endif

#ifndef TTT_H
#include "TTT.h"
#endif


class Player
{

public:

  char mark;
  vector<double> moves;

  NeuralNetwork brain;
  Player(char _mark);
  Player();

  int TakeTurn( TTT *game );
  int indexOf( vector<double>& v, double element );
  void SetMark( char _mark );
};
