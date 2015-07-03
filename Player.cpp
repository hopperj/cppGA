#include "Player.h"
#include <algorithm>
#include <iostream>

#ifndef TTT_H
#include "TTT.h"
#endif


Player::Player( char _mark ){
  brain.Init(18,36,9);
  mark = _mark;
}

Player::Player(){
  brain.Init(18,36,9);
}

void Player::SetMark( char _mark ){
  mark = _mark;
}

int Player::TakeTurn( TTT *game ){
  moves = brain.run( game->getBoardLinear() );

  vector<double> sorted = moves;
  int potentialMove;

  sort( sorted.begin(), sorted.end() );
  reverse( sorted.begin(), sorted.end() );

  for( int i=0; i<sorted.size(); i++ ){

    potentialMove = indexOf( moves, sorted[i] );
    if(!game->move( potentialMove/3, potentialMove%3, mark )){
      //cout << "Checking winner for player " << mark << endl;
      return game->checkWinner();
    }
  }

  return 0;

}

int Player::indexOf( vector<double>& v, double element ) {
  for( int i=0; i<v.size(); i++){
    if( v[i]==element ){
      return i;
    }
  }
  cout << "\n\nCouldn't find: "<<element<<endl;
  for( int i=0; i<v.size(); i++){
    cout << v[i] << " " << element << endl;
  }
  cout << "\n\n";
  return -1;
}
