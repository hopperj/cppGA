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
  playerMap = { {'x',-1}, {'o',1} };
}

int TTT::getMarkValue( char m ){
  return playerMap[m];
}

void TTT::clearBoard(){

  turnNum = 0;
  for( int i=0; i<N; i++ ) {
    for( int j=0; j<M; j++ ) {
      board[i][j] = 0;
    }
  }
}

int TTT::isValidMove(int x, int y){
  return board[x][y] == 0 && x < N && y < M;
}

void TTT::printBoard(){
  for( int i=0; i<N; i++ ) {
    cout << "\t";
    for( int j=0; j<M; j++ ) {
      if( board[i][j] == -1){
        cout << 'x' << " ";
      } else if( board[i][j] == 1){
        cout << 'o' << " ";
      } else {
        cout << ' ' << " ";
      }
      //cout << board[i][j] << " ";
      if( j<M-1){
	       cout << "| ";
      }
    }
    if( i<N-1){
      cout << "\n\t---------" << endl;
    }

  }
  cout << "\n\n\n" << endl;
}

int TTT::move(int x, int y, char playerToken ){
  //cout << "trying " << x << " " << y << endl;
  if( isValidMove(x,y) ){
    //board[x][y] = playerValues[ playerNum ];
    //cout << "Using player token: " << playerToken << endl;
    board[x][y] = playerMap[ playerToken ];
    //printBoard();
    //cout << "p" << playerMap[ playerToken ] << endl;
    //cout << x << " " << y << " set by " << playerToken << " " << board[x][y] << endl;
    turnNum++;
    return 0;
  }
  return 1;
}

void TTT::getBoardLinear( float *outpt ){
  //cout << "\n" << endl;
  vector<float> line = vector<float>(N*M,0.0);
  for( int i=0; i<N; i++){
    for( int j=0; j<M; j++ ){
      //line[i+j] = (float)board[i][j];
      *outpt = (float)board[i][j];
      //cout << line[i+j] << "\t";
      //cout << *outpt << "\t";
      outpt++;
    }
  }
}

void TTT::getBoardLinearLong( float *outpt ){
  //cout << "\n" << endl;
  vector<float> line = vector<float>(2*N*M,0.0);
  for( int i=0; i<N; i++){
    for( int j=0; j<M; j++ ){
      //line[i+j] = (float)board[i][j];
      if( board[i][j] == -1){
          *outpt = (float)board[i][j];
          outpt++;

          *outpt = 0.0;
          outpt++;
      } else {
        *outpt = 0.0;
        outpt++;

        *outpt = (float)board[i][j];
        outpt++;
      }
    }
  }
}

vector< int > TTT::getEmptySpaces(){
  vector< int > empty = vector< int >();

  for( int i=0; i<N; i++ ){
    for( int j=0; j<M; j++ ){
      if( board[i][j] == 0){
	       empty.push_back(3*i+j);
      }
    }
  }
  return empty;
}

int TTT::checkWinner(){

  if( turnNum < 4 ){
    return 0;
  }

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
