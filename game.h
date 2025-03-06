#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <random> // For shuffling blackjack deck.
#include <algorithm> // For shuffling blackjack deck.
using namespace std;

struct card {
    int suit; // 1: Clover 2: Clubs 3: Diamond 4: Hearts
    int face; // 1: Ace
    int value;
};

void outputHand(vector<card> hand, int numCards, string player, int sum);
bool checkBust(int sum);
void blackJack();

