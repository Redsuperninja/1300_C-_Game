//Status.h

// CSCI 1300 Spring 2023
// Author: Mallory Phillips
// Recitation: 104 – Tuhina Tripathi
// Project 3 

#ifndef STATUS_H
#define STATUS_H 
#include "players.h"
#include "NPC.h"
#include <iostream>
#include <vector>

using namespace std;

class Status
{
    private:
    int rooms_cleared; // rooms 
    int keys;
    int anger;
    int gold;
    int ingredients;
    //cooking equiptment
    int pots;
    int pans;
    int cauldrons;
    //weapons
    int clubs;
    int rapier;
    int spears;
    int longsword;
    int axes;
    int armor;
    //treasures
    int rings;  //silver ring, referenced with R
    int necklaces;  //ruby necklace, referenced with N
    int bracelets;  //emerald Bracelet, B
    int circlets;  //diamond circlet, C
    int goblets;  //gem-encrusted goblet, G
    vector<Players> party;  // vector of players

    public:
    // default constructor
    Status();
    //getter and setter for rooms_cleared
    int getRoomsCleared();
    void incrementRooms();
    //getter and setter for keys
    int getKeys();
    void incrementKeys();
    void loseKeys();
    //getter and setter for anger
    int getAnger();
    void incrementAnger();
//Inventory Functionality
    //getter and setter for gold
    int getGold();
    void incrementGold(int);
    //getter and setter for ingredients
    int getIngredients();
    void incrementIngredients(int);
//Weapon Funcitonality
    void incrementClub(int);
    int getClub();
    void incrementRapier(int);
    int getRapier();
    void incrementSpears(int);
    int getSpear();
    void incrementLongsword(int);
    int getLongsword();
    void incrementAxe(int);
    int getAxe();
    void incrementArmor(int);
    int getArmor();
//Cookware functionality
    //pot opperations
    void usePot(int);
    int getPot();
    void incrementPot();
    //pan opperations
    void usePan(int);
    int getPan();
    void incrementPan();
    //Cauldron opperations
    void useCauldron(int);
    int getCauldron();
    void incrementCauldron();
//Tresasure functionality
    //getter and setter functions for Rings
    int getRings();
    void setRings(int);
    //getter and setter functions for Necklaces
    int getNecklaces();
    void setNecklaces(int);
    //getter and setter functions for Bracelets
    int getBracelets();
    void setBracelets(int);
    //getter and setter functions for Circlets
    int getCirclets();
    void setCirclets(int);
    //getter and setter functions for Goblets
    int getGoblets();
    void setGoblets(int);
    //print Function
    void printTreasures();
    //print status
    void printstatus();
    //void party members and actions
    void setpartymembers();
    string getpartymembername(int number);
    int getpartysize();
    //kill party member
    void killplayer(int num);
    void lostfullnessperplayer(int pos, int num);
    //starvaition
    void starvedtodeath();
    bool mainstarvedtodeath();
    //weapons for fight function
    int getnumberweapons();
    bool fightmonster();
    //merchant menu for sales
    void merchantMenu(NPC myMerchant);
    //random misfortunes
    void randomMis(int,bool);
};

#endif