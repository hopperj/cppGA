#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>
#include <vector>
#include <fstream>


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
  vector<int> playerValues {-1, 1};
  vector<char> playerTolkens {'x', 'o'};
  TTT();

  void clearBoard();
  vector<double> getBoardLinear();
  int unitTest();
  
  int isValidMove(int x, int y);
  void printBoard();
  int move(int x, int y, int playerNum );
  int checkWinner();
};

