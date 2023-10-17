#ifndef PLAYERS_H
#define PLAYERS_H
#include <string>
#include "monsters.h"
using namespace std;

class Players{
    public:
        Players(string name);   //default constructor
        string getplayername();
        //getter setter anc lose functions to edit fullness
        int getfullness();
        int lose_fullness(int amount_lost);
        int setfullness(int);
        
    private:
        string player_name; // name 
        int player_fullness;    //fullness level

};

#endif