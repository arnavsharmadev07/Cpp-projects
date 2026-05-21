#include <iostream>
#include <vector>
#include "utilityfuncs.h"
vector<int> chessCordsTOarrayCords(string position){
    //-1 is an error!!!!
    //-2 is an exit flag!!!
    //-3 is an unknown bug!!!
    vector<int> temp;
    bool noterror1  = 0,noterror2 = 0;
    if(position.length()!=2){
        if(position == "E"){ temp.push_back(-2);}
        else if(position == "R"){temp.push_back(-3);}
        else{
            temp.push_back(-1);
        }
    }
    else if(position.length() == 2){
        int i = position.at(1)-'0';
        for(char a = 'a'; a<='h';a++){
            if(tolower(position[0])==a){
                noterror1 = 1;
            }
        }
        if(i>=1 && i<=8){
            noterror2 = 1;
        }
        if(!noterror1 || !noterror2){
            temp.push_back(-1);
        }
        int y = tolower(position[0]) - 'a'; // a is a decimal number learn 1
        int x = 8 - int(position[1] - '0');
        if(x <0 || x>7 || y>7 || y <0){
            temp.push_back(-1);
  
        } 
        temp.push_back(x);
        temp.push_back(y);
    }
    else{
        temp.push_back(-3);
    }
    return temp;
}