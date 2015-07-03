#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>
#include <vector>
#include <fstream>
#include <vector>

#include "GA.h"

GA::GA(){

  srand(time(NULL));

  population = vector<Player>(numOfPlayers);
  scores = vector< vector<double> >(numOfPlayers);

  for( int i=0; i<numOfPlayers; i++){
    population[i] = Player();
  }

}

void GA::RunSimulation(){
  Player p1;
  Player p2;




  p1 = population[0];
  p2 = population[1];
  cout << "Beginning game" << endl;
  //PlayGame( &p1, &p2);

  p1.SetMark('x');
  p2.SetMark('o');

  TTT game = TTT();
  for( int i=0; i<9; i++ ){
      if( turnNum % 2){
        if( p1.TakeTurn( &game ) ){
          cout << "Player 1 wins!" << endl;
          break;
        }

      } else {
        if( p2.TakeTurn( &game ) ){
          cout << "Player 2 wins!" << endl;
          break;
        }
      }
      //cout << "Turn: " << turnNum << endl;
      turnNum++;
  }
  game.printBoard();



}

void GA::PlayGame( Player *p1, Player *p2 ){
  TTT game = TTT();
  for( int i=0; i<9; i++ ){
      if( turnNum % 2){
        if( p1->TakeTurn( &game ) ){
          cout << "Player 1 wins!" << endl;
          break;
        }

      } else {
        if( p2->TakeTurn( &game ) ){
          cout << "Player 2 wins!" << endl;
          break;
        }
      }
      cout << "Turn: " << turnNum << endl;
      turnNum++;
  }
  game.printBoard();

}


int main(){

  GA ga = GA();

  ga.RunSimulation();

  return 1;
}
