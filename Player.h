#ifndef PLAYER_H
#define PLAYER_H
#endif

#ifndef NEURALNETWORK_H
#include "NeuralNetwork.h"
#endif

#ifndef TTT_H
#include "TTT.h"
#endif

//#include <mutex>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
using namespace std;
using namespace boost;

class Player
{

public:

  int Id;
  char mark;
  double wins, ties, losses;
  vector<double> moves;
  vector<double> sorted;

  int potentialMove;

  NeuralNetwork brain;
  Player();
  Player(int id);

  int TakeTurn( TTT *game );
  int TakeTurn( TTT *game, boost::mutex *m );
  inline int indexOf( vector<double>& v, double element );
  void SetMark( char _mark );
  double Fitness();
  double MaxFitness();
  void ClearScore();
  int GetId();
};
