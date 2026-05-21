#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <windows.h>
#include "Chessboard.h"
#include "utilityfuncs.h"

using namespace std;

void ChessBoard :: setPieces(){
    char out;
    for(int i = 0;i < 8; i++){
        if(i == 0 || i == 1) out = 'B';
        if(i == 6 || i == 7) out = 'W';
        for(int j = 0; j < 8;j++){
            if(i == 0 || i ==7){
                if(j==0 || j==7) board[i][j] = new Rook(out);
                else if(j==1 || j==6) board[i][j] = new Knight(out);
                else if(j==2 || j==5) board[i][j] = new Bishop(out);
                else if(j == 3) board[i][j] = new Queen(out);
                else{board[i][j] = new King(out);}
            }
            else if(i == 1 || i ==6){
                board[i][j] = new Pawn(out);
            }
            else{
                board[i][j] = nullptr;
            }
        }
    }
}

ChessBoard :: ChessBoard(){setPieces();}

void ChessBoard ::game(){
    int choice;
    cout<<endl<<endl
        <<"--- Welcome to the CONSOLE CHESS ---\n\t"<<"1. Enter (1) to Play Chess.\n\t2. Enter (2) to Fetch Past games. \n\t3. Enter (3) to Quit\n\nChoice-->";
    cin>>choice;
    switch(choice){
        case 1:
            runGame();
        break;
        case 2:
            system("cls");
            fetchPastGame();
            game();
            break;
        case 3:
            cout<<"Exiting..";
            return;
            break;
        default:
            do{
                cout<<"Invalid number entered,please try again!\n";
                cin>>choice;
            } while(choice != 1 || choice != 2 || choice != 3);
    }
}
void ChessBoard :: printBoard(){
    system("cls");
    int totalPadding = 8*(cellX.length()) + 9;
    int left_Padding2 = (totalPadding - player2.length())/2;
    int left_Padding1 = (totalPadding - player1.length())/2;
    cout<<string(left_Padding2,' ')<<player2 + "(Black)"<<endl;
    int gap = 2+int(cellX.length()/2);
    int boardY = 8;
    cout<<setw(gap);
    for(int i = 0; i < 8;i++){
        cout<<boardX[i];
        if(i!=7) cout<<setw(cellX.length()+1);
    }
    cout<<endl;
    for(int i = 0;i<9;i++){
        cout<<cellCorner;
        for(int j = 0;j<8;j++){
            cout<<cellX<<cellCorner;
        }
        if(i!=8) cout<<endl;
        for(int m = 0;m <3 && i!=8;m++){
            cout<<cellY;
            for(int k = 0; (k < 8 );k++){
                if(board[i][k]!=nullptr && m==1){
                    string fullPeice = board[i][k]->retName() + "[" + board[i][k]->retPlayerType() + "]";
                    int totalPadding = 11 - fullPeice.length();
                    int leftPadding = totalPadding/2;
                    int rightPadding = totalPadding - leftPadding; 
                    cout<<string(leftPadding,' ')<<fullPeice<<string(rightPadding,' ')<<cellY;
                }
                else{
                    cout<<setw(12)<<cellY;
                }
            }
            if(m == 1) cout<<setw(2)<<boardY;
            cout<<endl;
        }
        boardY--;
    }
    cout<<endl<<string(left_Padding1,' ')<<player1 + "(White)"<<endl;
}
int ChessBoard :: verifyInput(vector<int> & vec,string & position){
    int error = vec[0];
    if(vec[0]==-1){
        vec.clear();
        cout<<"Invalid format!please try again--> ";
        cin>>position;
        vec = chessCordsTOarrayCords(position);
        error = vec[0];
    }
    return error;
};
void ChessBoard :: kill_MovePiece(){
    if(board[move_to_position[0]][move_to_position[1]] != nullptr){
        delete board[move_to_position[0]][move_to_position[1]];
    }
    board[move_to_position[0]][move_to_position[1]] = board[currentPosition[0]][currentPosition[1]];
    board[currentPosition[0]][currentPosition[1]] = nullptr;
}
int ChessBoard :: gameLoop(char playerType,string chance){
    //-2 means exit -1 means invalid input and 1 means correct validation + move and 2 means fails coz of check,10 means friend attacked! 
    int Code;
    bool moveVerified;
    Code = askCurrentPosition();
    if(Code>=0){
        if(board[currentPosition[0]][currentPosition[1]]->retPlayerType()!=playerType){
            string ask_inp;
            currentPosition.clear();
            cout<<chance<<"'s move!try again -->";
            cin>>ask_inp;
            currentPosition = chessCordsTOarrayCords(ask_inp);
            if(currentPosition[0]<0){return -1;}
        }
        Code = askFuturePosition(playerType);
        if(Code>=0){
            if(Code==10){
                cout<<"Error!friend attacked,try again --> ";
                Code = askFuturePosition(playerType);
                if(Code==10 || Code<0) return -3;
            }
            moveVerified = board[currentPosition[0]][currentPosition[1]]->validateMove(board,currentPosition[0],currentPosition[1],move_to_position[0],move_to_position[1]);
            if(moveVerified){
                kill_MovePiece();
                Code = 1; //fine execution
            }
            else{
                return -1;
            }
        }
    }
    if(Code == -1) return errorLog();
    currentPosition.clear();
    move_to_position.clear();
    return Code;
}
int ChessBoard :: askCurrentPosition(){
    string position_current;
    cout<<"Current position of the piece --> ";
    cin>>position_current;
    currentPosition = chessCordsTOarrayCords(position_current);
    return verifyInput(currentPosition,position_current);
}
int ChessBoard :: errorLog(){
    char post;
    cout<<"Invalid move,press R to enter again -->";
    cin>>post;
    return -3;
}
int ChessBoard :: askFuturePosition(char playerType){
    string pieece = board[currentPosition[0]][currentPosition[1]]->retName() + '[' + playerType + ']',position_future;
    cout<<"Enter you move for "<<pieece<<" --> ";
    cin>>position_future;
    move_to_position = chessCordsTOarrayCords(position_future);
    int Code = verifyInput(move_to_position,position_future);
    if(Code>=0){
        if(currentPosition[0]==move_to_position[0] && currentPosition[1]==move_to_position[1]) return -1;
        if(board[move_to_position[0]][move_to_position[1]]!=nullptr){
            if(board[move_to_position[0]][move_to_position[1]]->retPlayerType() == board[currentPosition[0]][currentPosition[1]]->retPlayerType()){
                move_to_position.clear();
                return 10;
            }
        }
    }
    return Code;
}
void ChessBoard :: runGame(){
    int repeat,chance_count = 0;
    string chance;
    char playerType;
    cout<<"Enter the name of player 1 (White) --> ";
    cin>>player1;
    cout<<"\nEnter the name of player 2 (Black) --> ";
    cin>>player2;
    do{
        this->printBoard();
        chance = (chance_count%2==0)? player1:player2;
        playerType = (chance==player1)? 'W':'B';
        cout<<chance<<" is now Playing! (press E to exit game or press R to enter again)...\n";
        repeat = gameLoop(playerType,chance);
        if(repeat == -1){repeat = errorLog();}
        if(repeat>=0) chance_count++;
        system("cls");
    }while(repeat !=-2 && (repeat==1 || repeat==-1 || repeat==-3));
}
void ChessBoard :: fetchPastGame(){
    int exit;
    cout<<"\n Press 0 to exit game record.\n";
    do{
        cin>>exit;
        if(exit != 0) cout<<"Invalid key pressed! Please try again -->";
    } while(exit!=0);
    system("cls");
}