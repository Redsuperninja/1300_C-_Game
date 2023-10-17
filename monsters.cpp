#include "monsters.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

/*
split a string into parts 
1) check if string inputed is none empty
2) loop until you find a delimator/separator
3) store characters into a string until a delimator is found
4) when found store in antoher string in the array
5) return the number of splits found
Parameters: string input_string, char separator, string arr[], int array_size
Retun number of splits
*/
vector<string> split(string input_string, char separator) {
    int string_length = input_string.length();
    string temp = "";
    vector<string> vect;
    //a for loop checking every character in the string
    for (int i = 0; i < string_length; i++) {
        //check if the character is a separator and if not store it in the string array
        if (input_string[i] != separator) {
            temp += input_string[i];
        }
        else {
            vect.push_back(temp);
            temp = "";
        }
    }
    vect.push_back(temp);
    return vect;
}

//default constructor
Monsters :: Monsters() {
    //declare a stream for the files
    monster_strength = 1;
    num_monsters_killed = 0;
    ifstream fin;
    string postline = "";
    vector <string> temp;
    //check file opens
    fin.open("monsters.txt");
    while(!fin.eof()) {
        getline(fin, postline);
        temp = split(postline, ',');
        if(stoi(temp.at(1)) == monster_strength) {
            monster_names.push_back(temp.at(0));
        }  
    } 
    number_of_monsters = monster_names.size();
    fin.close();
}

void Monsters :: setmonsterdifficulty(int difficulty) {
    //declare a stream for the files
    monster_strength = difficulty;
    ifstream fin;
    string postline = "";
    vector <string> temp;
    monster_names.clear();
    //check file opens
    fin.open("monsters.txt");
    while(!fin.eof()) {
        getline(fin, postline);
        temp = split(postline, ',');
        if(stoi(temp.at(1)) == monster_strength) {
            monster_names.push_back(temp.at(0));
        }  
    } 
    number_of_monsters = monster_names.size();
    fin.close();
}

//get a monster to fight
string Monsters :: getmonster(int rand) {
    string temp;
    temp = monster_names.at(rand);
    return temp;
}

//referance monsters stored in vector
int Monsters :: get_number_of_monsters() {
    return number_of_monsters;
}

//remove monster from vector
void Monsters :: monster_killed(string monster_name) {
    for(int i = 0; i < number_of_monsters-1; i++) {
        if(monster_names.at(i) == monster_name) {
            monster_names.erase(monster_names.begin()+i);
            number_of_monsters--;
            num_monsters_killed++;
        }
    }
}

//tally for monsters killed
int Monsters :: get_num_monsters_killed() {
    return num_monsters_killed;
}

