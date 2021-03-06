#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>
#include <vector>
#include <fstream>
#include <map>

#ifndef TTT_H
#define TTT_H
#endif


using namespace std;

#define N 3
#define M 3

class TTT
{

public:
  int board[N][M];
  //vector<int> playerValues {-1, 1};
  //vector<char> playerTolkens {'x', 'o'};
  map<char, int> playerMap;
  TTT();

  unsigned int turnNum;

  void clearBoard();
  void getBoardLinear( float *outpt );
  void getBoardLinearLong( float *outpt );
  int unitTest();

  vector< int > getEmptySpaces();
  int getMarkValue( char m );
  int isValidMove(int x, int y);
  void printBoard();
  int move(int x, int y, char playerNum );
  int checkWinner();

};
