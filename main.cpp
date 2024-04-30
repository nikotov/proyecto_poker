#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>

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
        
        option = printMenu();
        switch (option){
        case 1:
            for (int i = 0; i < 5; i++) {
                cout << "Ronda " << i+1 << endl;
                playRound(playDeck, playerHand, botHand);
            }
            
            break;
        case 2:
            playRound(playDeck, playerHand, botHand);
            break;
        
        case 4:
            running = false;
        default:
           cout << "\033[2J";
        }

        
    }


    //shuffleVec(deck);

    //dealHand(deck, player);
    /* chooseHand(player);
    cout << "Player Deck: " << endl;
    printHand(player);

    sortHand(player);

    cout << "\nSorted Player Deck: " << endl;
    printHand(player);

    cout << endl << "Deck Value: ";
    cout << valueHand(player);
 */
    return 0;
}

