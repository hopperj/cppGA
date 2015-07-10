#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include <vector>
#include <algorithm>
#include <thread>
#include "GA.h"
#include <mutex>

using namespace std;

mutex outputMutex;
GA::GA(){

  srand(time(NULL));

  population = vector<Player>(NUMOFPLAYERS);
  scores = vector< vector<double> >(NUMOFPLAYERS);
  playerId = 0;
  oppId = 0;
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

  cout << "Max Fitness: " << newPopulation[0].Fitness() << endl;
  //cout << newPopulation[0].wins << " " << newPopulation[0].ties << " " << newPopulation[0].losses << endl;
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
    population[i] = Player(playerId++);
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
    population[i] = Player(playerId++);
  }
}

void GA::RunSimulation(){
  Player allStar;

  vector<Player> opponent = vector< Player >(TESTINGPOOLSIZE);

  for( int i=0; i<TESTINGPOOLSIZE; i++){
    opponent[i] = Player(oppId);
    opponent[i].SetMark('o');
  }

  vector< thread > threads = vector< thread >(numOfThreads);
  int start,end;


  clock_t t0 = clock();
  for( int generation=0; generation<(int)(NUMOFGENERATIONS*0.25); generation++){
    cout << "Generation: " << generation << endl;


    t0 = clock();
    for( int i=0; i<numOfThreads; i++){
      start = i*(int)((float)NUMOFPLAYERS/(float)numOfThreads);
      end = start + (int)((float)NUMOFPLAYERS/(float)numOfThreads);
      if( end > NUMOFPLAYERS){
        end = NUMOFPLAYERS;
      }

      //outputMutex.lock();
      //cout << "-->start: " << start << "\tend:" << end << endl;
      //outputMutex.unlock();

      threads[i] = thread( &GA::PlayTournament, this, start, end, opponent );
    }

    // Wait for threads to finish
    for( int i=0; i<numOfThreads; i++){
        outputMutex.lock();
        cout << " waiting for thread: " << i << endl;
        outputMutex.unlock();
        threads[i].join();
    }

    cout << "Time taken: " << float( clock () - t0 ) /  CLOCKS_PER_SEC << " sec" << endl;
    //PlayTournament(0, NUMOFPLAYERS);
    SortPopulation();
    for( int i=0; i<TESTINGPOOLSIZE; i++){
      opponent[i] = Player(oppId);
      opponent[i].SetMark('o');
    }
    Breed();
  }

  //return;

  cout << "\n\n*****Going into the REAL tournament!!*****\n\n";


  for( int generation=0; generation<NUMOFGENERATIONS; generation++){
    cout << "Generation: " << generation << endl;
    t0 = clock();
    for( int i=0; i<numOfThreads; i++){
      start = i*(int)((float)NUMOFPLAYERS/(float)numOfThreads);
      end = start + (int)((float)NUMOFPLAYERS/(float)numOfThreads);
      if( end > NUMOFPLAYERS){
        end = NUMOFPLAYERS;
      }

      //outputMutex.lock();
      //cout << "-->start: " << start << "\tend:" << end << endl;
      //outputMutex.unlock();

      threads[i] = thread( &GA::PlayTournament, this, start, end, opponent );
    }

    // Wait for threads to finish
    for( int i=0; i<numOfThreads; i++){
        outputMutex.lock();
        cout << " waiting for thread: " << i << endl;
        outputMutex.unlock();
        threads[i].join();
    }

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
  PlayTournament(0, NUMOFPLAYERS, opponent);
  cout << "All star fitness: " << population[0].Fitness() << endl;

}


void GA::PlayTournament(int startNum, int endNum, vector< Player > opponent){
  outputMutex.lock();
  cout << "from: " << startNum << " to: " << endNum << endl;
  outputMutex.unlock();


  TTT game = TTT();
  clock_t t0;
  t0 = clock();
  for( int p1Num=startNum; p1Num<endNum; p1Num++) {
    for( int p2Num=0; p2Num<TESTINGPOOLSIZE; p2Num++){
      PlayGame(&population[p1Num], &opponent[p2Num], &game);
      game.clearBoard();
    }
  }
  outputMutex.lock();
  cout << "Time taken: " << float( clock () - t0 ) /  CLOCKS_PER_SEC << " sec" << endl;
  outputMutex.unlock();
  //cout << "Time taken: " << float( clock () - t0 ) /  CLOCKS_PER_SEC << " sec" << endl;
}

void GA::PlayGame(Player *p1, Player *p2, TTT *game){
  //clock_t t0 = clock();

  bool wasWinner;

  p1->SetMark('x');
  //p2->SetMark('o');

  wasWinner = false;
  //cout << "Player " << p1->Id << " vs " << p2->Id << endl;
  for( int turnNum=0; turnNum<9; turnNum++ ) {
      //cout << "turnNum: " << turnNum << " " << endl;
      if( turnNum % 2 == 0){
        //cout << "P1" << endl;
        if( p1->TakeTurn( game ) ){
          //cout << "-->p1 wins" << endl;
          p1->wins += 1.0;
          //p2->losses += 1.0;
          wasWinner = true;
          break;
        }
      } else {
        //cout << "P2" << endl;
        if( p2->TakeTurn( game ) ){
          //cout << "-->p2 wins" << endl;
          //p2->wins += 1.0;
          p1->losses += 1.0;
          wasWinner = true;
          break;
        }
      }
  }
  //cout << float( clock () - t0 ) /  CLOCKS_PER_SEC << endl;
  //game.clearBoard();
  if( !wasWinner ){
    p1->ties += 1.0;
    //p2->ties += 1.0;
    //cout << "tie!" << endl;
  }

  //cout << "current fitness: " << p2->Fitness() << endl;

}





int main(){

  GA ga = GA();

  ga.RunSimulation();

  return 1;
}
