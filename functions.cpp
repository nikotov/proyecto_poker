#include <iostream>
#include <vector>
#include <iomanip>

#include "functions.h"

using namespace std;

// ASCII chars for suits
    char hearts[] = "\x03";
    char diamonds[] = "\x04";
    char clubs[] = "\x05";
    char spades[] = "\x06";


int getValue(int card) {
    //returns numerical value of a card within a certain suit
    return card % 13 + 1;
}


string getSuit(int card) {
    //0-12: Hearts, 13-25: Diamonds, 26-38: Clubs, 39-51: Spades
    int x = card / 13;
    if (x == 0) return hearts;
    if (x == 1) return diamonds;
    if (x == 2) return clubs;
    return spades;

}


void shuffleVec(vector<int>& vec) {
    // Seed for srand
    srand((unsigned) time(0));

    // Fisher-Yates shuffle algorithm
    for (int i = vec.size() - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        swap(vec[i], vec[j]);
    }
}


void printHand(vector<int>hand){

    for(int i = 0; i < hand.size(); i++){
        cout << i+1 << ".) ";

        //Handles non-numerical cards
        switch(getValue(hand[i])){
            case 1:
                cout << setw(5) << "Ace";
                break;

            case 11: 
                cout << setw(5) << "Jack";
                break;
                                
            case 12:
                cout << setw(5) << "Queen";
                break;
                                
            case 13:
                cout << setw(5) << "King";
                break;
            
            default:
                cout << setw(5) << getValue(hand[i]);                           
        }
        cout << " of " << getSuit(hand[i]) << endl;
    }
}


void dealHand(vector<int>& deck, vector<int>& hand){
    const int handSize = 5;

    //Pass the first value of shuffled deck to hand, removes card from deck
    for(int i = 0; i < handSize; i++){
        hand.push_back(deck[0]);
        deck.erase(deck.begin());
    }
}


void sortHand(vector<int>& hand){

    //Selection Sort algorithm using card value 
    for (int i = 0; i < hand.size() - 1; ++i) {
            int minInd = i;
            for (int j = i + 1; j < hand.size(); ++j) {
                if (getValue(hand[j]) < getValue(hand[minInd])) minInd = j;
            }
            if (minInd != i) {
                swap(hand[i], hand[minInd]);
            }
        }

}


bool nthOfAKind(int n, vector<int>hand){
    int counter;
    int compare;
    for(int i = 0; i < hand.size()+1 - n; i++){
        counter = 1;
        int compare = getValue(hand[i]);
        for(int j = i+1; j < hand.size(); j++){
            if(getValue(hand[j]) == compare) counter++;
        }
        if(counter >= n) break;
    }

    if(counter >= n) return getValue(compare);
    else return false;
}


bool twoPair(vector<int>hand){
    int pairs = 0;
    for(int i = 0; i < hand.size()-1; i++){
        int compare = getValue(hand[i]);
        for(int j = i+1; j < hand.size(); j++){
            if(getValue(hand[j]) == compare) pairs++;
        }
        if(pairs >= 2) break;
    }

    if(pairs >= 2) return true;
    else return false;
}

