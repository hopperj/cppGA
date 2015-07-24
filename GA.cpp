#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include <vector>
#include <algorithm>

#include <chrono>
#include <ctime>


#include <thread>
#include "GA.h"
#include <mutex>
using namespace std;


mutex outputMutex;
vector< mutex > m = vector< mutex >(NUMOFPLAYERS);
GA::GA(){

  srand(time(NULL));

  population = vector<Player>(NUMOFPLAYERS);
  scores = vector< vector<float> >(NUMOFPLAYERS);
  playerId = 0;
  oppId = 0;
}

vector<int> GA::indexOf( vector<float>& v, float element ) {
  vector<int> pos = vector<int>();
  //cout << "starting indexOf" << endl;
  for( unsigned int i=0; i<v.size(); i++){
    if( v[i]==element ){
      //cout << "-->adding: "<<i<<endl;
      pos.push_back(i);
    }
  }

  if( pos.size() < 1 ){
    cout << "didn't find anything!" << endl;
  }
  random_shuffle ( pos.begin(), pos.end() );
  return pos;

  cout << "\n\nCouldn't find: "<< element << endl;
  for( unsigned int i=0; i<v.size(); i++){
    cout << v[i] << " " << element << endl;
  }
  cout << "\n\n";
  return pos;
}

void GA::SortPopulation(){
  averageFitness = 0.0;
  fitness = vector< float >(NUMOFPLAYERS, -99.0);
  sortedFitness = vector< float >(NUMOFPLAYERS, -99.0);
  newPopulation = vector< Player >(NUMOFPLAYERS);

  for( int p=0; p<NUMOFPLAYERS; p++){
    fitness[p] = population[p].Fitness()/(float)TESTINGPOOLSIZE;
    sortedFitness[p] = fitness[p];
    averageFitness += fitness[p];
  }

  averageFitness /= (float)NUMOFPLAYERS;

  sort( sortedFitness.begin(), sortedFitness.end(), greater<double>() );

  vector< int > pos;
  cout << "Top player IDs:" << endl;
  for( int i=0; i<NUMOFPLAYERS; i++){
    pos = indexOf(fitness, sortedFitness[i]);
    //cout << pos.size() << endl;
    //newPopulation[i] = population[ pos[0] ];


    for( unsigned int j=0; j<pos.size(); j++ ){
      if( i >= NUMOFPLAYERS ) {
        //cout << "*************BREAKING*************" << endl;
        break;
      }
      newPopulation[i] = population[ pos[j] ];
      //cout << "inner loop: " << i << " " << pos[j] << endl;
      //cout << "id: " << population[ pos[j] ].Id << endl << endl;;
      i++;
      /*
      if( i < 10 ){
        cout << i << " " << pos[j] << endl;;
      }
      i++;*/
    }
    i--;
    //cout << "\n\n" << endl;

    //newPopulation[i] = population[ pos[0] ];

    /*
    for( unsigned int j=0; j<pos.size(); j++ ){
      cout << "pos[j]: " <<pos[j] << endl;
      newPopulation[i] = population[ pos[j] ];
      //cout << "i:" << i << "\tpos:" << pos[j] << "\tf:" << fitness[i] << "\tsf:" << sortedFitness[i] << "\tid:" << newPopulation[i].Id << endl;
      i++;
      if( i >= NUMOFPLAYERS ){
        break;
      }
    }
    */
  }
  //reverse( newPopulation.begin(), newPopulation.end() );

  cout << "Max Fitness: " << newPopulation[0].Id << " " <<newPopulation[0].Fitness()/(float)TESTINGPOOLSIZE << endl;
  cout << "Average Fitness: " << averageFitness << endl << endl;
  //cout << newPopulation[0].wins << " " << newPopulation[0].ties << " " << newPopulation[0].losses << endl;
  //cout << NUMOFPLAYERS-1 << " " << newPopulation[NUMOFPLAYERS-1].Fitness() << endl;

  for( int i=0; i<10; i++){
    cout << i << " " << newPopulation[i].Id << endl;
  }
  cout << "------------------------" << endl;





}

