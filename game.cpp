//game.cpp

// CSCI 1300 Spring 2023
// Authors: Tawhid Ather and Mallory Phillips
// Recitation: 104 – Tuhina Tripathi
// Project 3
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include<ctime>
#include<cmath>


#include "Map.h"
#include "monsters.h"
#include "status.h"
#include "players.h"
#include "NPC.h"

using namespace std;

/* Function takes input string and separator and places them into an array of defined size based on if deliminator is found
// 1. Sets temporary varaibles to be manipulated. 
    2. if string is empty return zero
    3. For each character in the string if it matches the deliminator the string is parsed and added to the array
    4. If splits is larger than array size return -1, if number of splits is zero return zero and wht whole string.
    */
vector<string> sort_split(string input_string, char separator) {
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

/* Function plays a game of rock paper scissors generating a random number and asking for user input
// 1. Sets temporary varaibles to be manipulated. 
    2. Creates a random number 0, 1, or 2. Prompts user input
    3. For the winning cases or a tie the computer will print, if a tie or loss happens, a incriment will happen anc loop will continue.
    4. If user wins, the funciton returns true otherwise, if the user loses three times they lose a party member.
    */
bool rps(){
    cout << "Let's play Boulder/Parchment/Shears! If you loose three times you'll loose a party member." << endl;
    bool end_game = 0;
    bool win_lose = 0;  // 1 means player wins 0 means computer won
    int user;
    int computer;
    int games_lost = 0;
    while(!end_game)    // loops until one is met, player win or death
    {
        computer = (rand()%2);  //generates 0,1,2 rock paper scissors
        cout << "Enter: \n(1) Boulder \n(2) Parchment \n(3) Shears" << endl;
        cin >> user;
        if(user == computer){   //still in the loop
            cout << "tie!" << endl;
            continue;
        }
        if(computer == 1 && user == 2){
           win_lose = 1;    //player win
           end_game = true; //breaks loop
           cout << "Congrats!!" << endl;
           continue;
        }else if(computer == 2 && user == 3){
           win_lose = 1;
           end_game = true;
           cout << "Congrats!!" << endl;
           continue;
        }else if(computer == 3 && user == 1){
           win_lose = 1;
           end_game = true;
           cout << "Congrats!!" << endl;
           continue;
        }
        else{
            cout << "you lose!" << endl;
            games_lost++;
        }
        if(games_lost == 3){
            end_game = true;    //if they lost three times they lose as a whole and return 0
        }
    }
   return win_lose;
}

/* Function creates various objects and allows the user to decide info and interact with such objects to defeat the wizard
// 1. Sets temporary varaibles to be manipulated. Take user input, allow user to purchase items. 
    2. While loop, as long as the game is not over it will allow user input. 
    3.Various function for user movemet and interaction with the map and other players and monsters.
    4. Game will end if player defeats sorcerer and or dies tryign with various in betweens and will print results into a file stream
    */

int main() {
    srand((unsigned int)time(0));   //random seed
    //all our initiailized variables
    Status status;
    Map map;
    Monsters monsters;
    string monster_name;
    NPC riddler;
    riddler.loadRidddles("riddles.txt");
    int action_choice = 0;
    int food;
    char player_move = ' ';
    bool game_over = false;
    bool game_win = false;
    bool fight_won = false;
    bool myKey = false;
    int turns = 0;
    int gold_lost = 0;
    int rand_num = 0;
    vector <string> results;
    vector <int> turns_to_win;

    map.setPlayerPosition((double(rand() / double(RAND_MAX)) * 12), ((double(rand() / double(RAND_MAX)) * 12)));    //creates map and player position
    map.setDungeonExit((double(rand() / double(RAND_MAX)) * 12), ((double(rand() / double(RAND_MAX)) * 12)));   //creates exit
    //set rooms
    while(map.getRoomCount() != 5) {
        map.addRoom((double(rand() / double(RAND_MAX)) * 12), ((double(rand() / double(RAND_MAX)) * 12)));
    }
    while(map.getNPCCount() != 5) {
        map.addNPC((double(rand() / double(RAND_MAX)) * 12), ((double(rand() / double(RAND_MAX)) * 12)));
    }
    status.setpartymembers();
    //prompt user in shop before start of the game
    cout << "Between the 5 of you, you have 100 gold pieces. \nYou will need to spend the some of your money on the following items:\n" << endl;
    cout << " - INGREDIENTS. To make food, you have to cook raw ingredients." << endl;
    cout << " - COOKWARE. If you want to cook, you have to have cookware first." << endl;
    cout << " - WEAPONS. You'll want at least one weapon per party member to fend off monsters." << endl;
    cout<< " - ARMOR. Armor increases the chances of surviving a monster attack.\n" << endl;
    cout<< "You can spend all of your money here before you start your journey, or you can save some to spend on merchants along the way. But beware, some of the merchants in this dungeon are shady characters, and they won't always give you a fair price..." << endl;
    status.merchantMenu(riddler);   //first call to menu using initialized NPC

    //loop with two conditions, game is not over or won, when game is won there is a different outcome that if not when over loop
    while (!game_over && !game_win) {
        status.printstatus();   //prints status at teh begining of each term
        if(!map.isExplored(map.getPlayerRow(), map.getPlayerCol())) {
            status.incrementAnger();    //movement will incriment anger
        }
        map.displayMap();   //prints player and map position each turn
        if(status.getAnger() == 100) {
            game_over = true;   // if player reaches max anger game terminates
            cout << "The sorcerer has reached max anger and smited the party. You were all killed." << endl;
            break;
        }
        //if the player is on the dungeon exit
        if (map.isDungeonExit(map.getPlayerRow(), map.getPlayerCol())) {
            if(map.getRoomCount() == 0) {
                cout << "You have vanquished the sorcerer and reached the exit!" << endl;
                game_win = true; // WIN THE GAME must make it to the exit
            }
            else{
                cout << "You can't exit the dungeon yet! Continue to explore the duegon and vanish the sorcer to unlock the exit." << endl;
                cout << "Select a direction to move" << endl;
                cin >> player_move; //must move
                while(map.move(player_move) == false) {
                    cout << "Please enter a valid direction" << endl;
                    cin >> player_move;
                }
            }
        }
        //if the player is on a room
        else if(map.isRoomLocation(map.getPlayerRow(), map.getPlayerCol())) {
            cout <<  "Select one:" << endl;
            cout << "1. Move" << endl;
            cout << "2. Open the Door"  << endl;
            cout << "3. Give up" << endl;
            cin >> action_choice;
            switch(action_choice) {     //may move away or challenge or use key 
                case 1:
                    cout << "Select a direction to move" << endl;
                    cin >> player_move;
                    while(map.move(player_move) == false) {
                        cout << "Please enter a valid direction" << endl;
                        cin >> player_move;
                    }
                    for(int i = 0; i < status.getpartysize(); i++) {
                        if (((double(rand() / double(RAND_MAX))) * 10) < 2) {
                            status.lostfullnessperplayer(i, 1);
                        }
                    }
                    break;
                case 2:
                    if(status.getKeys() >= 1) {
                        //if they have a key they my enter and fight the monster
                        cout << "You have a key so you open the door and now must fight a monster." << endl;
                        monsters.setmonsterdifficulty(status.getRoomsCleared() + 2);
                        monster_name = monsters.getmonster((double(rand() / double(RAND_MAX)) * monsters.get_number_of_monsters()));
                        cout << monster_name << " has emerged! Pepare for battle!" << endl;
                        //fightmonster function can be found in status file
                        fight_won = status.fightmonster();
                            if(fight_won) {
                                //misforutne 60%
                                if(rand()%9 < 6){
                                    status.randomMis(rand()%9,true);
                                }
                                //remove the room from the map
                                map.removeRoom(map.getPlayerRow(), map.getPlayerCol());
                                map.exploreSpace(map.getPlayerRow(), map.getPlayerCol());   //set explored
                                status.incrementRooms();    //adds to room cleared 
                                cout << "You have slain the " << monster_name << endl;
                                cout << "You have gained gold pieces and of ingredients from the monster" << endl;
                                //rewards from the monsters beat
                                status.incrementGold(10 * (status.getRoomsCleared()+1));
                                status.incrementIngredients(5 * (status.getRoomsCleared()+1));
                                monsters.monster_killed(monster_name);
                                if(((double(rand() / double(RAND_MAX))) * 10) < 1) {    
                                    status.incrementKeys();
                                    cout << "The " << monster_name << "dropped a key! What luck!" << endl;
                                }
                            }
                            else{
                                cout << "You have lost to the monster. Now suffer the consequence." << endl;
                                gold_lost = status.getGold() * 0.25;
                                status.incrementGold(-gold_lost);   // lose 1/4 your gold
                                status.incrementIngredients(-30);
                                status.loseKeys();
                                if(((double(rand() / double(RAND_MAX))) * 10) < 1) {
                                    if (status.getpartysize() == 2) {
                                        cout << "You are all alone. You succumb to the duengon and lose the game." << endl; //if party is too small
                                        game_over = true;
                                    } 
                                    else{
                                        status.killplayer(((double(rand() / double(RAND_MAX))) * (status.getpartysize()-2)));
                                    }
                                }
                            }
                    }
                    else if(rps()== 1){     //if the user has no keys they can play a game of chance and risk losing a player, calls rps function above
                        cout << "You have won rock paper scissors." << endl;
                        monsters.setmonsterdifficulty(status.getRoomsCleared() + 2);
                        //gets the moster of the room and allows challenge
                        monster_name = monsters.getmonster((double(rand() / double(RAND_MAX)) * monsters.get_number_of_monsters()));
                        cout << monster_name << " has emerged! Pepare for battle!" << endl;
                        fight_won = status.fightmonster();
                            if(fight_won) {
                                //misforutne 60%
                                if(rand()%9 < 6){
                                    status.randomMis(rand()%9,false);
                                }
                                map.removeRoom(map.getPlayerRow(), map.getPlayerCol());
                                map.exploreSpace(map.getPlayerRow(), map.getPlayerCol());
                                status.incrementRooms();
                                cout << "You have slain the " << monster_name << endl;
                                cout << "You have gained gold pieces and ingredients from the monster" << endl;
                                status.incrementGold(10 * (status.getRoomsCleared()+1));
                                status.incrementIngredients(5 * (status.getRoomsCleared()+1));
                                monsters.monster_killed(monster_name);
                                if(((double(rand() / double(RAND_MAX))) * 10) < 1) {
                                    status.incrementKeys();
                                    cout << "The " << monster_name << "dropped a key! What luck!" << endl;
                                }
                            }
                            else{
                                cout << "You have lost to the monster. Now suffer the consequence." << endl;
                                gold_lost = status.getGold() * 0.25;
                                status.incrementGold(-gold_lost);
                                status.incrementIngredients(-30);
                                status.loseKeys();
                                if(rand()%9 < 4){   //40% misfortune
                                    status.randomMis(rand()%9,false);
                                }
                                if(((double(rand() / double(RAND_MAX))) * 10) < 1) {
                                    if (status.getpartysize() == 2) {
                                        cout << "You are all alone. You succumb to the duengon and lose the game." << endl;
                                        game_over = true;
                                    } 
                                    else{
                                        status.killplayer(((double(rand() / double(RAND_MAX))) * (status.getpartysize()-2)));
                                    }
                                }
                            }
                    }else{
                        if (status.getpartysize() == 2) {
                        cout << "You are all alone. You succumb to the duengon and lose the game." << endl;
                        game_over = true;
                        } 
                        else{
                            status.killplayer(((double(rand() / double(RAND_MAX))) * (status.getpartysize()-2)));
                        }
                    }
                    break;
                case 3:
                    cout << "The party has given up." << endl;
                    game_over = true;
                    break;
                default:
                    cout << "Please choose a valid action" << endl;
                    while(action_choice < 1 || action_choice > 3) {
                        cout <<  "Select one:" << endl;
                        cout << "1. Move" << endl;
                        cout << "2. Speak to NPC"  << endl;
                        cout << "3. Give up" << endl;
                        cin >> action_choice;
                    }
                    break;
            }
        }
        //if the player has meet an NPC
        else if(map.isNPCLocation(map.getPlayerRow(), map.getPlayerCol())) {
            NPC myNPC(status.getRoomsCleared());
            myNPC.loadDialogue("npcDialogue.txt");
            myNPC.loadRidddles("riddles.txt");
            cout << "You have encounter an NPC! What would you like to do?" << endl;
            cout <<  "Select one:" << endl;
            cout << "1. Move" << endl;
            cout << "2. Speak to NPC"  << endl;
            cout << "3. Give up" << endl;
            cin >> action_choice;
            switch(action_choice) {
                case 1:
                    cout << "Select a direction to move" << endl;
                    cin >> player_move;
                    while(map.move(player_move) == false) {
                        cout << "Please enter a valid direction" << endl;
                        cin >> player_move;
                    }
                    for(int i = 0; i < status.getpartysize(); i++) {
                        if (((double(rand() / double(RAND_MAX))) * 10) < 2) {
                            status.lostfullnessperplayer(i, 1);
                        }
                    }
                    break;
                case 2:
                    cout << myNPC.getDialogue((double(rand() / double(RAND_MAX)) * 24)) << endl;
                    map.removeNPC(map.getPlayerRow(), map.getPlayerCol());
                    map.exploreSpace(map.getPlayerRow(), map.getPlayerCol());
                    cout << "Riddle me this and we can do business" << endl;
                    if(myNPC.getRiddle((double(rand() / double(RAND_MAX))) * 19)){  //if they get the riddle correct they may trade
                        status.merchantMenu(myNPC);
                    }else{
                        cout << "Oh well maybe next time" << endl;
                    }
                    break;
                case 3:
                    cout << "The party has given up." << endl;
                    game_over = true;
                    break;
                default:
                    cout << "Please choose a valid action" << endl;
                    while(action_choice < 1 || action_choice > 3) {
                        cout <<  "Select one:" << endl;
                        cout << "1. Move" << endl;
                        cout << "2. Speak to NPC"  << endl;
                        cout << "3. Give up" << endl;
                        cin >> action_choice;
                    }
                    break;
            }
        }
        else { //else regular actions occur
            cout <<  "Select one:" << endl;
            cout << "1. Move" << endl;
            cout << "2. Investigate"  << endl;
            cout << "3. Pick a Fight" << endl;
            cout << "4. Cook and Eat" << endl;
            cout << "5. Give up" << endl;
            cin >> action_choice;
            switch(action_choice) {
                case 1:
                    cout << "Select a direction to move" << endl;
                    cin >> player_move;
                    while(map.move(player_move) == false) {
                        cout << "Please enter a valid direction" << endl;
                        cin >> player_move;
                    }
                    for(int i = 0; i < status.getpartysize(); i++) {
                        if (((double(rand() / double(RAND_MAX))) * 10) < 2) {
                            status.lostfullnessperplayer(i, 1);
                        }
                    }
                    break;
                case 2: //investigate square and roll probability, could find a key, break something, get robbes and more
                    rand_num =((double(rand() / double(RAND_MAX))) * 9);
                    if(rand_num < 1){ // 10% chance
                        status.incrementKeys();
                        cout << "Congrats you found a key" << endl;
                    }else if(rand_num < 3){ // 1-3 non inclusive 20% chance
                        if(status.getRoomsCleared() > 0){   // must have cleared a room for it to work
                            cout << "Congrats you found a treasure" << endl;
                            switch(status.getRoomsCleared()){
                                case 1:
                                    status.setRings(status.getRings() + 1);
                                    break;
                                case 2:
                                    status.setNecklaces(status.getNecklaces() + 1);
                                    break;
                                case 3:
                                    status.setBracelets(status.getBracelets() + 1);
                                    break;
                                case 4:
                                    status.setCirclets(status.getCirclets() + 1);
                                    break;
                                case 5:
                                    status.setGoblets(status.getGoblets() + 1);
                                    break;
                            }   
                        }
                    }else if(rand_num < 5){ // 20% chance 
                        monster_name = monsters.getmonster((double(rand() / double(RAND_MAX)) * monsters.get_number_of_monsters()));
                        cout << monster_name << " AHEAD! THEY LOOK HOSTILE!" << endl;
                        if(status.getnumberweapons() >= 1) {
                            cout << "Choose if you want to fight or surrender" << endl;
                            cout << "1. Attack" << endl;
                            cout << "2. Surrender"  << endl;
                            cin >> action_choice;
                            switch(action_choice) {
                                case 1:
                                    cout << "You have choosen to fight the " << monster_name << ". Good Luck" << endl;
                                    fight_won = status.fightmonster();
                                    if(fight_won) {
                                        cout << "You have slain the " << monster_name << endl;
                                        cout << "You have gained gold pieces and ingredients from the monster" << endl;
                                        status.incrementGold(10 * (status.getRoomsCleared()+1));
                                        status.incrementIngredients(5 * (status.getRoomsCleared()+1));
                                        monsters.monster_killed(monster_name);
                                        if(((double(rand() / double(RAND_MAX))) * 10) < 1) {
                                            status.incrementKeys();
                                            cout << "The " << monster_name << "dropped a key! What luck!" << endl;
                                        }
                                    }
                                    else{
                                        cout << "You have lost to the monster. Now suffer the consequence." << endl;
                                        gold_lost = status.getGold() * 0.25;
                                        status.incrementGold(-gold_lost);
                                        status.incrementIngredients(-30);
                                        if(((double(rand() / double(RAND_MAX))) * 10) < 1) {
                                            if (status.getpartysize() == 2) {
                                                cout << "You are all alone. You succumb to the duengon and lose the game." << endl;
                                                game_over = true;
                                            } 
                                            else{
                                                status.killplayer(((double(rand() / double(RAND_MAX))) * (status.getpartysize()-2)));
                                            }
                                        }
                                    }
                                    break;
                                case 2:
                                    cout << "You have surrendered to" << monster_name << endl;
                                    if (status.getpartysize() == 2) {
                                    cout << "You are all alone. You succumb to the duengon and lose the game." << endl;
                                    game_over = true;
                                    } 
                                    else{
                                        status.killplayer(((double(rand() / double(RAND_MAX))) * (status.getpartysize()-2)));
                                    }
                                    break;
                            }
                        }
                    }else{
                        cout << "You didn't find anything!" << endl;
                    }
                    //reduce fullness randomly for each party member
                    for(int i = 0; i < status.getpartysize(); i++) {
                        if (((double(rand() / double(RAND_MAX))) * 10) < 5) {
                            status.lostfullnessperplayer(i, 1);
                        }
                    }
                    map.exploreSpace(map.getPlayerRow(), map.getPlayerCol());   // explored
                    break;
                case 3:
                //monster fight sequence
                    cout << "You decide to go looking for a fight. Lets see what you find." << endl;
                    monster_name = monsters.getmonster((double(rand() / double(RAND_MAX)) * monsters.get_number_of_monsters()));
                    cout << monster_name << " AHEAD! THEY LOOK HOSTILE!" << endl;
                    if(status.getnumberweapons() >= 1) {
                        cout << "Choose if you want to fight or surrender" << endl;
                        cout << "1. Attack" << endl;
                        cout << "2. Surrender"  << endl;
                        cin >> action_choice;
                        switch(action_choice) { //win or lose
                            case 1:
                                cout << "You have choosen to fight the " << monster_name << ". Good Luck" << endl;
                                fight_won = status.fightmonster();
                                if(fight_won) {
                                    cout << "You have slain the " << monster_name << endl;
                                    cout << "You have gained gold pieces and ingredients from the monster" << endl;
                                    status.incrementGold(10 * (status.getRoomsCleared()+1));
                                    status.incrementIngredients(5 * (status.getRoomsCleared()+1));
                                    monsters.monster_killed(monster_name);
                                    if(((double(rand() / double(RAND_MAX))) * 10) < 1) {
                                        status.incrementKeys();
                                        cout << "The " << monster_name << "dropped a key! What luck!" << endl;
                                    }
                                }
                                else{
                                    cout << "You have lost to the monster. Now suffer the consequence." << endl;
                                    gold_lost = status.getGold() * 0.25;
                                    status.incrementGold(-gold_lost);
                                    status.incrementIngredients(-30);
                                    if(((double(rand() / double(RAND_MAX))) * 10) < 1) {
                                        if (status.getpartysize() == 2) {
                                            cout << "You are all alone. You succumb to the duengon and lose the game." << endl;
                                            game_over = true;
                                        } 
                                        else{
                                            status.killplayer(((double(rand() / double(RAND_MAX))) * (status.getpartysize()-2)));
                                        }
                                    }
                                }
                            break;
                            case 2:
                                cout << "You have surrendered to" << monster_name << endl;
                                if (status.getpartysize() == 2) {
                                    cout << "You are all alone. You succumb to the duengon and lose the game." << endl;
                                    game_over = true;
                                } 
                                else{
                                    status.killplayer(((double(rand() / double(RAND_MAX))) * (status.getpartysize()-2)));
                                }
                            break;
                        }
                    }
                    else{   // no battle 
                        cout << "You have no weapons you must surrender" << endl;
                        if (status.getpartysize() == 2) {
                            cout << "You are all alone. You succumb to the duengon and lose the game." << endl;
                            game_over = true;
                        } 
                        else{
                            status.killplayer(((double(rand() / double(RAND_MAX))) * (status.getpartysize()-2)));
                        }
                    }
                    //random hunger decrease for each player
                    for(int i = 0; i < status.getpartysize(); i++) {
                        if (((double(rand() / double(RAND_MAX))) * 10) < 5) {
                            status.lostfullnessperplayer(i, 1);
                        }
                    }
                    if(rand()%9 < 4){   // random misfortune 40%
                        status.randomMis(rand()%9,false);
                    }
                    break;
                case 4:
                //cooking function
                    cout << "How many ingredients would you like to cook? enter a multiple of five please" << endl;
                    cin  >> food;
                    if(food % 5 == 0){      // food input must be a multiple of five 
                        cout << "What would you like to cook with (enter int 1,2, or 3): (1) Pot (2) Pan (3) Caouldrom" << endl;
                        cin >> action_choice;
                        switch(action_choice){
                            case 1: 
                            status.usePot(food);    // more details in status.cpp
                            break;
                            case 2:
                            status.usePan(food);
                            break;
                            case 3:
                            status.useCauldron(food);
                            break;
                            default:
                            cout <<"That was not an option." << endl;
                            break; 
                        }
                    }else{
                        cout << "Invalid input try again!" << endl;
                    }
                    if(rand()%9 < 4){   //rand misfortune
                        status.randomMis(rand()%9,false);
                    }
                    break;
                case 5: //gives up
                    cout << "The party has given up." << endl;
                    game_over = true;
                    break;
                default:    // invalid input, does not work for non int characters
                    cout << "Please choose a valid action" << endl;
                    while(action_choice < 1 || action_choice > 5) {
                        cout <<  "Select one:" << endl;
                        cout << "1. Move" << endl;
                        cout << "2. Investigate"  << endl;
                        cout << "3. Pick a Fight" << endl;
                        cout << "4. Cook and Eat" << endl;
                        cout << "5. Give up" << endl;
                        cin >> action_choice;
                    }  
                    break;
            }
        }   //checks status for starvation
        if(status.mainstarvedtodeath()) {   //bool value
            cout << "You have starved to death. What a pathetic death" << endl;
            game_over = true;
        }
        status.starvedtodeath();   //prints death message is starved
        if (status.getpartysize() == 1) {
            cout << "You are all alone. You succumb to the duengon and lose the game." << endl;
            game_over = true;
        } 
        turns++;    //incriments turns
    }
    if(game_win) {      //IF GAME is successfully won
        cout << "You succesfully killed the sorcerer and made it out of the dungeon! Congragulations! Here are you stats below." << endl;
    }
    else if(game_over) {    //death sad message
        cout << "You didn't make it out of the duegeon alive. Below are the stats of your demise." << endl;
    }
    //final stats
    cout << "Here are you final stats" << endl;
    cout << "Your Name" << endl;
    cout << status.getpartymembername(0) << endl;
    cout << "Party Members alive" << endl;
    cout << "Gold Remaining" << endl;
    cout << status.getGold() << endl;
    cout << "Treasure" << endl;
    status.printTreasures();
    cout << "Spaces explored" << endl;
    cout << map.numSpacesExplored() << endl;
    cout << "Monsters killed" << endl;
    cout << monsters.get_num_monsters_killed() << endl;
    cout << "Turns Elapsed" << endl;
    cout << turns << endl;
    //If game is won, to leaderboard file, prints stats, sorts within file
    if(game_win) {
        ofstream fout;
        fout.open ("results.txt");
        fout << status.getpartymembername(0) << "|" << turns << endl;
        fout.close ();
        ifstream fin;
        string postline = "";
        vector <string> temp;
        //check file opens
        fin.open("results.txt");
        while(!fin.eof()) {
            getline(fin, postline);
            temp = sort_split(postline, '|');
            if(results.size() == 0) {
                results.push_back(temp.at(0));
                turns_to_win.push_back(stoi(temp.at(1)));
            }
            else{
                for(int i = 0; i < results.size(); i++){
                    if (stoi(temp.at(1)) > turns_to_win.at(i)) {
                        results.insert((results.begin() + i), temp.at(0));
                        turns_to_win.insert((turns_to_win.begin() + i), stoi(temp.at(1)));
                        break;
                    }
                    else if(i == results.size() - 1) {
                        results.push_back(temp.at(0));
                        turns_to_win.push_back(stoi(temp.at(1)));
                    }
                }
            }
        }
        for (int i = results.size(); i > 0; i--) {
            cout << results.at(i-1) << endl;
        }
        fin.close();
    }
    return 0;
}