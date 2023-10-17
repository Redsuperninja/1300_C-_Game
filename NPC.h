//NPC.h

// CSCI 1300 Spring 2023
// Authors: Tawhid Ather and Mallory Phillips
// Recitation: 104 – Tuhina Tripathi
// Project 3 

#ifndef NPC_H
#define NPC_H
#include <iostream>
#include <vector>

using namespace std;

struct riddle   // smaller objects to go with the NPC
{
    string body;    //question prompt
    string answer;  //target string
};

class NPC
{
    private:
    //price value for every item sold by the merchant
    int ingredient_price;
    int pot_price;
    int pan_price;
    int cauldron_price;
    int club_price;
    int spear_price;
    int axe_price;
    int rapier_price;
    int longsword_price;
    int armor_price;
    //vectors of dialogue to be called in interactions with NPC
    vector <riddle> myRiddles;
    vector <string> NPC_dialogue;
    
    public:
    void loadDialogue(string);  //places dialogue into private vector
    void loadRidddles(string);  //places riddel objects into private vector
    NPC();  //default constructor
    NPC(int); //constructor with string, file name that will referance a text file for dialogue
    string getDialogue(int);    //returns string to be printed
    bool getRiddle(int);    //if riddle is correct or wrong
    //getters for price of objects
    int getingredientPrice();
    int getPotPrice();
    int getPanPrice();
    int getCauldronPrice();
    int getClubPrice();
    int getSpearPrice();
    int getAxePrice();
    int getRapierPrice();
    int getLongswordPrice();
    int getArmorPrice();
};

#endif