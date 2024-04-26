#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "functions.h"

using namespace std;

int main() {

    // Ordered deck
    vector<int> deck = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
        13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
        26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
        39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51
    };

    vector<int> playDeck;
    vector<int> player;
    vector<int> computer;

    shuffleVec(deck);

    dealHand(deck, player);
    cout << "Player Deck: " << endl;
    printHandB(player);

    sortHand(player);

    cout << "\nSorted Player Deck: " << endl;
    printHandB(player);

    cout << endl << "Deck Value: ";
    cout << valueHand(player);

    cout << endl << endl;
    discardHand(deck, player);

    cout << "\nDiscard Player Deck: " << endl;
    printHandB(player);

    cout << endl << "Deck Value: ";
    cout << valueHand(player);

    return 0;
}

