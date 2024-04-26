#include <vector>
#include <string>
using namespace std;

void shuffleVec(vector<int>& vec);

string getSuit(int card);

int getValue(int card);

void printHand(vector<int>hand);

void dealHand(vector<int>& deck, vector<int>& hand);

void sortHand(std::vector<int>& hand); 

bool nthOfAKind(int n, vector<int>hand);

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

void discardHand(vector<int>& deck, vector<int>& hand);