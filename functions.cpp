#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <iomanip>
#include "functions.h"
#include "print_game.h"
#include <fstream>

using namespace std;

// ASCII chars for suits
    string hearts = "\x03";
    string diamonds = "\x04";
    string clubs = "\x05";
    string spades = "\x06";

// Ordered deck
    vector<int> newDeck = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
        13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
        26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
        39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51
    };

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


void shuffleDeck(vector<int>& vec) {
    
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
    for(int i = 0 + hand.size(); i < handSize; i++){
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
    //Compares the suit of the first card to all others. If there is a difference, returns false
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
    //Straight Flush where first card is a 10 and last is an Ace
    if(isStraightFlush(hand) && getValue(hand.back()) == 14 && getValue(hand[0]) == 10)
    return true;
    else return false;
}


vector<int> valueHand(vector<int> hand){
    vector<int> returnVector; // Vector to return values
    int end = hand[hand.size() - 1]; // Last card in hand

    if(isRoyalFlush(hand)) {
        returnVector.push_back(0); // Values 0 if Royal Flush
        return(returnVector);
    }

    else if(isStraightFlush(hand)) {
        returnVector.push_back(1);  // Values 1 if Straight Flush
        returnVector.push_back(end); // Also returns highest card
        return(returnVector);
    }

    else if(isNthOfAKind(4, hand)) {
        returnVector.push_back(2); // Values 2 if Poker
        returnVector.push_back(hand[2]); // Returns poker card value
        // Finds extra card and returns it as 2nd index
        if (getValue(hand[2]) == getValue(end)) returnVector.push_back(hand[0]);
        else returnVector.push_back(end);
        return(returnVector);
    }

    else if(isFullHouse(hand)) {
        returnVector.push_back(3); // Values 3 if Full House
        // Checks value of three of a kind, value of pair and returns it as 1st and 2nd index
        if (getValue(hand[2]) == end) {
            returnVector.push_back(end);
            returnVector.push_back(hand[0]);
        }
        else {            
            returnVector.push_back(hand[0]);
            returnVector.push_back(end);
        }
        return(returnVector);
    }

    else if(isFlush(hand)) {
        returnVector.push_back(4); // Values 4 if Flush
        // Returns hand cards in descending order
        for(int i = hand.size() - 1; i >= 0; i--) {
            returnVector.push_back(hand[i]);
        }
        return(returnVector);
    }

    else if(isStraight(hand)) { 
        returnVector.push_back(5); // Values 5 if Straight
        returnVector.push_back(end); // Returns highest card of hand
    }

    else if(isNthOfAKind(3, hand)) {
        returnVector.push_back(6); // Values 6 if three of a kind
        // Finds value of three of a kind, returns it and extra cards in descending order
        if (getValue(hand[2]) == getValue(end)) {
            returnVector.push_back(hand[2]);
            returnVector.push_back(hand[1]);
            returnVector.push_back(hand[0]);
        }
        else if (getValue(hand[2]) == getValue(hand[0])) {
            returnVector.push_back(hand[2]);
            returnVector.push_back(end);
            returnVector.push_back(hand[3]);
        }
        else {
            returnVector.push_back(hand[2]);
            returnVector.push_back(end);
            returnVector.push_back(hand[0]);
        }
        return(returnVector);
    }

    else if(isTwoPair(hand)) {
        returnVector.push_back(7); // Values 7 if two pair
        // Checks for lone card, returns highest pair, lower pair, and lone card
        if(getValue(hand[0]) != getValue(hand[1])) {
            returnVector.push_back(end);
            returnVector.push_back(hand[2]);
            returnVector.push_back(hand[0]);
        }
        else if(getValue(end) != getValue(hand[4])) {
            returnVector.push_back(hand[2]);
            returnVector.push_back(hand[0]);
            returnVector.push_back(end);
        }
        else {
            returnVector.push_back(end);
            returnVector.push_back(hand[0]);
            returnVector.push_back(hand[2]);
        }
        return(returnVector);
    }

    else if(isNthOfAKind(2, hand)) {
        returnVector.push_back(8); // Values 8 if pair
        vector<int> buffer = hand; // Copies hand
        // Searchs for pair, sets its value to -1
        for(int i = 0; i < buffer.size() - 1; i++) {
            if(getValue(buffer[i]) == getValue(buffer[i+1])) {
                returnVector.push_back(buffer[i]);
                buffer[i] = -1;
                buffer[i + 1] = -1;
            }            
        }
        sortHand(buffer); // Sorts buffer, pair ends at indexes 0 and 1
        // Returns lone cards in desending order
        returnVector.push_back(buffer[4]);
        returnVector.push_back(buffer[3]);
        returnVector.push_back(buffer[2]);
        return(returnVector);
    }

    else {
        returnVector.push_back(9); // Values 9 if High Card
        // Returns cards in desending order
        for(int i = hand.size() - 1; i >= 0; i--) {
            returnVector.push_back(hand[i]);
        }
        return(returnVector);
    }
    return(returnVector);

}


void discardHand(vector<int>& deck, vector<int>& hand){
    cout <<"Cuales cartas del quieres descartar (0 para confirmar tu eleccion): ";
    
    //Creates a vector to store the indexes of cards that will be discarded
    vector<int> discards;
    vector<int> newHand;
    for(int i = 0; i < hand.size() + 1;){
        int temp;
        cin >> temp;
        if(temp == 0) break;
        //Prevents the same card from being discarded twice
        if(find(discards.begin(), discards.end(), temp) != discards.end()) {
            cout << "Ya escogiste esta carta. Intenta otra vez.";
        }             
        //Prevents an imput outside the range of the hand
        else if(temp < 1 || temp > hand.size()) {
            cout << "Introduce un numero valido. Intenta otra vez.";
        }
        else{
            discards.push_back(temp-1);
            i++;
        }
    }

    if(discards.size() == 0) return;

    sortHand(discards);

    for(int i = 0, j = 0; i < hand.size(); i++){
        if(discards[j] == i) j++;
        else newHand.push_back(hand[i]);
    }
    hand = newHand;
    dealHand(deck, hand);

    sortHand(hand);

}


void logHand(ofstream& outLog, vector<int> hand){
    
    //Copies the recieved hand into the log in text form
    for(int i = 0; i < hand.size(); i++){
        outLog << i+1 << ".) ";

        //Handles non-numerical cards
        switch(getValue(hand[i])){
            case 14:
                outLog << setw(5) << "Ace";
                break;

            case 11: 
                outLog << setw(5) << "Jack";
                break;
                                
            case 12:
                outLog << setw(5) << "Queen";
                break;
                                
            case 13:
                outLog << setw(5) << "King";
                break;
            
            default:
                outLog << setw(5) << getValue(hand[i]);                           
        }
        outLog << " of ";

        switch(hand[i] / 13){
            case 0: 
                outLog << "hearts";
                break;

            case 1:  
                outLog << "diamonds";
                break;

            case 2: 
                outLog <<  "clubs";
                break;

            default:
                outLog << "spades";
        }
        outLog << endl;
        outLog.flush();
    }
}


void playRound(vector<int>& playDeck, vector<int>& playerHand, vector<int>& botHand, ofstream& log) {
    vector<int> evalPlayer;
    vector<int> evalBot;
    vector<int> reset;

    //Empties both players hands, reintroduces all cards back into the deck
    playerHand = reset;
    botHand = reset;
    resetDeck(playDeck);
    
    //Shuffles deck, deals cards, and sorts the hands for future operations
    shuffleDeck(playDeck);
    dealHand(playDeck, botHand);
    dealHand(playDeck, playerHand);
    sortHand(playerHand);
    sortHand(botHand);

    //Registers current hands into the log
    log << "Mano del jugador inicial: " << endl;
    logHand(log, playerHand);
    log << "Mano del bot inicial: " << endl;
    logHand(log, botHand);

    cout << "Tu mano: ";
    printHand(playerHand);

    //Allows both players to discard the cards they need
    discardHand(playDeck, playerHand);
    botAlgorithm(botHand, playDeck);
    clearConsole();
    
    //Registers new hands into the log
    log << "Mano del jugador final: " << endl;
    logHand(log, playerHand);
    log << "Mano del bot final: " << endl;
    logHand(log, botHand);

const string showdown = R"(
~~~~~~~~~~~~~~~~~~~~~~~~~~
         Showdown!
~~~~~~~~~~~~~~~~~~~~~~~~~~
)";

    cout << showdown;
    cout << "Mano del adversario: ";
    printHand(botHand);
    cout << "Tu nueva mano: ";
    printHand(playerHand);

    //Returns a vector for comparing hands
    evalPlayer = valueHand(playerHand);
    evalBot = valueHand(botHand);

    for(int i = 0, f = evalPlayer.size() - 1; i < evalPlayer.size(); i++) {
        if (evalPlayer[i] < evalBot[i] && i == 0) {
            log << "Jugador gana" << endl << endl;
            cout << "Ganaste!";
            break;
        }
        else if (evalPlayer[i] > evalBot[i] && i == 0) {
            log << "Bot gana" << endl << endl;
            cout << "Gano tu adversario";
            break;
        }
        else if (getValue(evalPlayer[i]) == getValue(evalBot[i]) && i == f) {
            log << "Empate" << endl << endl;
            cout << "Empate!";
            break;
        }
        else if (getValue(evalPlayer[i]) > getValue(evalBot[i])) {
            log << "Jugador gana" << endl << endl;
            cout << "Ganaste!";
            break;
        }
        else if (getValue(evalPlayer[i]) < getValue(evalBot[i])){
            log << "Bot gana" << endl << endl;
            cout << "Gano tu adversario...";
            break;
        }  
    }

    int foo;
    cout << endl << "Ingresa cualquier valor para continuar: ";
    cin >> foo;

}

