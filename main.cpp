#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <fstream>
#include "functions.h"
#include "print_game.h"

using namespace std;

int main() {

int menu;
do{

   menu = printMenu();

   if(menu == 1){

        ofstream outLog{"log.txt", ios::app};

        if (!outLog){
            cerr << "Log file could not be opened" << endl;
            exit(EXIT_FAILURE);
        }

        // Ordered deck
        vector<int> deck = {
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
            13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
            26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
            39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51
        };
        vector<int> player;
        vector<int> computer;

        shuffleVec(deck);
        outLog << "New Game: " << endl << endl;

        dealHand(deck, computer);
        sortHand(computer);
        outLog << "Computer Hand: " << endl;
        logHand(outLog, computer);
        outLog << endl;

        dealHand(deck, player);
        sortHand(player);
        outLog << "Player Hand: " << endl;
        logHand(outLog, player);
        outLog << endl;        

        cout << "Player Hand: " << endl;
        printHand(player);

        cout << "Do you want to discard any card? [y/n]: ";
        string choice;
        cin >> choice;
        if(choice == "y"){
            discardHand(deck, player);
            outLog << "Discard Player Hand: " << endl;
            logHand(outLog, player);
            outLog << endl; 

            cout << "New Player Hand: ";
            printHand(player);
        }

        cout << endl << "Deck Value: ";
        cout << valueHand(player) << endl;

        outLog << "Player Wins" << endl << endl;
        cout << "Congratulations! You won! Returning to main menu...";
        outLog.close();
   }

} while(menu != 3);

return 0;

}

