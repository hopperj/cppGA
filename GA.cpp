#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>
#include <vector>
#include <fstream>
#include <vector>
#include <algorithm>
#include "GA.h"

using namespace std;

GA::GA(){

  srand(time(NULL));

  population = vector<Player>(NUMOFPLAYERS);
  scores = vector< vector<double> >(NUMOFPLAYERS);
  GenPopulation();
}

int GA::indexOf( vector<double>& v, double element ) {
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

void GA::SortPopulation(){
  fitness = vector< double >(NUMOFPLAYERS, -99.0);
  sortedFitness = vector< double >(NUMOFPLAYERS, -99.0);
  newPopulation = vector< Player >(NUMOFPLAYERS);

  for( int p=0; p<NUMOFPLAYERS; p++){
    fitness[p] = population[p].Fitness();
    sortedFitness[p] = fitness[p];
  }

  sort( sortedFitness.begin(), sortedFitness.end() );

  for( int i=0; i<NUMOFPLAYERS; i++){
    newPopulation[i] = population[ indexOf(fitness, sortedFitness[i]) ];
  }

  reverse( newPopulation.begin(), newPopulation.end() );

  cout << 0 << " " << newPopulation[0].Fitness() << endl;
  //cout << NUMOFPLAYERS-1 << " " << newPopulation[NUMOFPLAYERS-1].Fitness() << endl;
  /*
  for( int i=0; i<1; i++){
    cout << i << " " << newPopulation[i].Fitness() << endl;
  }
  */
}

void GA::Breed(){
  Player newP;
  vector<Player> children = vector<Player>( NUMOFPLAYERS*killFraction );
  int i=0;
  perfectScore = false;

  if( newPopulation[0].Fitness() == 4.0 ){
    perfectScore = true;
  }

  while( i<NUMOFPLAYERS*( 1.0 - killFraction ) ){
    population[i] = newPopulation[i];
    population[i].ClearScore();
    i++;
  }
  cout << "Adding in randoms" << endl;
  while( i<NUMOFPLAYERS*( 1.0 - killFraction )+0.1*NUMOFPLAYERS){
    population[i] = Player();
    i++;
  }
  cout << "Doing breeding" << endl;
  while( i < NUMOFPLAYERS ){
    for( int j=0; j<=NUMOFPLAYERS*breedFraction; j++){
      newP = newPopulation[j];
      newP.brain.PertibateBrain();
      population[i] = newP;
      population[i].ClearScore();
      i++;
      if( i >= NUMOFPLAYERS ){
        break;
      }
    }
  }
}

void GA::GenPopulation(){
  cout << "\n\nGenerating " << NUMOFPLAYERS << " Players\n\n" << endl;
  for( int i=0; i<NUMOFPLAYERS; i++){
    population[i] = Player();
    population[i].wins = 0.0;
    population[i].ties = 0.0;
    population[i].losses = 0.0;
  }
}

void GA::RunSimulation(){
  Player allStar;
  opponent = vector< Player >(testingPool);

  for( int i=0; i<testingPool; i++){
    opponent[i] = Player();
  }


  for( int generation=0; generation<numOfGenerations; generation++){
    cout << "Generation: " << generation << endl;
    PlayTournament();
    SortPopulation();
    cout << "Making more randoms" << endl;
    for( int i=0; i<testingPool; i++){
      opponent[i] = Player();
    }

    Breed();

  }


  cout << "Going into the REAL tournament!!" << endl;





  for( int generation=0; generation<numOfGenerations; generation++){
    cout << "Generation: " << generation << endl;
    PlayTournament();
    SortPopulation();

    for( int i=0; i<testingPool; i++){
      opponent[i] = population[ (rand()/float(RAND_MAX))*(NUMOFPLAYERS-1) ];
    }

    if( generation<numOfGenerations-1 ){
      Breed();
    }

  }
  population[0].brain.save();

  allStar = population[0];
  GenPopulation();
  population[0] = allStar;
  PlayTournament();
  cout << "All star fitness: " << population[0].Fitness() << endl;

}

void GA::PlayTournament(){

  TTT game = TTT();

  for( int p1Num=0; p1Num<NUMOFPLAYERS-1; p1Num++) {
    for( int p2Num=0; p2Num<testingPool; p2Num++){
      //cout << p1Num << " vs " << p2Num << endl;
      PlayGame(&population[p1Num], &opponent[p2Num], &game);
      game.clearBoard();
      PlayGame(&opponent[p2Num], &population[p1Num], &game);
      game.clearBoard();
    }

  }

  return;


  for( int p1Num=0; p1Num<NUMOFPLAYERS-1; p1Num++) {
    for( int p2Num=p1Num+1; p2Num<NUMOFPLAYERS; p2Num++) {
      //cout << "Player " << p1Num << " vs " << p2Num << endl;
      //if( rand()/float(RAND_MAX) <= 0.5 ){
        //PlayGame( p1Num, p2Num, &game );
        game.clearBoard();
      //}
      //else {
        //PlayGame( p2Num, p1Num, &game );
        game.clearBoard();
      //}



    }
    /*
    if( ( int( (float(p1Num)/float(NUMOFPLAYERS) )*100 ) ) % 20 == 0 ){
      cout << "Progress: " << 100.0*float(p1Num)/float(NUMOFPLAYERS) << endl;
    }
    */
  }
  //cout << "\n\n" << endl;
}

void GA::PlayGame2(int p1Num, int p2Num, TTT *game){
  Player *p1;
  Player *p2;

  bool wasWinner;

  p1 = &population[p1Num];
  p2 = &population[p2Num];
  p1->SetMark('x');
  p2->SetMark('o');

  wasWinner = false;

  for( int turnNum=0; turnNum<9; turnNum++ ){
      if( turnNum % 2){
        if( p1->TakeTurn( game ) ){
          p1->wins += 1.0;
          p2->losses += 1.0;
          wasWinner = true;
          break;
        }
      } else {
        if( p2->TakeTurn( game ) ){
          p2->wins += 1.0;
          p2->losses += 1.0;
          wasWinner = true;
          break;
        }
      }
  }
  //game.clearBoard();
  if( !wasWinner ){
    p1->ties += 1.0;
    p2->ties += 1.0;
  }

}

void GA::PlayGame(Player *p1, Player *p2, TTT *game){

  bool wasWinner;

  p1->SetMark('x');
  p2->SetMark('o');

  wasWinner = false;
  for( int turnNum=0; turnNum<9; turnNum++ ){
      //cout << "turnNum: " << turnNum << " " << endl;
      if( turnNum % 2 == 0){
        //cout << "P1" << endl;
        if( p1->TakeTurn( game ) ){
          //cout << "p1 wins" << endl;
          p1->wins += 1.0;
          p2->losses += 1.0;
          wasWinner = true;
          break;
        }
      } else {
        //cout << "P2" << endl;
        if( p2->TakeTurn( game ) ){
          //cout << "p2 wins" << endl;
          p2->wins += 1.0;
          p2->losses += 1.0;
          wasWinner = true;
          break;
        }
      }
  }
  //game.clearBoard();
  if( !wasWinner ){
    p1->ties += 1.0;
    p2->ties += 1.0;
  }

}





int main(){

  GA ga = GA();

  ga.RunSimulation();

  return 1;
}
