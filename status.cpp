//Status.cpp

// CSCI 1300 Spring 2023
// Author: Mallory Phillips
// Recitation: 104 – Tuhina Tripathi
// Project 3

//int srand(time(0));

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include<cstdlib>
#include<ctime>
#include<cmath>

#include "Map.h"
#include "monsters.h"
#include "status.h"
#include "players.h"
#include "NPC.h"

using namespace std;

Status :: Status()  //default constructor, begining of the game
{
    rooms_cleared = 0;
    keys = 0;
    anger = 0;
    gold = 100;
    ingredients = 0;
    pots = 0;
    pans = 0;
    cauldrons = 0;
    clubs = 0;
    spears = 0;
    rapier = 0;
    axes = 0;
    longsword = 0;
    armor = 0;
    rings = 0;  //silver ring, referenced with R
    necklaces = 0;  //ruby necklace, referenced with N
    bracelets = 0;  //emerald Bracelet, B
    circlets = 0;  //diamond circlet, C
    goblets = 0;
}

//getter and setter for rooms_cleared
int Status :: getRoomsCleared(){
    return rooms_cleared;
}
void Status :: incrementRooms(){
    rooms_cleared++;
}

//getter and setter for keys
int Status :: getKeys(){
    return keys;
}
void Status :: incrementKeys(){
    keys++;
}
void Status :: loseKeys() {
    keys--;
    if(keys < 0) {
        keys = 0;
    }
}

//getter and setter for anger
int Status :: getAnger(){
    return anger;
}
void Status :: incrementAnger(){
    anger++;
}

//getter and setter for gold
int Status :: getGold(){
    return gold;
}
void Status :: incrementGold(int g){
    gold+= g;
    if(ingredients < 0) {
        ingredients = 0;
    }
}

//Weapon Funcitonality
//club functionality
void Status :: incrementClub(int c){
    clubs += c;
}
int Status :: getClub(){
    return clubs;
}
//rapier fnctinality
void Status ::incrementRapier(int r){
    rapier += r;
}
int Status :: getRapier(){
    return rapier;
}
//spear functionality
void Status ::incrementSpears(int s){
    spears += s;
}
int Status :: getSpear(){
    return spears;
}
//longsword functionality
void Status ::incrementLongsword(int l){
    longsword += l;
}
int Status :: getLongsword(){
    return longsword;
}
//axe functionality
void Status ::incrementAxe(int a){
    axes += a;
}
int Status :: getAxe(){
    return axes;
}
//armor functionality
void Status ::incrementArmor(int a){
    axes += a;
}
int Status :: getArmor(){
    return armor;
}

//getter and setter for ingredients
int Status :: getIngredients(){
    return ingredients;
}
void Status :: incrementIngredients(int i){
    ingredients += i;
    if(ingredients < 0) {
        ingredients = 0;
    }
}