void GA::Breed(){

  Player newP;
  vector<Player> children = vector<Player>( NUMOFPLAYERS*killFraction );
  int i=0;
  perfectScore = false;

  if( newPopulation[0].Fitness() == 4.0 ){
    perfectScore = true;
  }

  //cout << "Adding breeders" << endl;
  while( i<NUMOFPLAYERS*( 1.0 - killFraction ) ){
    population[i] = newPopulation[i];
    population[i].ClearScore();
    i++;
  }
  //cout << "Adding in randoms" << endl;
  while( i<NUMOFPLAYERS*( 1.0 - killFraction )+0.05*NUMOFPLAYERS){
    population[i] = Player(playerId++);
    i++;
  }
  //population[0].LoadBrain();
  //cout << "Doing breeding" << endl;
  while( i < NUMOFPLAYERS ){
    for( int j=0; j<=NUMOFPLAYERS*breedFraction; j++){
      //cout << "-->" << i << " " << j << endl;
      newP = newPopulation[j];
      //cout << "changing ID " << playerId << endl;
      newP.brain = newPopulation[j].brain;
      //cout << "doing other brain" << endl;
      //newPopulation[j].brain.PertibateBrain();
      //cout << "done, doing new brain now" << endl;
      //cout << "hhw: " << newP.brain.hhw[0][0][8] << endl;
      //cout << "HHW: " << endl;
      newP.brain.PrintHHW();
      newP.brain.PertibateBrain();
      //cout << "punched brain" << endl;
      newP.Id = playerId++;
      //cout << "j: " << j << "\tid: " << newPopulation[j].Id << "\t" << newP.brain.ihw[0][0] << "\t" << newPopulation[j].brain.ihw[0][0] << endl;
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

  int lastGen = NUMOFGENERATIONS;
  while (population[0].LoadBrain(lastGen, 0) == 0){
    lastGen--;
  }
  cout << "Last generation was: " << lastGen << endl;
  for( int i=0; i<NUMOFPLAYERS; i++){
    if( population[i].LoadBrain(lastGen, i) == 1 ){
      //cout << "Error loading brain " << i << endl;
      break;
    }
  }
  population[0].brain.PrintIHW();
  cout << "---------------------------------------------------------" << endl;
  cout << "Done creating population" << endl;
}

void GA::RunSimulation(){
  GenPopulation();

  Player allStar;
  float threshold = 1.0;
  vector<Player> opponent = vector< Player >(TESTINGPOOLSIZE);
  cout << "Creating opponent pool" << endl;
  for( int i=0; i<TESTINGPOOLSIZE; i++){
    opponent[i] = Player(oppId++);
    opponent[i].SetMark('o');
  }
  cout << "Created opponents" << endl;
  // thread_ = thread( &clientTCP::run , this, f );
  vector< thread > threads = vector< thread >(numOfThreads);
  int start,end;

  chrono::time_point<chrono::system_clock> t0;
  chrono::duration<double> elapsed_seconds;
  cout << "Beginning simulation." << endl;
  for( int generation=0; generation<NUMOFGENERATIONS; generation++){

    cout << "Generation: " << generation << endl;
    t0 = chrono::system_clock::now();
    for( int i=0; i<numOfThreads; i++){
      start = i*(int)((float)NUMOFPLAYERS/(float)numOfThreads);
      end = start + (int)((float)NUMOFPLAYERS/(float)numOfThreads);
      if( end > NUMOFPLAYERS){
        end = NUMOFPLAYERS;
      }

      //outputMutex.lock();
      //cout << "-->start: " << start << "\tend:" << end << endl;
      //outputMutex.unlock();
      //threads[i] = thread( &GA::PlayTournament, this, start, end, opponent );
      threads[i] = thread( &GA::PlayTournament, this, start, end, opponent );
    }

    // Wait for threads to finish
    /*
    outputMutex.lock();
    cout << " waiting for threads: " << endl;
    outputMutex.unlock();
    */
    for( int i=0; i<numOfThreads; i++){
        threads[i].join();
    }

    //break;
    elapsed_seconds = chrono::system_clock::now() - t0;
    cout << "Time taken: " << elapsed_seconds.count() << " sec" << endl;
    //PlayTournament(0, NUMOFPLAYERS);
    SortPopulation();
    cout << "\n\n\nbreeding\n\n\n" << endl;
    Breed();

    if( averageFitness > threshold ){
      threshold += 0.1;
      cout << "Population average is high enough to move on." << endl;
      break;
    }
    if( averageFitness > threshold ){
      threshold += 0.1;
      cout << "Generating new opponents to be crushed!!" << endl;
      for( int i=0; i<TESTINGPOOLSIZE; i++){
        opponent[i] = Player(oppId++);
        opponent[i].SetMark('o');
      }
    }


  }

  //return;

  cout << "\n\n*****Going into the REAL tournament!!*****\n\n";
  threshold = 1.0;

  threshold = 1.0;
  for( int generation=0; generation<NUMOFGENERATIONS; generation++){
    cout << "Generation: " << generation << endl;

    if(generation>0 && generation%(1+(int)(NUMOFGENERATIONS*0.1))==0){
      cout << "Preserving the top minds of this generation" << endl;
      SortPopulation();
      for( int i=0; i<(int)(NUMOFPLAYERS*breedFraction); i++ ){
        newPopulation[i].SaveBrain(generation,i);
      }
    }

    t0 = chrono::system_clock::now();
    for( int i=0; i<numOfThreads; i++){
      start = i*(int)((float)NUMOFPLAYERS/(float)numOfThreads);
      end = start + (int)((float)NUMOFPLAYERS/(float)numOfThreads);
      if( end > NUMOFPLAYERS){
        end = NUMOFPLAYERS;
      }

      //outputMutex.lock();
      //cout << "-->start: " << start << "\tend:" << end << endl;
      //outputMutex.unlock();
      //threads[i] = thread( &GA::PlayTournament, this, start, end, opponent );


      threads[i] = thread( &GA::PlayTournament, this, start, end, opponent );
    }

    // Wait for threads to finish
    for( int i=0; i<numOfThreads; i++){
      /*
      outputMutex.lock();
      cout << " waiting for thread: " << i << endl;
      outputMutex.unlock();
      */
      threads[i].join();
    }

    SortPopulation();

    if( generation<NUMOFGENERATIONS-1 ){
      Breed();
    }
    if( averageFitness > threshold ) {
      threshold += 0.1;
      cout << "Opponents are too easy .... getting new ones!" << endl;

      for( int i=0; i<(int)(TESTINGPOOLSIZE*0.25); i++){
	opponent[i] = Player(oppId++);
	opponent[i].SetMark('o');
      }
      for( int i=(int)(TESTINGPOOLSIZE*0.75); i<TESTINGPOOLSIZE; i++){
	opponent[i] = population[ (rand()/float(RAND_MAX))*(NUMOFPLAYERS-1) ];
	opponent[i].SetMark('o');
      }
    }


  }
  /*
  SortPopulation();

  allStar = population[0];
  //GenPopulation();
  population[0] = allStar;
  PlayTournament(0, NUMOFPLAYERS, opponent);
  cout << "All star fitness: " << population[0].Fitness()/(float)TESTINGPOOLSIZE << endl;
  */
  SortPopulation();
  for( unsigned int i=0; i<(NUMOFPLAYERS*breedFraction); i++ ){
    newPopulation[i].SaveBrain(NUMOFGENERATIONS,i);
  }

  //PlayHumanTournament(&allStar);
}

void GA::PlayHumanTournament( Player *allStar){

  char inpt;
  while(1){
    PlayHumanGame(allStar);
    cout << "play again? [y/N]" << endl;
    cin >> inpt;
    if( inpt != 'y' ){
      break;
    }
  }

}


void GA::PlayTournament(int startNum, int endNum, vector< Player > opponent){

  //outputMutex.lock();
  //cout << "from: " << startNum << " to: " << endNum << endl;
  //outputMutex.unlock();


  TTT game = TTT();

  for( int p1Num=startNum; p1Num<endNum; p1Num++) {
    /*
    outputMutex.lock();
    cout << p1Num << " of " << startNum << " " << endNum << endl;
    outputMutex.unlock();
    */
    for( int p2Num=0; p2Num<TESTINGPOOLSIZE; p2Num++){
      PlayGame(&population[p1Num], &opponent[p2Num], &game, p1Num);
      game.clearBoard();
    }
  }
  //outputMutex.lock();
  //cout << "Time taken: " << float( clock () - t0 ) /  CLOCKS_PER_SEC << " sec" << endl;
  //outputMutex.unlock();
  //cout << "Time taken: " << float( clock () - t0 ) /  CLOCKS_PER_SEC << " sec" << endl;
}

void GA::Resume(int gen, int p){
  cout << "Resuming......" << endl;

  Player allStar = Player(0);
  cout << "Loading brain" << endl;
  allStar.LoadBrain(gen, p);
  //allStar.LoadBrain(NUMOFGENERATIONS, 0);



  PlayHumanTournament( &allStar);

}

void GA::PlayHumanGame(Player *p1){
  TTT game = TTT();

    bool wasWinner;
    char playerInput;
    int playerMove;
    p1->SetMark('x');
    //p2->SetMark('o');
    //game.printBoard();
    wasWinner = false;
    for( int turnNum=0; turnNum<9; turnNum++ ) {
        cout << "\n\n\n";
        game.printBoard();
        if( turnNum % 2 == 0){
          if( p1->TakeTurn( &game ) ){
            cout << "-->P1 wins" << endl;
            wasWinner = true;
            break;
          }
        } else {
          cout << "Enter square number: " << endl << ">> ";
          cin >> playerInput;
          playerMove = playerInput - '0';
          if( playerInput=='q'){
            return;
          }

          cout << "GOT " << (int)playerMove << endl;
          while(game.move( (int)playerMove/3, (int)playerMove%3, 'o' )){
            cout << "Invalid move, please try again or press 'q' to quit." << endl;
            cin >> playerInput;
            playerMove = playerInput - '0';
            //cout << "Checking winner for player " << mark << endl;
            if( playerInput=='q'){
              return;
            }
            cout << "GOT " << (int)playerMove << endl;
          }
          wasWinner = game.checkWinner();
          if( wasWinner ){
            cout << "-->P2 wins!" << endl;
            break;
          }
        }
    }
    if( !wasWinner ){
      cout << "tie!" << endl;
    }
    game.printBoard();
}

void GA::PlayGame(Player *p1, Player *p2, TTT *game, int playerNum){
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
          //cout << "p1 wins" << endl;
          //p1->wins += 1.0;
          p1->wins += 1.50 - (float)(turnNum-4)/4.0;
          //p2->losses += 1.0;
          wasWinner = true;
          break;
        }
      } else {
        //cout << "P2" << endl;
        if( p2->TakeTurn( game, &m[playerNum] ) ){
          //cout << "-->p2 wins" << endl;
          //p2->wins += 1.0;
          p1-> wins -= 2.50 - (float)(turnNum-4)/4.0;
          //p1->losses += 1.0;
          wasWinner = true;
          break;
        }
      }
      //game->printBoard();
  }
  //cout << float( clock () - t0 ) /  CLOCKS_PER_SEC << endl;
  //game.clearBoard();
  if( !wasWinner ){
    //p1->ties += 1.0;
    p1->wins += 0.25;
    //p2->ties += 1.0;
    //cout << "tie!" << endl;
  }

  //cout << "current fitness: " << p2->Fitness() << endl;

}





int main(int argc, char* argv[]){

  GA ga = GA();

  if( argc>1 ){
    int mode = atoi(argv[1]);
    cout << argv[0] << " " << mode << endl;
    if( mode==0){
      cout << "Running simulation" << endl;
      ga.RunSimulation();
    } else {
      cout << "Playing game" << endl;
      if(argc>3){
        ga.Resume(atoi(argv[2]), atoi(argv[3]));
      } else {
        ga.Resume(NUMOFGENERATIONS, 0);
      }
    }
  }
  return 1;
}
