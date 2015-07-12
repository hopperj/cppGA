#include "Player.h"
#include <algorithm>
#include <iostream>
#include <mutex>
/*
#ifndef TT
#include "TTT.h"
#endif
*/
/*
Player::Player( char _mark ){
  brain.Init(18,18,18,9);
  mark = _mark;

  wins = 0.0;
  ties = 0.0;
  losses = 0.0;
}
*/

//mutex m;

Player::Player(){
}
Player::Player(int id){
  brain.Init(9,9,9,9);

  wins = 0.0;
  ties = 0.0;
  losses = 0.0;

  Id = id;
}

int Player::GetId(){
  return Id;
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
  if(wins+ties+losses == 0 ){
    return 0.0;
  }
  return wins;
  return 1.0 - (float)losses/(float)(wins+ties+losses);
  return (5.0*wins + 4.0*ties - 10.0*losses)/(float)(wins+ties+losses);
}

double Player::MaxFitness(){
  return 1.0;
  return 5.0;
}
int Player::TakeTurn( TTT *game, mutex *m ){
  m->lock();
  int ret = TakeTurn( game );
  m->unlock();
  return ret;
}
int Player::TakeTurn( TTT *game ){
  const int numOfInputs = 9;

  //cout << "doing stuff" << endl;
  double tmp[numOfInputs] = {0.0};
  game->getBoardLinear( tmp );
  /*
  for( int i=0; i<numOfInputs; i++){
    cout << tmp[i] << "\t";
  }
  */
  //cout << " test\n";
  //cout << "running brain" << endl;
  moves = brain.run( tmp );

  sorted = moves;

  sort( sorted.begin(), sorted.end(), greater<double>() );
  if( sorted[0] < sorted[moves.size()-1]){
    cout << "WHAT THE FUCK" << endl;
  }
  //reverse( sorted.begin(), sorted.end() );

  for( int i=0; i<sorted.size(); i++ ){

    potentialMove = indexOf( moves, sorted[i] );
    if(!game->move( potentialMove/3, potentialMove%3, mark )){
      //cout << "Checking winner for player " << mark << endl;
      return game->checkWinner();
    }
  }

  return 0;

}

inline int Player::indexOf( vector<double>& v, double element ) {
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
