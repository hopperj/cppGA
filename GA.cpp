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

  double results[2] = {0.0,0.0};

  TTT game = TTT();
  for( int p1Num=0; p1Num<numOfPlayers-1; p1Num++){
    for( int p2Num=p1Num+1; p2Num<numOfPlayers; p2Num++){
      p1 = population[p1Num];
      p2 = population[p2Num];
      //p1 = Player();
      //p2 = Player();

      p1.SetMark('x');
      p2.SetMark('o');




      for( int turnNum=0; turnNum<9; turnNum++ ){
          if( turnNum % 2){
            if( p1.TakeTurn( &game ) ){
              //cout << "Player 1 wins!" << endl;
              results[0] += 1.0;
              break;
            }

          } else {
            if( p2.TakeTurn( &game ) ){
              //cout << "Player 2 wins!" << endl;
              results[1] += 1.0;
              break;
            }
          }
          //cout << "Turn: " << turnNum << endl;
      }
      //game.printBoard();
      game.clearBoard();
    }
    if( p1Num%10==0){
      cout << float(p1Num)/float(numOfPlayers) << endl;
    }
  }


  cout <<"Player 1: " << results[0] << endl;
  cout << "Player 2: " << results[1] << endl;
  cout << "Ratio: " << (float)results[0]/(float)results[1] << endl;
}

void GA::PlayGame( Player *p1, Player *p2 ){
  /*
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
  */
}


int main(){

  GA ga = GA();

  ga.RunSimulation();

  return 1;
}