//pot opperations
int Status :: getPot()
{
    return pots;
}
void Status :: incrementPot(){
    pots++;
}
void Status :: usePot(int food)
{
    if(pots == 0 || food > ingredients){    // if you dont have the item or ingredients
        cout << "You can't cook that silly." << endl;
        return;
    }
    int random = (rand() % 3);
    if(random == 1){    //random probability it breaks
        pots -= 1;
        cout << "Your pot broke you! You now have " << pots << " pots." << endl;
        return;   
    }else{  //else works
        cout << "What a delicious meal! Each of you has gained " << food / 5 << ". YUM!!" << endl;
        ingredients -= food;
        for(int i = 0; i < party.size(); i++){
            party.at(i).lose_fullness(-(food / 5));   //incriment total party fullness
        }
    }
    return;    //returns
}
//pan opperations
int Status :: getPan()
{
    return pans;
}
void Status :: incrementPan(){
    pans++;
}
void Status :: usePan(int food)
{
    if(pans == 0 || food > ingredients){  // if you dont have the item or ingredients
        cout << "You can't cook that silly." << endl;
        return ;   //returns
    }
    int random = (rand() % 9);
    if(random == 1){
        pans -= 1;
        cout << "Your pan broke you! You now have " << pans << " pans." << endl;
        return;  //return  if breaks
    }else{
        cout << "What a delicious meal! Each of you has gained " << food / 5 << ". YUM!!" << endl;
        ingredients -= food;
        for(int i = 0; i < party.size(); i++){
            party.at(i).lose_fullness(-(food / 5));
        }
    }
    return;    //returns still in invintory
}
//Cauldron opperations
int Status :: getCauldron()
{
    return cauldrons;
}
void Status :: useCauldron(int food)
{
    if(cauldrons == 0 || food > ingredients){
        cout << "You can't cook that silly." << endl;
        return;   //returns 0 if not ran
    }
    int random = (rand() % 50);
    if(random == 1){
        cauldrons -= 1;
        //cout << "Your cauldron broke you! You now have " << cauldrons << " cauldrons." << endl;
        return;  //returns -1 if item breaks
    }else{
        cout << "What a delicious meal! Each of you has gained " << food / 5 << ". YUM!!" << endl;
        ingredients -= food;
        for(int i = 0; i < party.size(); i++){
            party.at(i).lose_fullness(-(food / 5));
        }
    }
    return;    //returns 
}
void Status :: incrementCauldron(){
    cauldrons++;
}
//Treasure Funcitonality 
//getter and setter functions for Rings
int Status :: getRings(){
    return rings;
}
void Status :: setRings(int ring){
    rings = ring;
}

//getter and setter functions for Necklaces
int Status :: getNecklaces(){
    return necklaces;
}
void Status :: setNecklaces(int neck){
    necklaces = neck;
}

//getter and setter functions for Bracelets
int Status :: getBracelets(){
    return bracelets;
}
void Status :: setBracelets(int brace){
    bracelets = brace;
}

//getter and setter functions for Circlets
int Status :: getCirclets(){
    return circlets;
}
void Status :: setCirclets(int circle){
    circlets = circle;
}

//getter and setter functions for Goblets
int Status :: getGoblets(){
    return goblets;
}
void Status :: setGoblets(int gobble){
    goblets = gobble;
}
//print treasures 
void Status :: printTreasures()
{
    cout << "R: " << rings << " | N: " << necklaces << " | B: " << bracelets << " | C: " << circlets << " | G: " << goblets << endl;
}

//print status
void Status :: printstatus() {
    cout << "+-------------+" << endl;
    cout << "| STATUS      |" << endl;
    cout << "+-------------+" << endl;
    cout << "|  Rooms Cleared: " << rooms_cleared << " | Keys: " << keys << " | Anger Level: " << anger << endl;
    cout << "+-------------+" << endl;
    cout << "| INVENTORY   |" << endl;
    cout << "+-------------+" << endl;
    cout << "| Gold        | " << gold << endl;
    cout << "| Ingredients | " << ingredients << "kg" << endl;
    cout << "| Cookware    | P: " << pots << " | F: " << pans << " | C: " << cauldrons << endl;
    cout << "| Weapons     | C: " << clubs << " | S: " << spears << " | R: " << rapier << " | B: " << axes << " | L: " << longsword << endl;
    cout << "| Armor       | " << armor << endl;
    cout << "| Treasures   | R: " << rings << " | N: " << necklaces << " | B: " << bracelets << " | C: " << circlets << " | G: " << goblets << endl;
    cout << "+-------------+" << endl;
    cout << "| PARTY       |" << endl;
    cout << "+-------------+" << endl;
    for(int i = 0; i < party.size(); i++) {
        cout << "| " << party.at(i).getplayername() << " | Fullness: " << party.at(i).getfullness() << endl;
    }
}

