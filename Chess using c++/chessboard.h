#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include <vector>
#include <string>
#include "piece.h"

using namespace std;
class ChessBoard{
    vector<int> currentPosition,move_to_position;
    Piece* board[8][8];
    bool play = true;
    char boardX[8] = {'A','B','C','D','E','F','G','H'};
    char cellCorner = '+',cellY = '|';
    int chance_count = 0;
    string cellX = "-----------",player1,player2;
    void setPieces();
    int verifyInput(vector<int> & vec,string & position);
    void kill_MovePiece();
    int gameLoop(char,string);
    void runGame();
    void fetchPastGame();
    int askCurrentPosition();
    int askFuturePosition(char);
    int errorLog();
    public:
        ChessBoard();
        void game();
        void printBoard();
};
#endif