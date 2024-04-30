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
    vector<int> playDeck;
    vector<int> playerHand;
    vector<int> botHand;

    // Seed for srand
    srand((unsigned) time(0));

    bool running = true;
    int option;

    

    while(running) {
        clearConsole();
        option = printMenu();
        switch (option){
        case 1:
            {
                ofstream outLog{"log.txt", ios::app};

                if (!outLog){
                    cerr << "Log file could not be opened" << endl;
                    exit(EXIT_FAILURE);
                }

                outLog << "Nueva partida de 5" << endl;

                for (int i = 0; i < 5; i++) {
                    clearConsole();
                    outLog << "Ronda " << i+1 << endl;
                    cout << "Ronda " << i+1 << endl;
                    
                    playRound(playDeck, playerHand, botHand, outLog);
                }
                outLog.close();
                break;
            }
        case 2:
            {
                ofstream outLog{"log.txt", ios::app};

                if (!outLog){
                    cerr << "Log file could not be opened" << endl;
                    exit(EXIT_FAILURE);
                }

                outLog << "Nueva partida de 1" << endl;
                
                clearConsole();
                playRound(playDeck, playerHand, botHand, outLog);
                outLog.close();
                break;
            }
        
        case 3:
            running = false;
        default:
           clearConsole();
        }

        
    }


    return 0;

}