//Creates vector of party members for the whole game, only called once
void Status :: setpartymembers() {
    string player_names = "";
    cout << "Enter your name: " << endl;
    cin >> player_names;
    party.push_back(Players(player_names));
    cout << "Enter the name of your first party member: " << endl;
    cin >> player_names;
    party.push_back(Players(player_names));
    cout << "Enter the name of your second party member: " << endl;
    cin >> player_names;
    party.push_back(Players(player_names));
    cout << "Enter the name of your third party member: " << endl;
    cin >> player_names;
    party.push_back(Players(player_names));
    cout << "Enter the name of your fourth and final party member: " << endl;
    cin >> player_names;
    party.push_back(Players(player_names));
}

//retreives private information since the vector party cannot be called in outside
string Status :: getpartymembername (int num) {
    return party.at(num).getplayername();
}

//other party opperator
int Status :: getpartysize() {
    return party.size();
}

//removes player and prints death message
void Status :: killplayer(int num) {
    cout << party.at(num+1).getplayername() << " has died" << endl;
    party.erase(party.begin()+(num+1));
}

//removes fullness in party for public use
void Status :: lostfullnessperplayer(int pos, int num) {
    party.at(pos).lose_fullness(num);
}

//if any member of the party has a fullness less than or zero, death
bool Status :: mainstarvedtodeath() {
    if(party.at(0).getfullness() <= 0) {
        return true;
    }
    else{
        return false;
    }
}

//prints and removes party member if dead
void Status :: starvedtodeath() {
    for(int i = 1; i < party.size(); i++) {
        if(party.at(i).getfullness() <= 0){
            cout << party.at(i).getplayername() << " has died" << endl;
            party.erase(party.begin()+i);
        }
    }
}

//sum of the wapons in the party
int Status :: getnumberweapons() {
    int temp = clubs + rapier + spears + longsword + axes;
    return temp;
}

/*
    use the monster array and randomly call a monster that exists on the floor
    using the strenth of the parties weapons and armor roll to see if they win the fight
    if they win retrun true if not return false
    if they win remove the monster from the array so it can't be called
    otherwise kill a player afterwards
    specific calculation
*/
bool Status :: fightmonster() {
    int weapon_strength = 0;
    int different_weapons = 0;
    int challenge = rooms_cleared + 1;
    int r_1 = (double(rand() / double(RAND_MAX)) * 6);
    int r_2 = (double(rand() / double(RAND_MAX)) * 6);
    if(clubs >= 1) {
        different_weapons++;
    }
    if(rapier >= 1) {
        different_weapons++;
    }
    if(spears >= 1) {
        different_weapons++;
    }
    if(longsword >= 1) {
        different_weapons++;
    }
    if(axes >= 1) {
        different_weapons++;
    }
    weapon_strength = (clubs + spears + (rapier*2) + (axes*3) + (longsword*4));
    int outcome = ((r_1 * weapon_strength + different_weapons) - ((r_2 * challenge)/armor));
    if (outcome > 0) {
        return true;
    }
    else{
        return false;
    }
}

