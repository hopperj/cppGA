#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>
#include <vector>
#include <fstream>
#include <vector>
#include <algorithm>
#include <thread>
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
  opponent = vector< Player >(TESTINGPOOLSIZE);

  for( int i=0; i<TESTINGPOOLSIZE; i++){
    opponent[i] = Player();
  }

  vector< thread > th;
  int nr_threads = 4;

  vector< int > args;
  thread t;
  for( int generation=0; generation<NUMOFGENERATIONS; generation++){
    cout << "Generation: " << generation << endl;
    //th = vector< thread >(nr_threads);

    //args = {0,10,11,20};
    //std::thread tt(&PlayTournament, args);

    /*
    for (int i = 0; i < nr_threads; ++i) {
      args = {i*NUMOFPLAYERS/nr_threads,
        (i+1)*NUMOFPLAYERS/nr_threads,
        i*TESTINGPOOLSIZE/nr_threads,
        (i+1)*TESTINGPOOLSIZE/nr_threads};
      th.push_back(thread(PlayTournament,args));

    }
    */
    PlayTournament();
    SortPopulation();
    cout << "Making more randoms" << endl;
    for( int i=0; i<TESTINGPOOLSIZE; i++){
      opponent[i] = Player();
    }

    Breed();

  }

  return;

  cout << "\n\n*****Going into the REAL tournament!!*****\n\n";


  for( int generation=0; generation<NUMOFGENERATIONS; generation++){
    cout << "Generation: " << generation << endl;
    PlayTournament();
    SortPopulation();

    for( int i=0; i<TESTINGPOOLSIZE; i++){
      opponent[i] = population[ (rand()/float(RAND_MAX))*(NUMOFPLAYERS-1) ];
    }

    if( generation<NUMOFGENERATIONS-1 ){
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

void GA::PlayTournament( vector< int > args ) {

  int p1Start=args[0];
  int p1End=args[1];
  int poolStart=args[2];
  int poolEnd=args[3];

  TTT game = TTT();
  clock_t t0 = clock();
  for( int p1Num=p1Start; p1Num<p1End; p1Num++) {
    for( int p2Num=poolStart; p2Num<poolEnd; p2Num++){
      //cout << p1Num << " vs " << p2Num << endl;
      //t0 = clock();
      PlayGame(&population[p1Num], &opponent[p2Num], &game);
      //cout << "Time taken: " << float( clock () - t0 ) /  CLOCKS_PER_SEC << " ms" << endl;
      game.clearBoard();
      //PlayGame(&opponent[p2Num], &population[p1Num], &game);
      //game.clearBoard();
    }
  }
  cout << "Time taken: " << float( clock () - t0 ) /  CLOCKS_PER_SEC << " sec" << endl;


  return;
}

void GA::PlayTournament(){

  TTT game = TTT();
  clock_t t0 = clock();
  for( int p1Num=0; p1Num<NUMOFPLAYERS; p1Num++) {
    for( int p2Num=0; p2Num<TESTINGPOOLSIZE; p2Num++){
      //cout << p1Num << " vs " << p2Num << endl;
      //t0 = clock();
      PlayGame(&population[p1Num], &opponent[p2Num], &game);
      //cout << "Time taken: " << float( clock () - t0 ) /  CLOCKS_PER_SEC << " ms" << endl;
      game.clearBoard();
      //PlayGame(&opponent[p2Num], &population[p1Num], &game);
      //game.clearBoard();
    }
  }
  cout << "Time taken: " << float( clock () - t0 ) /  CLOCKS_PER_SEC << " sec" << endl;


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
  //clock_t t0 = clock();

  bool wasWinner;

  p1->SetMark('x');
  p2->SetMark('o');

  wasWinner = false;
  for( int turnNum=0; turnNum<9; turnNum++ ) {
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
  //cout << float( clock () - t0 ) /  CLOCKS_PER_SEC << endl;
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
