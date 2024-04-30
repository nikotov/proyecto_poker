#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>

#include "functions.h"
#include "print_game.h"


int printMenu() {
    int x = 4;
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
1. Jugar varias rondas
2. Jugar una ronda
3. Opciones
4. Salir
~~~~~~~~~~~~~~~~~~~~~~~~~~
Ingrese un numero: )";
    cout << menu;
    cin >> x;
    return x;
}


void printHand(vector<int>& hand) {
    vector<string> values;
    vector<string> suits;

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

    for(auto x : hand) {
        string suit;
        suit = getSuit(x);
        suits.push_back((suit));
    }



    string handTop = R"(
 _____  _____  _____  _____  _____  
|     ||     ||     ||     ||     | 
)";
    

    string handBot = R"(
|_____||_____||_____||_____||_____|
   1      2      3      4      5
)";
    cout << handTop;
    cout << "| " << values[0] << "  || " << values[1] << "  || " << values[2] << "  || " << values[3] << "  || " << values[4] << "  |" << endl;
    cout << "|  " << suits[0] << "  ||  " << suits[1] << "  ||  " << suits[2] << "  ||  " << suits[3] << "  ||  " << suits[4] << "  |";
    cout << handBot;
}
