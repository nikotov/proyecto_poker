#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <iomanip>
#include "functions.h"

using namespace std;

// ASCII chars for suits
    string hearts = "\x03";
    string diamonds = "\x04";
    string clubs = "\x05";
    string spades = "\x06";


int getValue(int card) {
    //returns numerical value of a card within a certain suit
    return card % 13 + 2;
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


void printHandB(vector<int>hand){

    for(int i = 0; i < hand.size(); i++){
        cout << i+1 << ".) ";

        //Handles non-numerical cards
        switch(getValue(hand[i])){
            case 14:
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


void chooseHand(vector<int>& hand){
    //For testing purposes. Lets you put any 5 cards into a hand
    for(int i = 0; i < 5; i++){
        int temp;
        cout << "Introduce el ID de una carta: ";
        cin >> temp;
        hand.push_back(temp);
    }
}


bool isNthOfAKind(int n, vector<int>hand){
    int counter = 0;
    int compare = 0;
    //Uses a counter to keep track of number of matches for each individual card
    for(int i = 0; i < hand.size()+1 - n; i++){
        counter = 1;
        int compare = getValue(hand[i]);
        for(int j = i+1; j < hand.size(); j++){
            if(getValue(hand[j]) == compare) counter++;
        }
        //If enough matches are found, breaks the loop
        if(counter >= n) break;
    }

    if(counter >= n) return getValue(compare);
    else return false;
}


bool isTwoPair(vector<int>hand){
    //Uses a counter to keep track of pairs found
    int pairs = 0;
    for(int i = 0; i < hand.size()-1; i++){
        int compare = getValue(hand[i]);
        for(int j = i+1; j < hand.size(); j++){
            //When a pair is found, stops loop and removes the second instance to avoid errors with 3 of a kind
            if(getValue(hand[j]) == compare){ 
                pairs++;
                hand[j] = -1;
                break;
            }
        }
        if(pairs >= 2) break;
    }
    if(pairs >= 2) return true;
    else return false;
}


bool isStraight(vector<int>hand){
    bool isStraight = true;
    for(int i = 0; i < hand.size() - 1; i++){
        //Handles Ace being used as a low card     
        if(i == 0){
            if(getValue(hand[hand.size() - 1]) == 14 && getValue(hand[i]) == 2 ) hand[hand.size() - 1] = 4;
        }
        //Turns false if any given pair is not consecutive. Doesnt allow for wrap-arounds (Q, K, A, 2, 3 is not a straight)
        if(getValue(hand[i])+1 != getValue(hand[i+1])){
            isStraight = false;
            break;
        }
    }
    return isStraight;
}


bool isFlush(vector<int>hand){
    bool isFlush = true;
    string compare = getSuit(hand[0]);
    for(int i = 1; i < hand.size(); i++){
        if(getSuit(hand[i]) != compare){
            isFlush = false;
            break;
        }
    }

    return isFlush;
}


bool isFullHouse(vector<int>hand){
    bool isFullHouse = true;
    //Determines if there is any repeat value in the sorted hand
    int repeat = -1;
    for (int k = 0; k < hand.size(); k++) {
        hand[k] = getValue(hand[k]);
    }

    for (int i = 0; i < hand.size(); ++i) {
        if (getValue(hand[i]) == getValue(hand[i+1])) repeat = hand[i];
    }

    if(repeat != -1){
        //If there is a repeat, removes all instances of the repeat
        hand.erase(remove(hand.begin(), hand.end(), repeat), hand.end());

        if(hand.size() > 1){
            //If all remaining cards are equal, returns true
            for(int i = 0; i < hand.size()-1; i++){
                if(getValue(hand[i]) != getValue(hand[i+1])) isFullHouse = false;
            }
        } 
        else isFullHouse = false;
    }
    else isFullHouse = false;

    return isFullHouse;

}


bool isStraightFlush(vector<int>hand){
    if(isStraight(hand) && isFlush(hand)) return true;
    else return false;
}


bool isRoyalFlush(vector<int>hand){
    if(isStraightFlush(hand) && getValue(hand.back()) == 14 && getValue(hand[0]) == 10)
    return true;
    else return false;
}


int valueHand(vector<int>hand){
    if(isRoyalFlush(hand)) return 0;
    else if(isStraightFlush(hand)) return 1;
    else if(isNthOfAKind(4, hand)) return 2;
    else if(isFullHouse(hand)) return 3;
    else if(isFlush(hand)) return 4;
    else if(isStraight(hand)) return 5;
    else if(isNthOfAKind(3, hand)) return 6;
    else if(isTwoPair(hand)) return 7;
    else if(isNthOfAKind(2, hand)) return 8;
    else return 9;

}


void discardHand(vector<int>& deck, vector<int>& hand){
    cout <<"Cuales cartas del quieres descartar (0 para confirmar tu eleccion): ";
    
    //Sets the value of cards to be discarded to -1
    for(int i = 0; i < hand.size();){
        int discard;
        cin >> discard;
        if(discard == 0) break;

        else if(discard < 0 || discard > hand.size())
            cout << "Ingresa un numero valido. Intenta otra vez" << endl;
        
        else if(hand[discard-1] == -1)
            cout << "Ya escogiste esta carta. Intenta otra vez" << endl;
        
        else{
            hand[discard-1] = -1;
            i++;
        }
    }

    //Replaces all -1 values with new cards
    for(int i = 0; i < hand.size(); i++){
        if(hand[i] == -1){
            hand[i] = deck[0];
            deck.erase(deck.begin());
        }
    }

    sortHand(hand);
}

