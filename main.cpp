/* Nicolás Tovar    NRC 3455    00/00/2024
Purpose*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

void shuffleVector(vector<int>& vec);
string getSuit(int card);
int getValue(int card);

// ASCII chars for suits
    char hearts[] = "\x03";
    char diamonds[] = "\x04";
    char clubs[] = "\x05";
    char spades[] = "\x06";


int main() {
    bool running = true;

    // Ordered deck
    vector<int> deck = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
        21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
        39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51
    };

    vector <int> shuffledDeck;
    shuffledDeck = deck;

    shuffleVector(shuffledDeck);

    while (running) {
        for(int k = 0, card; k < deck.size(); k++) {
            card = deck[k];
            cout << card << ": " << getSuit(card) << getValue(card) << endl;  
        }
        cout << endl << endl;

        for(int k = 0, card; k < shuffledDeck.size(); k++) {
            card = shuffledDeck[k];
            cout << card << ": " << getSuit(card) << getValue(card) << endl;  
        }

        running = false;   
    }
    
    return 0;
}

int getValue(int card) {
    return card % 13 + 2;
}

string getSuit(int card) {
    int x = card / 13;
    if (x == 0) return hearts;
    if (x == 1) return diamonds;
    if (x == 2) return clubs;
    return spades;

}


void shuffleVector(vector<int>& vec) {
    // Seed for srand
    srand((unsigned) time(0));

    // Fisher-Yates shuffle algorithm
    for (int i = vec.size() - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        swap(vec[i], vec[j]);
    }
}