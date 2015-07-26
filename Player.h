#ifndef PLAYER_H
#define PLAYER_H
#endif

#ifndef NEURALNETWORK_H
#include "NeuralNetwork.h"
#endif

#ifndef TTT_H
#include "TTT.h"
#endif

#include <mutex>
//#include <boost/thread.hpp>
//#include <boost/thread/mutex.hpp>
using namespace std;
//using namespace boost;

class Player
{

public:

  int Id;
  char mark;
  float wins, ties, losses;
  vector<float> moves;
  vector<float> sorted;

  int potentialMove;

  NeuralNetwork brain;
  Player();
  Player(int id);

  int TakeTurn( TTT *game );
  int TakeTurnRanking( TTT *game );
  inline int indexOf( vector<float>& v, float element );
  void SetMark( char _mark );
  float Fitness();
  float MaxFitness();
  void ClearScore();
  int GetId();
  int LoadBrain(int gen, int id);
  int SaveBrain(int gen, int id);
};
