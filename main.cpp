/* Nicolas Tovar y Juan Burgos      NRC: 3455   30/04/2024
Programa de poker de 5 cartas*/

// Init libraries
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <fstream>

// Include functions
#include "functions.h"
#include "print_game.h"


using namespace std;


int main() {
    // Init vectors for game
    vector<int> playDeck;
    vector<int> playerHand;
    vector<int> botHand;

    // Seed for srand
    srand((unsigned) time(0));

    // Variables for running program
    bool running = true;
    int option; 

    
    // Loop for menu
    while(running) {
        clearConsole();
        option = printMenu(); // Get user input

        switch (option){
        case 1: // Player wants to play 5 rounds
            {
                ofstream outLog{"log.txt", ios::app}; // Init log ofstream

                // Exits if error opening log file
                if (!outLog){
                    cerr << "Log file could not be opened" << endl;
                    exit(EXIT_FAILURE);
                }

                outLog << "Nueva partida de 5" << endl;

                // Prints round number, and plays 5 rounds
                for (int i = 0; i < 5; i++) {
                    clearConsole();
                    outLog << "Ronda " << i+1 << endl;
                    cout << "Ronda " << i+1 << endl;
                    
                    playRound(playDeck, playerHand, botHand, outLog);
                }
                outLog.close(); // Close log
                break;
            }
        case 2: // Player wants to play 1 round
            {
                ofstream outLog{"log.txt", ios::app}; // Init log ofstream

                // Exits if error opening log file
                if (!outLog){
                    cerr << "Log file could not be opened" << endl;
                    exit(EXIT_FAILURE);
                }

                outLog << "Nueva partida de 1" << endl;
                
                clearConsole();
                playRound(playDeck, playerHand, botHand, outLog);
                outLog.close(); // Close log
                break;
            }
        
        case 3: // player wants to exit
            running = false;
        default: // Player choose invalid option
           clearConsole();
        }        
    }

    return 0;
}