#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

void shuffleVec(vector<int>& vec);

string getSuit(int card);

int getValue(int card);

void printHand(vector<int>hand);

void dealHand(vector<int>& deck, vector<int>& hand);

void sortHand(vector<int>& hand); 

void chooseHand(vector<int>& hand);

bool isNthOfAKind(int n, vector<int>hand);

bool isTwoPair(vector<int>hand);

bool isStraight(vector<int>hand);

bool isFlush(vector<int>hand);

bool isFullHouse(vector<int>hand);

bool isStraightFlush(vector<int>hand);

bool isRoyalFlush(vector<int>hand);

int valueHand(vector<int>hand);

int main() {

    // Ordered deck
    vector<int> deck = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
        21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
        39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51
    };

    vector<int> player;
    vector<int> computer;
    
    shuffleVec(deck);

    dealHand(deck, player);
    cout << "Player Deck: " << endl;
    printHand(player);

    sortHand(player);

    cout << "\nSorted Player Deck: " << endl;
    printHand(player);

    cout << endl << "Deck Value: ";
    cout << valueHand(player);

    return 0;
}

