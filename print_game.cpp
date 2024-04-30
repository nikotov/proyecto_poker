#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>

#include "functions.h"
#include "print_game.h"

// Prints main menu and returns player input
int printMenu() {
    int x;
    const string menu = R"(
 _____
|A .  | _____
| /.\ ||A ^  | _____
|(_._)|| / \ ||A _  | _____
|  |  || \ / || ( ) ||A_ _ |
|____V||  .  ||(_'_)||( v )|
       |____V||  |  || \ / |
              |____V||  .  |
                     |____V|
~~~~~~~~~~~~~~~~~~~~~~~~~~
        Poker Night
~~~~~~~~~~~~~~~~~~~~~~~~~~
1. Jugar 5 rondas
2. Jugar 1 ronda
3. Salir
~~~~~~~~~~~~~~~~~~~~~~~~~~
Ingrese un numero: )";
    cout << menu;
    cin >> x;
    return x;
}


// Prints a hand in ascii art
void printHand(vector<int>& hand) {
    vector<string> values;
    vector<string> suits;

    // Loops trough, and adds to values an string with " " and value of card
    for(int i = 0, value = 0; i < hand.size(); i++) {
        value = getValue(hand[i]);
        if (value < 10) {
            values.push_back(" " + to_string(value));
        }
        else if (value == 10) values.push_back("10");
        else if (value == 11) values.push_back(" J");
        else if (value == 12) values.push_back(" Q");
        else if (value == 13) values.push_back(" K");
        else if (value == 14) values.push_back(" A");
    }

    // Gets suits of cards and adds strings to vector
    for(auto x : hand) {
        string suit;
        suit = getSuit(x);
        suits.push_back((suit));
    }


    // Top of ascii art
    string handTop = R"(
 _____  _____  _____  _____  _____  
|     ||     ||     ||     ||     | 
)";
    
    // Bottom of ascii art
    string handBot = R"(
|_____||_____||_____||_____||_____|
   1      2      3      4      5
)";
    // Couts top, values row, suits row and bottom of cards
    cout << handTop;
    cout << "| " << values[0] << "  || " << values[1] << "  || " << values[2] << "  || " << values[3] << "  || " << values[4] << "  |" << endl;
    cout << "|  " << suits[0] << "  ||  " << suits[1] << "  ||  " << suits[2] << "  ||  " << suits[3] << "  ||  " << suits[4] << "  |";
    cout << handBot;
}


// Couts ansii code that clears the console
void clearConsole () {
    cout << "\033[2J";
}