//Menu that allows user choice to purchase items. updating their Inventory and conforming purchase of various materials
void Status :: merchantMenu(NPC myMerchant)
{
    //declare temporary varaiables
    int menu = 0;
    int choice = 0;
    int num = 0;
    char yeno;
    char treasure;

    // while loop until choice to leave
    while(menu != 6){
        while(menu < 1 || menu > 6){    //while there is not a valid choice
            cout << "\n+-------------+\n| INVENTORY   |\n+-------------+\n| Gold        | " << gold << "\n| Ingredients | " << ingredients << " kg \n| Cookware    | P: " << pots << " | F: " << pans << " | C: " << cauldrons << endl;
            cout << "| Weapons     | C: " << clubs << " | S: " << spears << " | R: " << rapier << " | B: " << axes << " | L: " << longsword << "\n| Armor       | " << armor << "\n| Treasures   | R: " << rings << " | N: " << necklaces << " | B: " << bracelets << " | C: " << circlets << " | G: " << goblets << "" << endl;
            cout <<"\nChoose one of the following: \n1. Ingredients: To make food, you have to cook raw ingredients. \n2. Cookware: You will need something to cook those ingredients. \n3. Weapons: It's dangerous to go alone, take this!" << endl;
            cout << "4. Armor: If you want to survive monster attacks, you will need some armor. \n5. Sell treasures: If you find anything shiny, I would be happy to take it off your hands. \n6. Leave: Make sure you get everything you need, I'm leaving after this sale!" << endl;
            cin >> menu;
            if(menu < 1 || menu > 6){   //if choice meets no criteria invalid, return to menu
                cout << "Invalid input. Please enter a number between 1 and 6." << endl;
                menu = 0; }
            cout << endl;
        }
        switch(menu){
        case 1: //ingredients
            cout << "I would recomend 10 kg of food per party member for your voyage!" << endl;
            cout << "How many kg of ingredients do you need [" << myMerchant.getingredientPrice() << " Gold/kg]? (Enter a positive mulitple of 5, or 0 to cancel)" << endl;
            cin >> num;
            if(num % 5 != 0){   //must be multiple of five to work 
                cout << "Invalid input." << endl;
                menu = 1;
                break; }    
            while(num != 0){    // if is real intiger
                cout << "You want to buy " << num << " kg of ingredients for "<< num * myMerchant.getingredientPrice() << " Gold? (y/n)" << endl;
                cin >> yeno;    //confirm in yeno (yes/no)
                if(yeno =='y'){
                    while(gold <= num * myMerchant.getingredientPrice()){   // if value costs more than they have
                        cout << "You don't have enough money for that. \nIs there another amount you would like (enter 0 to quit)?" << endl;
                        cin >> num;
                    }
                    if(num > 0){
                        ingredients += num; //give them goods
                        gold -= (num * myMerchant.getingredientPrice());    //charge the gold
                        cout << "\nThank you for your patronage! What else can I get for you?" << endl;
                        num = 0;    //return to menu
                    }
                }if(yeno == 'n'){
                    num = 0;
                }
            }
            cout << endl;
            menu = 0;   //return to menu
            break;
        case 2: //purchase cookware
            cout << "I have a several types of cookware, which one would you like?\nEach type has a different probability of breaking when used, marked with (XX%).\n" << endl;
            cout << "\nChoose one of the following:\n1. (25%) Ceramic Pot ["<< myMerchant.getPotPrice() <<" Gold]\n2. (10%) Frying Pan ["<< myMerchant.getPanPrice() <<" Gold]\n3. ( 2%) Cauldron ["<< myMerchant.getCauldronPrice() <<" Gold]\n4. Cancel" << endl;
            cin >> choice;
            if(choice != 4){    //quantity
            cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
            cin >> num; }
            if(num > 0){
                switch(choice){
                    case 1: //pots
                        cout << "You want to buy " << num << " Ceramic Pot(s) for " << num * myMerchant.getPotPrice()<<" gold? (y/n)" << endl;
                        cin >> yeno;    //confirm
                        if(yeno =='y'){
                            if(gold <= num * myMerchant.getPotPrice()){
                                cout << "You don't have enough money for that. Broke a**!" << endl;
                                break;
                            }else{
                                pots += num;
                                gold-= (num*myMerchant.getPotPrice());
                                cout << "\nThank you for your patronage! What else can I get for you?" << endl;
                            }  
                        }else{
                        num = 0; 
                        }
                        break;
                    case 2: //pans
                        cout << "You want to buy " << num << " Frying Pan(s) for " << num * myMerchant.getPanPrice()<<" gold? (y/n)" << endl;
                        cin >> yeno;    //confir,=m
                        if(yeno =='y'){
                            if(gold <= num * myMerchant.getPanPrice()){
                                cout << "You don't have enough money for that. Broke a**!" << endl;
                                break;
                            }else{
                                pans += num;
                                gold -= (num*myMerchant.getPanPrice());
                                cout << "\nThank you for your patronage! What else can I get for you?" << endl;
                            }  
                        }else{
                        num = 0; 
                        }
                        break;
                    case 3: //cauldron
                        cout << "You want to buy " << num << " Cauldron(s) for " << num * myMerchant.getCauldronPrice()<<" gold? (y/n)" << endl;
                        cin >> yeno;
                        if(yeno =='y'){
                            if(gold <= num * myMerchant.getCauldronPrice()){
                                cout << "You don't have enough money for that. Broke a**!" << endl;
                                break;
                            }else{
                                cauldrons += num;
                                gold -= (num*myMerchant.getCauldronPrice());
                                cout << "\nThank you for your patronage! What else can I get for you?" << endl;
                            }  
                        }else{
                        num = 0; 
                        }
                        break;
                    case 4:
                        break;
                    default:
                    cout << "That was not a valid input, back to the menu!" << endl;
                }
            }
            menu = 0;   //return to menu
            break;
        case 3: //weapons
            cout << "I have a plentiful collection of weapons to choose from, what would you like? \nNote that some of them provide you a special bonus in combat, marked by a (+X).\n" << endl;
            cout << "1. Stone Club ["<< myMerchant.getClubPrice() << " Gold] \n2. Iron Spear [" << myMerchant.getSpearPrice() << " Gold] \n3. (+1) Mythril Rapier [" << myMerchant.getRapierPrice() << " Gold] \n4. (+2) Flaming Battle-Axe [" << myMerchant.getAxePrice() << " Gold]\n5. (+3) Vorpal Longsword [" << myMerchant.getLongswordPrice() << " Gold]\n6. Cancel" << endl;
            cin >> choice;
            if(choice != 6){
            cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
            cin >> num; }
            if(num > 0){
                switch(choice){
                    case 1: //clubs
                        cout << "You want to buy " << num << " Stone Club(s) for " << num * myMerchant.getClubPrice()<<" gold? (y/n)" << endl;
                        cin >> yeno;
                        if(yeno =='y'){
                            if(gold <= num * myMerchant.getClubPrice()){
                                cout << "You don't have enough money for that. Broke a**!" << endl;
                                break;
                            }else{
                                clubs += num;
                                gold -= (num*myMerchant.getClubPrice());
                                cout << "\nThank you for your patronage! What else can I get for you?" << endl;
                            }  
                        }else{
                        num = 0; }
                        break;
                    case 2: //spears
                         cout << "You want to buy " << num << " Iron Spear(s) for " << num * myMerchant.getSpearPrice()<<" gold? (y/n)" << endl;
                        cin >> yeno;
                        if(yeno =='y'){
                            if(gold <= num * myMerchant.getSpearPrice()){
                                cout << "You don't have enough money for that. Broke a**!" << endl;
                                break;
                            }else{
                                spears += num;
                                gold -= (num*myMerchant.getSpearPrice());
                                cout << "\nThank you for your patronage! What else can I get for you?" << endl;
                            }  
                        }else{
                        num = 0;    }
                        break;
                    case 3: //rapiers
                        cout << "You want to buy " << num << " (+1) Mythril Rapier(s) for " << num * myMerchant.getRapierPrice()<<" gold? (y/n)" << endl;
                        cin >> yeno;
                        if(yeno =='y'){
                            if(gold <= num * myMerchant.getRapierPrice()){
                                cout << "You don't have enough money for that. Broke a**!" << endl;
                                break;
                            }else{
                                rapier += num;
                                gold -= (num * myMerchant.getRapierPrice());
                                cout << "\nThank you for your patronage! What else can I get for you?" << endl;
                            }  
                        }else{
                        num = 0;    }
                        break;
                    case 4: // axes
                        cout << "You want to buy " << num << " (+2) Flaming Battle-Axe(s) for " << num * myMerchant.getAxePrice()<<" gold? (y/n)" << endl;
                        cin >> yeno;
                        if(yeno =='y'){
                            if(gold <= num * myMerchant.getAxePrice()){
                                cout << "You don't have enough money for that. Broke a**!" << endl;
                                break;
                            }else{
                                axes += num;
                                gold -= (num * myMerchant.getAxePrice());
                                cout << "\nThank you for your patronage! What else can I get for you?" << endl;
                            }  
                        }else{
                            num = 0;    }
                        break;
                    case 5: //longswords
                         cout << "You want to buy " << num << " (+3) Vorpal Longsword(s) for " << num * myMerchant.getLongswordPrice()<<" gold? (y/n)" << endl;
                        cin >> yeno;
                        if(yeno =='y'){
                            if( gold <= num * myMerchant.getLongswordPrice()){
                                cout << "You don't have enough money for that. Broke a**!" << endl;
                                break;
                            }else{
                                longsword += num;
                                gold -= (num * myMerchant.getLongswordPrice());
                                cout << "\nThank you for your patronage! What else can I get for you?" << endl;
                            }  
                        }else{
                            num = 0;    }
                        break;
                    case 6: //cancel
                        break;
                    default:    //not valid input
                        cout << "That was not a valid input, back to the menu!" << endl;
                }
            }
            cout << endl;
            menu = 0;
            break;
        case 4://ARMOR
            cout << "Armor protects you from monsters. Equipping your team with the maximum amount of armor (1 armor per person) will maximize your chances of survival during an attack. \nAdding more armor on top of the maximum amount will not increase your chances further." << endl;
            cout << "How many suits of armor can I get you? (Enter a positive integer, or 0 to cancel)" << endl;
            cin >> num;
            if(num < 0){    //input validation
                cout << "Invalid input." << endl;
                menu = 2;
                break; }    
            while(num != 0){
                cout << "You want to buy " << num << " suit(s) of armor for "<< num * myMerchant.getArmorPrice() << " Gold? (y/n)" << endl;
                cin >> yeno;
                if(yeno =='y'){
                    while(gold <= num * myMerchant.getArmorPrice()){
                        cout << "You don't have enough money for that. \nIs there another amount you would like (enter 0 to quit)?" << endl;
                        cin >> num;
                    }
                    if(num > 0){
                        armor += num;
                        gold -= (num * myMerchant.getArmorPrice());
                        cout << "\nThank you for your patronage! What else can I get for you?" << endl;
                        num = 0;
                    }
                }if(yeno == 'n'){
                    num = 0;
                }
            }
            menu = 0;   //return to menu
            break;
        case 5: //sell treasures
            cout << "What treasures would you like to sell me?\nCheck your invintory, it looks like you have:" << endl;
            if(rings > 0){  //must have treasure to see price
                cout << "Silver ring (R) - 10 gold pieces each" << endl;
            }
            if(necklaces > 0){
                cout << "Ruby necklace (N) - 20 gold pieces each" << endl;
            }
            if(bracelets > 0){
                cout << "Emerald bracelet (B) - 30 gold pieces each" << endl;
            }
            if(circlets > 0){
                cout << "Diamond circlet (C) - 40 gold pieces each" << endl;
            }
            if(goblets > 0){
                cout << "Gem-encrusted goblet (G) - 50 gold pieces each" << endl;
            }
            cout << "\nEnter the key displayed above (if any) to sell me you treasure (enter case sensitive letter from display)\nIf you don't see anything come back after you have cleared a few levels!" << endl;
            cin >> treasure;
            cout << "How many are you willing to share? (positive integer or zero to quit" << endl;
            cin >> num;
            if(num > 0){
                switch(treasure){
                case 'R':   //rings
                    if(rings >= num){   //must have more than wanting to sell
                        rings -= num;
                        gold += (num * 10);
                    }else{
                        cout << "You dont have enough to sell silly!" << endl;
                    }
                    num = 0;
                    break;
                case 'N':   //necklace
                    if(necklaces >= num){
                        necklaces -= num;
                        gold += (num * 20);
                    }else{
                        cout << "You dont have enough to sell silly!" << endl;
                    }
                    num = 0;
                    break;
                case 'B':   //bracelets
                    if(bracelets >= num){
                        bracelets -= num;
                        gold += (num * 30);
                    }else{
                        cout << "You dont have enough to sell silly!" << endl;
                    }
                    num = 0;
                    break;
                case 'C':   //circlet
                    if(circlets >= num){
                        circlets -= num;
                        gold +=(num * 40);
                    }else{
                        cout << "You dont have enough to sell silly!" << endl;
                    }
                    num = 0;
                    break;
                case 'G':   //gobblets
                    if(goblets >= num){
                        goblets -= num;
                        gold +=(num * 50);
                    }else{
                        cout << "You dont have enough to sell silly!" << endl;
                    }
                    num = 0;
                    break;
                default:
                    cout << "That's an invalid input silly goose no treasure for you!" << endl;
                }
            }
            menu = 0;
            break;
        case 6: 
            cout << "Are you sure you're finished? You won't be able to buy anything else from me! (y/n)" << endl;
            cin >> yeno;
            if(yeno == 'n'){
                menu = 0;
                break;
            }
        } 
    }
}

