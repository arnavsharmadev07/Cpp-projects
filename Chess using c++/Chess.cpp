#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <windows.h>
using namespace std;
vector<int> chessCordsTOarrayCords(string position);
class Piece{
    protected:
        char playerType;
        int myModulus(int n){
            if(n>=0) return n;
            else{return -n;}
        }
    public:
        Piece(){}
        Piece(char playerType){
            this->playerType = playerType;
        };
        char retPlayerType(){return playerType;}
        virtual string retName() = 0;
        void translateMoveTOCords();
        virtual bool validateMotion(Piece *board[8][8],int i_c = 0,int j_c = 0,int i_m = 0,int j_m = 0){
            char type1 = this->playerType;
            if(board[i_m][j_m]!=nullptr){
                char type2 = board[i_m][j_m]->retPlayerType();
                if(type1==type2) return false;
            }
            int rowStep = (i_c<i_m)? 1:-1;
            int colStep = (j_c<j_m)? 1:-1;
            while((i_c != i_m) || (j_c != j_m)){
                if(board[i_c][j_c] != nullptr && (i_c!=i_m && j_c !=j_m)){
                    return false;
                }
                i_c+=rowStep;
                j_c+=colStep;
            }
            return true;
        };
        virtual bool validateMove(Piece* board[8][8],int, int,string move) = 0;
        virtual ~Piece(){}
};
class Rook : virtual public Piece{
    string pieceName="Rook";
    public:
        Rook(){}
        Rook(char c) : Piece(c){}
        bool validateMove(Piece* board[8][8],int i,int j,string move) override{
            vector<int> X_Y = chessCordsTOarrayCords(move);
            int rowDifference = myModulus(X_Y[0]-i),colDifference = myModulus(X_Y[1]-j); 
            if((rowDifference==0 && colDifference>0) || (rowDifference >0 && colDifference==0)){
                if(validateMotion(board,i,j,X_Y[0],X_Y[1])){
                    return true;
                }
                return false;
            }
            else{return 0;}
        }
        string retName(){return pieceName;}
};
class Knight : public Piece{
    string pieceName="Knight";
    bool validateMotion(Piece* board[8][8],int i_c,int j_c,int i_m,int j_m) override {return true;}
    public:
        Knight(char c) : Piece(c){}
        bool validateMove(Piece* board[8][8],int i,int j,string move) override{
            vector<int> X_Y = chessCordsTOarrayCords(move);
            int colDifference = myModulus(X_Y[1]-j),rowDifference = myModulus(X_Y[0]-i);
            char type1 = this->playerType;
            if((colDifference == 2 && rowDifference ==1) || (colDifference == 1 && rowDifference ==2)){
                if(board[X_Y[0]][X_Y[1]]!= nullptr){
                    char type2 = board[X_Y[0]][X_Y[1]]->retPlayerType();
                    if(type1!=type2) return true;
                    else{ return false;}
                }
                else{
                    return true;
                }
            }
            else{return false;}
        }
        string retName(){return pieceName;}
};
class Bishop : virtual public Piece{
    string pieceName="Bishop";
    public:
        Bishop(){}
        Bishop(char c) : Piece(c){}
        bool validateMove(Piece* board[8][8],int i,int j,string move) override{
            vector<int> X_Y = chessCordsTOarrayCords(move);
            int colDifference = myModulus(X_Y[1]-j),rowDifference = myModulus(X_Y[0]-i);
            if(colDifference==rowDifference){
                if(validateMotion(board,i,j,X_Y[0],X_Y[1])){
                    return true;
                }
                return false;
            }
            else{return false;}
        }
        string retName(){return pieceName;}
};
class Queen : public Bishop,public Rook{
    string pieceName="Queen";
    public:
        Queen(char c) : Piece(c){}
        bool validateMove(Piece* board[8][8],int i,int j,string move) override{
            bool rookMove = Rook::validateMove(board,i,j,move);
            bool bishopMove = Bishop::validateMove(board,i,j,move);
            if(rookMove || bishopMove){return true;}
            else{return false;}
        }
        string retName(){return pieceName;}
};
class King : public Piece{
    string pieceName="King";
    bool validateMotion(Piece* board[8][8],int i_c,int j_c,int i_m,int j_m){
        int rowGap = (i_c<i_m)?1:-1;
        int colGap = (j_c<j_m)?1:-1;
        while(i_c==i_m && j_c==j_m){}
    }
    public:
        King(char c) : Piece(c){}
        bool validateMove(Piece* board[8][8],int i,int j,string move) override{
            vector<int> X_Y = chessCordsTOarrayCords(move);
            int colDifference = myModulus(X_Y[1]-j),rowDifference = myModulus(X_Y[0]-i);
            if(colDifference == 1 || rowDifference == 1){

            }
        }
        string retName(){return pieceName;}
};
class Pawn : public Piece{
    string pieceName="Pawn";
    bool validateMotion(Piece* board[8][8],int i_c,int j_c,int i_m,int j_M) override{return true;}
    public:
        Pawn(char c) : Piece(c){}
        bool validateMove(Piece* board[8][8],int i,int j,string move) override{
            vector<int> X_Y = chessCordsTOarrayCords(move);
            int colDifference = X_Y[1]-j,rowDifference = X_Y[0]-i;
            if((this->playerType == 'B' && rowDifference>0) || (this->playerType == 'W' && rowDifference<0)){
                if(myModulus(rowDifference) == 1 && colDifference == 0){
                    if(board[X_Y[0]][X_Y[1]] == nullptr){
                        return true;
                    }
                }
                if(myModulus(rowDifference)== 1 && myModulus(colDifference) == 1 && board[X_Y[0]][X_Y[1]]!=nullptr){
                    if(this->playerType != board[X_Y[0]][X_Y[1]]->retPlayerType()){
                        return true;
                    }
                }
                if(i==1 || i == 6 && myModulus(rowDifference) == 2 && myModulus(colDifference) == 0){
                    return true;
                }
            }
            return false;
        }
        string retName() override{return pieceName;}
};
class ChessBoard{
    bool play = true;
    char boardX[8] = {'A','B','C','D','E','F','G','H'};
    void kill_MovePiece(int x,int y,vector<int> move){
        if(board[move[0]][move[1]] != nullptr){
            delete board[move[0]][move[1]];
        }
        board[move[0]][move[1]] = board[x][y];
        board[x][y] = nullptr;
    }
    void runGame();
    void fetchPastGame(){
        int exit;
        cout<<"\n Press 0 to exit game record.\n";
        do{
            cin>>exit;
            if(exit != 0) cout<<"Invalid key pressed! Please try again -->";
        } while(exit!=0);
        system("cls");
    }
    char cellCorner = '+',cellY = '|';
    string cellX = "-----------",player1,player2;
    Piece* board[8][8];
    void setPieces();
    int gameLoop();
    void loopAction1(vector<int> & vec,string & position,int & exitCode){
        if(vec[0]==-2){exitCode = -2; return;}
        if(vec[0]==-1){
            vec.clear();
            cout<<"Invalid format!please try again--> ";
            cin>>position;
            vector<int> temp = chessCordsTOarrayCords(position);
            vec.push_back(temp[0]);
            vec.push_back(temp[1]);
            if(vec[0] == -2){exitCode =-2;return;}
            if(vec[0] == -1){exitCode =-1;return;}
        }
        exitCode  = 1;
        return;
    };
    int chance_count = 0;
    public:
        ChessBoard(){setPieces();}
        void game();
        void printBoard();
};
void ChessBoard :: printBoard(){
    system("cls");
    int totalPadding = 8*(cellX.length()) + 9;
    int left_Padding2 = (totalPadding - player2.length())/2;
    int left_Padding1 = (totalPadding - player1.length())/2;
    cout<<string(left_Padding2,' ')<<player2<<endl;
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
    cout<<endl<<string(left_Padding1,' ')<<player1<<endl;
}
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
void ChessBoard ::game(){
    int choice;
    cout<<endl<<endl<<endl
        <<"|--- Welcome to the CONSOLE CHESS ---|\n\t"<<"1. Enter (1) to Play Chess.\n\t2. Enter (2) to Fetch Past games. \n\t3. Enter (3) to Quit\n\nChoice-->";
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
int ChessBoard :: gameLoop(){
    //-2 means exit -1 means invalid input and 1 means correct validation + move and 2 means fails coz of check 
    int exitCode;
    string chance,position_current,position_move;
    bool moveVerified;
    char playerType;
    if(chance_count%2 == 0){ chance = player1;playerType = 'W';}
    else{chance = player2; playerType = 'B';}
    cout<<chance<<" is now Playing!(press E to exit game)...\n";
    cout<<"Current position of the piece --> ";
    cin>>position_current;
    vector<int> cPlace = chessCordsTOarrayCords(position_current);
    loopAction1(cPlace,position_current,exitCode);
    if(board[cPlace[0]][cPlace[1]]->retPlayerType() != playerType){
        cPlace.clear();
        cout<<chance<<"'s move!try again -->";
        cin>>position_current;
        vector<int> temp = chessCordsTOarrayCords(position_current);
        cPlace.push_back(temp[0]);
        cPlace.push_back(temp[1]);
        if(board[cPlace[0]][cPlace[1]]->retPlayerType() != playerType) return -1;
    }
    switch(exitCode){
        case -2:
            return -2;
            break;
        case -1:
            return -1;
            break;
        default:break;
    }
    if(exitCode == 1){
        string pieece = board[cPlace[0]][cPlace[1]]->retName() + '[' + chance.at(0) + ']';
        cout<<endl;
        cout<<"Enter you move for "<<pieece<<" --> ";
        cin>>position_move;
        if(position_current==position_move){
            cout<<"Invalid move!please try again -->";
            cin>>position_move;
            if(position_current == position_move){exitCode = -1; return exitCode;}
        }
        vector<int> mPlace = chessCordsTOarrayCords(position_move);
        loopAction1(mPlace,position_move,exitCode);
        switch(exitCode){
            case -2:
                return -2;
                break;
            case -1:
                return -1;
                break;
            default:break;
        }
        if(exitCode == 1){
            bool moveVerified = board[cPlace[0]][cPlace[1]]->validateMove(board,cPlace[0],cPlace[1],position_move);
            if(moveVerified){
                kill_MovePiece(cPlace[0],cPlace[1],mPlace);
            }
        }
    }
    cPlace.clear();
    chance_count++;
    return 1;
}
void ChessBoard :: runGame(){
    int repeat;
    cout<<"Enter the name of player 1 (White) --> ";
    cin>>player1;
    cout<<"\nEnter the name of player 2 (Black) --> ";
    cin>>player2;
    player2+="(Black)";
    player1+="(White)";
    do{
        this->printBoard();
        repeat = gameLoop();
        system("cls");
    }while(repeat == 1 && repeat !=-2 || repeat==-1);
}
vector<int> chessCordsTOarrayCords(string position){
    //-1 is an error!!!!
    //-2 is an exit flag!!!
    vector<int> temp;
    bool noterror1  = 0,noterror2 = 0;
    if(position.length()!=2){
        if(position == "E"){ temp.push_back(-2);}
        else{
            temp.push_back(-1);
        }
        return temp;
    }
    for(char a = 'a'; a<='h';a++){
        if(tolower(position[0])==a){
            noterror1 = 1;
        }
    }
    for(int i = 1;i<=8;i++){
        if((position[1]-'0')==i){
            noterror2 = 1;
        }
    }
    if(!noterror1 && !noterror2){
        temp.push_back(-1);
        return temp;
    }
    int y = tolower(position[0]) - 'a'; // a is a decimal number learn 1
    int x=8-int(position.at(1) - '0');
    if(x <0 || x>7 || y>7 || y <0){
        temp.push_back(-1);
        return temp;  
    } 
    temp.push_back(x);
    temp.push_back(y);
    return temp;
}
int main(){
    ChessBoard c;
    c.game();
    return 0;
}