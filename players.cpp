#include "players.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

Players :: Players(string name) {   //default, name and full fullness
    player_name = name;
    player_fullness = 50;
}

string Players :: getplayername() {
    return player_name; //returns name
}

int Players :: getfullness() {
    return player_fullness; //returns fullness
}

int Players :: setfullness(int i){
    player_fullness = i;    //sets fullness to specific value
    return player_fullness;
}

/*
    is a setter to decrease the fullness of a give player
    return the value of the remain fullness
*/
int Players :: lose_fullness(int amount_lost){
    return player_fullness -= amount_lost;
}

