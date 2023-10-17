//monsters.h

// CSCI 1300 Spring 2023
// Authors: Tawhid Ather and Mallory Phillips
// Recitation: 104 – Tuhina Tripathi 
// Project 3

#ifndef Monsters_H
#define Monsters_H
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class Monsters{
    public:
        Monsters();
        void setmonsterdifficulty(int difficulty);
        string getmonster(int rand);
        int get_number_of_monsters();
        void monster_killed(string monster_name);
        int get_num_monsters_killed();
    private:
        vector<string> monster_names;   //vector to referance with monsters
        int monster_strength;   // level of monster read from file
        int number_of_monsters;     // size or vector
        int num_monsters_killed;    //num of monsters removed
};

#endif