// Sets a deck to its init state
void resetDeck(vector<int>& deck) {
    //Puts all cards back into the deck to play again
    deck = newDeck;
    return;
}


// Handles bot descisions
void botAlgorithm (vector<int>& hand, vector<int>& deck) {
    // Init vectors
    vector<int> value = valueHand(hand);
    vector<int> discard;
    vector<int> newHand;
    
    // Checks whether hand contains a hand better than a three of a kind
    if (value[0] < 6) return;

    // Checks if its not a high card hand
    if (value[0] != 9) {
        int flag = 0;
            for(int i = 0; i < hand.size(); i++) {
                flag = 0;
                // Loops and raises flag if card i is equal to any other one in hand
                for (int j = 0; j < hand.size(); j++) {
                    if (getValue(hand[i]) == getValue(hand[j]) && j != i) flag = 1;
                }
                // If not equal to any other card, add its index
                if(flag == 0) discard.push_back(i); 
        }
          
            sortHand(discard); // Sort discard array

            // Loops through hand and copies cards if not in discard array
            for(int i = 0, j = 0; i < hand.size(); i++){
                if(discard[j] == i) j++;
                else newHand.push_back(hand[i]);
            }

        hand = newHand; // Copies cards to keep into bot hand
        dealHand(deck, hand); // Deals replacement cards
        sortHand(hand);
        return;
    }
    else { // If high card hand
        discard = {0, 1, 2}; // Sets discard to lowest 3 cards

        sortHand(discard);

        // Loops and discards
        for(int i = 0, j = 0; i < hand.size(); i++){
            if(discard[j] == i) j++;
            else newHand.push_back(hand[i]);
        }

        hand = newHand; // Copies kept cards
        dealHand(deck, hand); // Deal replacement
        sortHand(hand);
        return;
    }

    
}

