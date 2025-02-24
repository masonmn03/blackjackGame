#include "Games.h"

int rollDie() {
    int die1, die2, sum;
    die1 = rand() % 6 + 1;
    die2 = rand() % 6 + 1;

    sum = die1 + die2;

    cout << die1 << " + " << die2 << " = " << sum << endl;
    return sum;
}

void playCraps() {
    int sum, point;
    sum = rollDie();
        if (sum == 7 || sum == 11)
        // || short circuit -> if the left is T doesn't evaluate right in OR
        // | evaluates both sides and chooses T or F
            cout << "You win!\n";
        
        else if (sum == 2 || sum == 3 || sum == 12) {
            cout << "You lose!\n";
        }
        else {
            point = sum;
            sum = rollDie();
            while (sum != point && sum !=7) {
                sum = rollDie();
            }
            if (sum == point || sum == 7) {
                cout << "You win!\n";
            }
            else {
                cout << "Oops - better luck next time!\n";
            }
        }
}
void scraps() {}

void hangman() {
    cout << "\n-- Hangman --\n\n";
    // open file
    ifstream inFile;
    inFile.open("words.txt");
    if (!inFile.good()) {
        cout << "error in input file\n";
        return;
    }
    
    string word, guessWord, realWord;
    vector<string> words;
    while (getline(inFile, word)) {
        words.push_back(word);
    }
    
    //choose random word
    int wordPos = rand() % words.size();
    
    realWord = words[wordPos];
    cout << realWord << endl;
    
    //setup guess word
    guessWord = "";
    for (int i = 0; i < realWord.size(); i++) {
        guessWord += "_";
    }
    for (int i = 0; i < guessWord.size(); i++) {
        cout << i << " ";
    }
    
    cout << endl;
    
    inFile.close();
}

void outputHand(vector<card> hand, int numCards, string player, int sum) {
    cout << player << " has the following cards:" << endl;
    for (int j = 0; j < numCards; j++) {
        char suitChr; // Spade, clover, diamond, heart
        if (hand.at(j).suit == 1) {
            suitChr = 'S';
        }
        else if (hand.at(j).suit == 2) {
            suitChr = 'C';
        }
        else if (hand.at(j).suit == 3) {
            suitChr = 'D';
        }
        else {
            suitChr = 'H';
        }

        cout << suitChr << " " << hand.at(j).face << endl;
    }
    cout << setw(15) << right << "Total: " << sum << endl;
}
bool checkBust(int& sum, vector<card>& hand) {
    if (sum > 21) {
        for (int i = 0; i < hand.size(); i++) {
            if (((hand.at(i).face) == 1) && ((hand.at(i).value) == 11)) {
                hand.at(i).value = 1;
                sum -= 10;
                if (sum <= 21) {
                    return false;
                }
            }
        }
        return true;
    }
    else {
        return false;
    }
}
void playBlackJack() {
    char playAgain = 'Y';
    
    while (playAgain == 'Y' || playAgain == 'y') {
        vector<int> suitValues;
        suitValues.push_back(1); // Spade
        suitValues.push_back(2); // Club
        suitValues.push_back(3); // Diamond
        suitValues.push_back(4); // Heart

        vector<int> faceValues;
        // Ace = 1, Jack = 11, Queen = 12, King = 13
        for (int i=1; i < 14; i++) {
            faceValues.push_back(i);
        }
        vector<card> deck;
        for (int s = 0; s < suitValues.size(); s++) {
            for (int f = 0; f < faceValues.size(); f++) {
                card temp;
                temp.suit = suitValues[s];
                temp.face = faceValues[f];
                if (temp.face >= 2 && temp.face <= 9) {
                    temp.value = temp.face;
                }
                else if (temp.face == 1) {
                    temp.value = 11;
                }
                else if ((temp.face == 10) || (temp.face == 11) || (temp.face == 12) || (temp.face == 13)) {
                    temp.value = 10;
                }
                deck.push_back(temp);
            }
        }
        
        // Shuffles the deck. Used ChatGPT to help with the randomization of each game.
        // Prompt was "How do I randomize the deck instead of having them in order?" after showing my code.
        random_device rd;  // Seed generator
        mt19937 g(rd());   // Random number engine (Mersenne Twister)
        shuffle(deck.begin(), deck.end(), g);

        int cardsOut = 0; // Number cards taken out deck
        vector<card> playerHand;
        vector<card> dealerHand;
        int playerSum = 0, dealerSum = 0;

        for (int i = 0; i < 4; i++) {  // Initializes dealer and player hands with 2 cards each alternating between each one.
            card temp;
            temp = deck.at(i);
            int tempVal = temp.value;
            if (i % 2 == 0) {
                playerHand.push_back(temp);
                playerSum += tempVal;
            }
            else {
                dealerHand.push_back(temp);
                dealerSum += tempVal;
            }
            cardsOut += 1;
        }

        outputHand(playerHand, playerHand.size(), "Player", playerSum);
        char input;

        cout << "Would you like to take another card? (Y/N)" << endl;
        cin >> input;

        while (input == 'Y') {
            card temp;
            temp = deck.at(cardsOut);
            playerHand.push_back(temp);
            cardsOut += 1;
            playerSum += temp.value;

            if (checkBust(playerSum, playerHand)) {
                if (playerSum > 21) {  // Double-check if still busting after Ace adjustment
                    outputHand(playerHand, playerHand.size(), "Player", playerSum);
                    cout << setw(15) << right << "OOPS - Player went over 21. Computer wins." << endl;
                    break;
                }
            }
            outputHand(playerHand, playerHand.size(), "Player", playerSum);

            cout << "Would you like to take another card? (Y/N)" << endl;
            cin >> input;
            cout << endl;
        }
        if (playerSum <= 21) {
            cout << "\nDealer's Turn:\n";
            outputHand(dealerHand, dealerHand.size(), "Dealer", dealerSum);

            while (dealerSum <= 17) {  // Dealer must hit if sum is <= 17
                card temp = deck.at(cardsOut++);
                dealerHand.push_back(temp);
                dealerSum += temp.value;

                if (checkBust(dealerSum, dealerHand)) {
                    outputHand(dealerHand, dealerHand.size(), "Dealer", dealerSum); // Show updated sum
                        break;
                    
                }
                outputHand(dealerHand, dealerHand.size(), "Dealer", dealerSum);
            }
            if (dealerSum > 21) {
                cout << setw(15) << right << "Dealer went over 21. Player wins!" << endl;
            }
            else if (dealerSum > playerSum) {
                cout << "Dealer Wins!";
            }
            else if (playerSum > dealerSum) {
                cout << "Player wins!";
            }
            else if (playerSum == dealerSum) {
                cout << "Tied Match!";
            }
        }
    // Ask if they want to play again
        cout << "\nWould you like to play again? (Y/N): ";
        cin >> playAgain;
        cout << endl;
    }
    cout << "Thanks for playing! Goodbye.";
}
