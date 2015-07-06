#include "Player.h"
#include <algorithm>
#include <iostream>

#ifndef TTT_H
#include "TTT.h"
#endif


Player::Player( char _mark ){
  brain.Init(18,18,3,9);
  mark = _mark;

  wins = 0.0;
  ties = 0.0;
  losses = 0.0;
}

Player::Player(){
  /*
  brain.Init(2,3,2,1);
  cout << "IHW" << endl;
  brain.PrintIHW();
  cout << endl;
  cout << "HHW" << endl;
  brain.PrintHHW();
  cout << endl;
  cout << "HOW" << endl;
  brain.PrintHOW();
  */
  brain.Init(18,18,5,9);

  wins = 0.0;
  ties = 0.0;
  losses = 0.0;
}

void Player::SetMark( char _mark ){
  mark = _mark;
}

void Player::ClearScore(){
  wins = 0.0;
  ties = 0.0;
  losses = 0.0;
}

double Player::Fitness(){
  if(wins+ties+losses == 0.0 ){
    return 0.0;
  }
  return (5.0*wins + 4.0*ties - 10.0*losses)/(float)(wins+ties+losses);
}

double Player::MaxFitness(){
  return 5.0;
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
