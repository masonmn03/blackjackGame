#include "Functions.h"



bool isDigits(string str) {
    return str.find_first_not_of("1239") == string:: npos;
}

string menu() {
    string choice = "B";
    return choice;
}
int displayMenu() {
    string inStr;
    int choice;
    cout << "Welcome to My Games Program \n";
    cout << "1. Craps \n";
    cout << "2. Scraps\n";
    cout << "3. Blackjack\n";
    cout << "9. Quit\n";
    cout << "Please enter 1, 2, 3 or 9" << endl;

    getline(cin, inStr);
    if (isDigits(inStr)) {
        choice = stoi(inStr);
    }
    else {
        choice = 9;
    }

    /*int choice;
    cin >> choice;
    */
    while (choice != 1 && choice !=2 && choice != 3 && choice != 9) {
        cout << "Please enter a valid choice" << endl;
        cin >> choice;
    }
    return choice;
}