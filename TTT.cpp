#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>
#include <vector>
#include <fstream>

#include "TTT.h"

using namespace std;


TTT::TTT(){
  clearBoard();
}

void TTT::clearBoard(){
  for( int i=0; i<N; i++ ) {
    for( int j=0; j<M; j++ ) {
      board[i][j] = 0;
    }
  }
}

int TTT::isValidMove(int x, int y){
  return board[x][y] == 0;
}

void TTT::printBoard(){
  for( int i=0; i<N; i++ ) {
    cout << "\t";
    for( int j=0; j<M; j++ ) {
      cout << board[i][j] << " ";
      if( j<M-1){
	cout << "| ";
      }
    }
    cout << "\n\t---------" << endl;
  }
  cout << "\n\n\n" << endl;
}

int TTT::move(int x, int y, int playerNum ){
  if( isValidMove(x,y) ){
    board[x][y] = playerValues[ playerNum ];
    return 0;
  }  
  return 1;
}

vector<double> TTT::getBoardLinear(){
  vector<double> line = vector<double>(N*M,0.0);

  for( int i=0; i<N; i++){
    for( int j=0; j<M; j++ ){
      line[i+j] = board[i][j];
    }
  }

  return line;
}

int TTT::checkWinner(){

  int sum=0;

  // Check Rows
  for( int i=0; i<N; i++ ){    
    for( int j=0; j<M; j++ ){
      sum += board[i][j];
    }
    if( abs(sum) == 3 ){
      return 1;
    }
    sum = 0;
  }

  // Check Columns
  for( int j=0; j<M; j++ ){    
    for( int i=0; i<N; i++ ){
      sum += board[i][j];
    }
    if( abs(sum) == 3 ){
      return 1;
    }
    sum = 0;
  }

  // Check Diagonal  
  for( int j=0; j<M; j++ ){
      sum += board[j][j];
  }
  if( abs(sum) == 3 ){
    return 1;
  }
  sum = 0;
  

  // Check Other Diagonal
  for( int i=0; i<N; i++ ){
    sum += board[i][M-i-1];
  }
  if( abs(sum) == 3 ){
    return 1;
  }
  sum = 0;

  
  return 0;
}



int TTT::unitTest(){


  move(0,0,0);
  move(1,1,0);
  move(2,2,0);
  
  cout << "Winning? " << checkWinner() << endl;  
  printBoard();
  clearBoard();




  move(0,2,0);
  move(1,1,0);
  move(2,0,0);
  
  cout << "Winning? " << checkWinner() << endl;  
  printBoard();
  clearBoard();




  move(0,2,1);
  move(1,2,1);
  move(2,2,1);
  
  cout << "Winning? " << checkWinner() << endl;  
  printBoard();
  clearBoard();




  move(0,1,1);
  move(1,1,1);
  move(2,1,1);
  
  cout << "Winning? " << checkWinner() << endl;  
  printBoard();
  clearBoard();




  move(0,1,1);
  move(1,1,0);
  move(2,1,1);
  
  cout << "Winning? " << checkWinner() << endl;  
  printBoard();
  clearBoard();


  return 0;

}

  
