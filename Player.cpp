#include "Player.h"

#ifndef TTT_H
#include "TTT.h"
#endif


Player::Player( char _mark ){
  brain.Init(18,36,9);
  mark = _mark;
}

void Player::TakeTurn( TTT game ){
  moves = brain.run( game.getBoardLinear() );
  for( int i = 0; i<moves.size(); i++ ){
    cout << moves[i] << endl;
  }
}
