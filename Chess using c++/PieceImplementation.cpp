#include <iostream>
#include <vector>
#include <string>
#include "Piece.h"
#include "utilityfuncs.h"

using namespace std;

/*       Piece class       */
Piece :: Piece(){}
Piece :: Piece(char playerType){
    this->playerType = playerType;
};
int Piece :: myModulus(int n){
    if(n>=0) return n;
    else{
        return -n;
    }
}
char Piece :: retPlayerType(){
    return playerType;
}
bool Piece :: validateMotion(Piece *board[8][8],int i_c,int j_c,int i_m,int j_m){
    int rowStep = (i_c==i_m)? 0:(i_c<i_m)? 1:-1;
    int colStep = (j_c==j_m)? 0:(j_c<j_m)? 1:-1;
    while((i_c != i_m) || (j_c != j_m)){
        i_c+=rowStep;
        j_c+=colStep;
        if(board[i_c][j_c] != nullptr){
            return false;
        }
    }
    return true;
};
Piece :: ~Piece(){}

/*       Rook class       */

Rook :: Rook(){}
Rook :: Rook(char c) : Piece(c){}
bool Rook :: validateMove(Piece* board[8][8],int i,int j,int i_m,int j_m){
    int rowDifference = myModulus(i_m-i),colDifference = myModulus(j_m-j); 
    if((rowDifference==0 && colDifference>0) || (rowDifference >0 && colDifference==0)){
        if(validateMotion(board,i,j,i_m,j_m)){
            return true;
        }
        return false;
    }
    else{return 0;}
}

/*       Knight class       */

Knight :: Knight(char c) : Piece(c){}
bool Knight :: validateMotion(Piece* board[8][8],int i_c,int j_c,int i_m,int j_m){return true;}
bool Knight :: validateMove(Piece* board[8][8],int i,int j,int i_m,int j_m){
    int colDifference = myModulus(j_m-j),rowDifference = myModulus(i_m-i);
    if((colDifference == 2 && rowDifference ==1) || (colDifference == 1 && rowDifference ==2)){
        return true;
    }
    else{return false;}
}

/*       Bishop class       */

Bishop :: Bishop(){}
Bishop :: Bishop(char c) : Piece(c){}
bool Bishop :: validateMove(Piece* board[8][8],int i,int j,int i_m,int j_m){
    int colDifference = myModulus(j_m-j),rowDifference = myModulus(i_m-i);
    if(colDifference==rowDifference){
        if(validateMotion(board,i,j,i_m,j_m)){
            return true;
        }
        return false;
    }
    else{return false;}
}

/*       Queen class       */

Queen :: Queen(char c) : Piece(c){}
bool Queen :: validateMove(Piece* board[8][8],int i,int j,int i_m,int j_m){
    bool rookMove = Rook::validateMove(board,i,j,i_m,j_m);
    bool bishopMove = Bishop::validateMove(board,i,j,i_m,j_m);
    if(rookMove || bishopMove){return true;}
    else{return false;}
}

/*       King class       */

King :: King(char c) : Piece(c){}
bool King :: validateMotion(Piece* board[8][8],int i_c,int j_c,int i_m,int j_m){return true;}
bool King :: validateMove(Piece* board[8][8],int i,int j,int i_m,int j_m){
    int colDifference = myModulus(j_m-j),rowDifference = myModulus(i_m-i);
    if(colDifference == 1 || rowDifference == 1){
        return true;
    }
}

/*       Pawn class       */

Pawn ::  Pawn(char c) : Piece(c){}
bool Pawn :: validateMotion(Piece* board[8][8],int i_c,int j_c,int i_m,int j_M){return true;}
bool Pawn :: validateMove(Piece* board[8][8],int i,int j,int i_m,int j_m){
    int colDifference = j_m-j,rowDifference = i_m-i;
    if((this->playerType == 'B' && rowDifference>0) || (this->playerType == 'W' && rowDifference<0)){
        if(myModulus(rowDifference) == 1 && colDifference == 0){
            if(board[i_m][j_m] == nullptr){
                return true;
            }
        }
        if(myModulus(rowDifference)== 1 && myModulus(colDifference) == 1 && board[i_m][j_m]!=nullptr){
            if(this->playerType != board[i_m][j_m]->retPlayerType()){
                return true;
            }
        }
        if(i==1 || i == 6 && myModulus(rowDifference) == 2 && myModulus(colDifference) == 0){
            return true;
        }
    }
    return false;
}

// retPiece name function for all classes
string Rook   :: retName(){return pieceName;}
string Knight :: retName(){return pieceName;}
string Bishop :: retName(){return pieceName;}
string Queen  :: retName(){return pieceName;}
string King   :: retName(){return pieceName;}
string Pawn   :: retName(){return pieceName;}