#include "Player.h"
#include <algorithm>
#include <iostream>
#include <mutex>


using namespace std;

Player::Player(){
}
Player::Player(int id){
  brain.Init(18,18,18,1);

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

float Player::Fitness(){
  if(wins+ties+losses == 0 ){
    return 0.0;
  }
  return wins;
  return 1.0 - (float)losses/(float)(wins+ties+losses);
  return (5.0*wins + 4.0*ties - 10.0*losses)/(float)(wins+ties+losses);
}

float Player::MaxFitness(){
  return 1.0;
  return 5.0;
}

int Player::TakeTurnRanking( TTT *game ){

  vector< int > moves = game->getEmptySpaces();

  int bestMove=-1;
  float bestRank = -9999.9;
  float currentRank;
  float board[18];
  //cout << "taking turn" << endl;
  for( unsigned int i=0; i<moves.size(); i++ ){
    //cout << "i: " << i << endl;
    game->getBoardLinearLong( &board[0] );
    //cout << "got board" << endl;
    if( mark=='x'){
      board[ 2*moves[i] ] = game->getMarkValue(mark);
    } else {
      board[ 2*moves[i]+1 ] = game->getMarkValue(mark);
    }
    /*
    for( int i=0; i<18; i++ ){
      cout << board[i] << " ";
    }
    cout << endl;
    */
    //cout << "moves: " << moves[i] << endl;
    currentRank = brain.run( &board[0] )[0];
    //board[ moves[i] ] = 0;
    //cout << "currentRank: " << currentRank << endl;
    //cout << "rank: " << currentRank << " move: " << moves[i] << endl;
    if( currentRank > bestRank ){
      bestRank = currentRank;
      bestMove = moves[i];
    }
  }

  game->move( bestMove/3, bestMove%3, mark );
  //cout << "move complete. moved to the " << bestMove << "th place" << endl;
  //cout << "\n\n";
  return game->checkWinner();

}

/*
int Player::TakeTurn( TTT *game ){
  const int numOfInputs = 9;

  //cout << "doing stuff" << endl;
  float tmp[numOfInputs] = {0.0};
  game->getBoardLinear( tmp );

  moves = brain.run( &tmp[0] );

  sorted = moves;

  sort( sorted.begin(), sorted.end(), greater<float>() );
  if( sorted[0] < sorted[moves.size()-1]){
    cout << "WHAT THE FUCK" << endl;
  }

  for( unsigned int i=0; i<sorted.size(); i++ ){
    potentialMove = indexOf( moves, sorted[i] );
    //cout << "sorted: " << i << " " << potentialMove << " " << sorted[i] << endl;
    if(!game->move( potentialMove/3, potentialMove%3, mark )){
      //cout << "--moved to: " << potentialMove << endl;
      return game->checkWinner();
    }
  }

  return 0;

}
*/


inline int Player::indexOf( vector<float>& v, float element ) {
  for( unsigned int i=0; i<v.size(); i++){
    if( v[i]==element ){
      return i;
    }
  }
  cout << "\n\nCouldn't find: "<<element<<endl;
  for( unsigned int i=0; i<v.size(); i++){
    cout << v[i] << " " << element << endl;
  }
  cout << "\n\n";
  return -1;
}

int Player::SaveBrain(int gen, int id){
  return brain.save(gen, id);
}
int Player::LoadBrain(int gen, int id){
  return brain.load(gen, id);
}
