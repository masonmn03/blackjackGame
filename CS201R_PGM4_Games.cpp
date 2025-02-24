// CS201R_PGM4_Games.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// NAME: MASON NGUYEN
// DATE: 2/20/25
// PROGRAM: GAMES PROJECT
//

#include "Games.h"
#include "Games.cpp"
#include "Functions.cpp"
#include "Functions.h"

int main() {
    int choice;
        srand(time(0));
        choice = displayMenu();
    
        switch (choice) {
        case 1:
            playCraps();
            break;
        case 2:
            cout << "Call scraps\n";
            break;
        case 3:
            cout << "Welcome to BlackJack!" << endl << endl;
            playBlackJack();
            break;
        case 9:
            cout << "Thanks for using our game\n";
            break;
        default:
            cout << "A valid option was not entered\n";
            break;
        }
}

            
            //roll 2 die
    
            //get sum of 2 dice
            //if sum 7 or 11 win
            //else if sum 2, 3, 12 lose
            //else point i added to sum
            // roll until you get point win or 7 lose
    
    


 