//random misfortune calls probability of random things happening to you and if attempted on door 100% probability of something happenong
void Status :: randomMis(int first, bool door){ //first is a ransom int from 0-9
    int second; //second probability
    switch(first){
        case 0: case 1: case 2: //three cases 30% robbery
            cout << "OH NO! Your team was robbed by dungeon bandits!" << endl;
            ingredients -= 10;
            second = rand() % 3;   // generates random 0,1,2, or 3
                switch(second){
                case 0:
                    if(cauldrons > 0){
                    cout << "You lost 1 cauldron!" << endl;
                    cauldrons--;
                    break;
                    }
                case 1:
                    if(pots > 0){
                    cout << "You lost 1 pot!" << endl;
                    pots--;
                    break;
                    }
                case 2: 
                    if(pans > 0){
                    cout << "You lost 1 pan!" << endl;
                    pans--;
                    break;
                    }
                default:
                    if(armor > 0){
                    armor--;
                    cout << "You lost 1 armor" << endl;
                    }
                    break;
                }
            break;
        case 3: // 10% probability broken weapon
            second = rand() % 5;
            switch(second){
            case 0:
                if(clubs > 0){
                cout << "OH NO! Your Club broke!" << endl;
                clubs--;
                break;
                }
            case 1:
                if(rapier > 0){
                cout << "OH NO! Your +1 Rapier broke!" << endl;
                rapier--;
                break;
                }
            case 2: 
                if(spears > 0){
                cout << "OH NO! Your Spear broke!" << endl;
                spears--;
                break;
                }
            case 3:
                if(longsword > 0){
                cout << "OH NO! Your +3 Longsword broke!" << endl;
                longsword--;
                break;
                }
            case 4: 
                if(axes > 0){
                cout << "OH NO! Your +2 Axe broke!" << endl;
                axes--;
                break;
                }
            default:
                if(armor > 0){
                    armor--;
                    cout << "You lost 1 armor" << endl;
                }
                break;
            }
            break;
        case 4: case 5: case 6: // 30% hunger is lost
            second = rand() % (party.size()-1);
            party.at(second).lose_fullness(10);
            cout << party.at(second).getplayername() << " lost 10 hunger." << endl;
            if(party.at(second).getfullness() == 0){
                cout << party.at(second).getplayername() << " has died! continue on without them." << endl;
                party.erase(party.begin() + second);
            }
            break;
        default: //else
            if(door == true){   //if attempting to open door remaining 30%
                second = rand() % (party.size()-2);
                cout << "OH NO! Your teammate " <<  party.at(second).getplayername() << " is trapped in the previous room and is unable to get through. You must continue without them." << endl;
                party.erase(party.begin() + second + 1);
                cout << "Your party size has reduced to "<< party.size() <<  " members." << endl; 
            }
            break;
    }   
}