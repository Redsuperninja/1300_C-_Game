//NPC.cpp
 
// CSCI 1300 Spring 2023
// Authors: Tawhid Ather and Mallory Phillips
// Recitation: 104 – Tuhina Tripathi
// Project 3


#include <iostream>
#include <string>
#include <fstream>
#include "NPC.h"

using namespace std;

/* Function takes input string and separator and places them into an array of defined size based on if deliminator is found
// 1. Sets temporary varaibles to be manipulated. 
    2. if string is empty return zero
    3. For each character in the string if it matches the deliminator the string is parsed and added to the array
    4. If splits is larger than array size return -1, if number of splits is zero return zero and wht whole string.
    */
int split( string input_string, char separator, string arr[], int arr_size)
{
    //creates a variable to hold number of times string splits
    int numSplits = 0;
    // end if string is empty
    if(input_string.length() == 0)
    {
        return 0;
    }
    // temporary string to hold values
    string temp = "";
    int length = input_string.length();
    for(int i = 0; i < length ; i++)
    {
        if(input_string[i] != separator)
        {
            temp = temp + input_string[i]; 
        }
        //statement will run if target character is found as well as at the end
        if(input_string[i] == separator || i == length-1)
        {
            //arr value
            arr[numSplits]= temp;
            temp = "";
            numSplits += 1; 
        }
        //if splits are greater than array size return -1
        if(numSplits > arr_size)
            {
                return -1;
            }
    }
    //if no splits return whole line
    if(numSplits == 0)
    {
        arr[0] = input_string;
        return 1;
    }
    return numSplits;
}

//default constructor prices at begining of the game
NPC :: NPC()
{
    ingredient_price = 1;
    pot_price = 5;
    pan_price = 10;
    cauldron_price = 20;
    club_price = 2;
    spear_price = 2;
    axe_price = 15;
    rapier_price = 5;
    longsword_price = 50;
    armor_price = 5;
    vector <string> NPC_dialogue;
    vector <riddle> myRiddles;
}

//for input of rooms cleared, increases the price of each object to an int but still increased
NPC :: NPC(int rooms_cleared)
{
    if(rooms_cleared > 0){
        ingredient_price = 1 + 1 * (rooms_cleared * 0.25);
        pot_price = 5 + 5 * (rooms_cleared* 0.25);
        pan_price = 10 + 10 *(rooms_cleared * 0.25);
        cauldron_price = 20 + 20 *(rooms_cleared * 0.25);
        club_price = 2 + 2 *(rooms_cleared * 0.25);
        spear_price = 2 + 2 *(rooms_cleared * 0.25);
        axe_price = 15 + 15 *(rooms_cleared * 0.25);
        rapier_price = 5 + 5 *(rooms_cleared* 0.25);
        longsword_price = 50 + 50 *(rooms_cleared* 0.25);
        armor_price = 5 + 5 *(rooms_cleared* 0.25);
    }else{
        ingredient_price = 1;
        pot_price = 5;
        pan_price = 10;
        cauldron_price = 20;
        club_price = 2;
        spear_price = 2;
        axe_price = 15;
        rapier_price = 5;
        longsword_price = 50;
        armor_price = 5;
    }

    vector <string> NPC_dialogue;
    vector <riddle> myRiddles;
}

//must be done to add to the vetor of dialogue for each NPC
void NPC :: loadDialogue(string filename)
{
    // var to hold the line from file
    string line;
    //opens files stream
    ifstream fin;
    fin.open(filename);
    // if file fails to open end code
    if(fin.fail())
    {
        fin.close();
    }
    else
    {
        // when refrencing line from open file
        while(!fin.eof())
        {
            //retreive line of code from text file
            getline(fin,line);
            NPC_dialogue.push_back(line);   
        }
        //close files
        fin.close();
    }
}

//must be done to add to the vetor of dialogue for each NPC
void NPC :: loadRidddles(string filename){
    // var to hold the line from file
    string line;
    //opens files stream
    ifstream fin;
    fin.open(filename);
    // if file fails to open end code
    if(fin.fail())
    {
        fin.close();
    }
    else
    {
        // when refrencing line from open file
        while(!fin.eof())
        {
            //array that can hold two values
            string arr[2] = {"",""};
            //retreive line of code from text file
            getline(fin,line);
            // split line into sections, must consist of sender, header, body, and time 
            int num_splits = split(line,'~', arr, 2);
            riddle temp{arr[0],arr[1]};
            myRiddles.push_back(temp);
        }
        //close files
        fin.close();
    }
}

//pulls dialogue from vector 
string NPC :: getDialogue(int num){
    return NPC_dialogue.at(num);
}

//function pronpts user with riddle, if answer is correct true, else false
bool NPC :: getRiddle(int num){
    string response;
    riddle temp = myRiddles.at(num);
    cout << temp.body << endl;
    cin >> response;
    if(response == temp.answer){
        return true;
    }
    return false;
}

//all retreive price of objects in NPC
int NPC :: getingredientPrice(){
    return ingredient_price;
}
int NPC :: getPotPrice(){
    return pot_price;
}
int NPC :: getPanPrice(){
    return pan_price;
}
int NPC :: getCauldronPrice(){
    return cauldron_price;
}    
int NPC :: getClubPrice(){
    return club_price;
}
int NPC :: getSpearPrice(){
    return spear_price;
}    
int NPC :: getAxePrice(){
    return axe_price;
}
int NPC :: getRapierPrice(){
    return rapier_price;
}    
int NPC :: getLongswordPrice(){
    return longsword_price;
}
int NPC :: getArmorPrice(){
    return armor_price;
}