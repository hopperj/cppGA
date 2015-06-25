#include "Player.h"
#include <algorithm>

#ifndef TTT_H
#include "TTT.h"
#endif


Player::Player( char _mark ){
  brain.Init(18,36,9);
  mark = _mark;
}

void Player::TakeTurn( TTT game ){
  moves = brain.run( game.getBoardLinear() );
  vector<double> sorted = moves;

  sort( sorted.begin(), sorted.end() );
  cout << "Max: " << *max_element( sorted.begin(), sorted.end() ) << endl;
  for( int i = 0; i<sorted.size(); i++ ){
    cout << sorted[i] << endl;
  }
}
