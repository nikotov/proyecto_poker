#include <vector>

void shuffleVec(vector<int>& vec);
string getSuit(int card);
int getValue(int card);
void printHand(vector<int>hand);
void dealHand(vector<int>& deck, vector<int>& hand);
void sortHand(std::vector<int>& hand); 
bool nthOfAKind(int n, vector<int>hand);