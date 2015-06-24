#include "GA.h"
#include "TTT.h"

#ifndef NEURALNETWORK_H
#include "NeuralNetwork.h"
#endif

#include "Player.h"

using namespace std;

GA::GA(){

}




int main(){
  TTT game = TTT();
  Player p1 = Player('x');
  Player p2 = Player('o');


  //p1.brain.printIHW();
  
  p1.TakeTurn( game );

  
  cout << "Cleaning up" << endl;

  return 1;
}
