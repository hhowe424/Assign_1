//1-10-2022
/*
This program is a matching game that asks the player
to enter x and y coordinates relating to two positions
on a board of hidden numbers. If the numbers match they
will stay on the board, however if they are different the
cards will flip over again. The player wins when all 8 pairs
are matched.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
int const LENGTH = 4;
using namespace std;

void InitializeCards(int cards[][LENGTH]);
void ShowCards(int [][LENGTH], bool [][LENGTH]);
void GuessCards(int [][LENGTH], bool [][LENGTH], int&, int&);

int main (){
    ofstream outputFile;
    outputFile.open("game-results.txt");

    string begin;
    string name;
    int quit = 0;
    int turns = 0;
    int cards[LENGTH][LENGTH] = {0};
    bool faceUp[LENGTH][LENGTH] = {false};

    cout << "Welcome to my card matching game.\n"
            "Please enter your full name: ";
    getline(cin, name);
    outputFile << "Player's name: " << name << endl;

    cout << "Hi " << name << "!" << endl;
    cout << "To complete the game you must find all "
            "the matching pairs on the board." << endl;
    cout << "To begin enter 'start'...";
    cin >> begin;

    if (begin == "start") {
        int match = 0;
        InitializeCards(cards);
        while(match < 8 && quit != 1) {
            turns++;
            ShowCards(cards, faceUp);
            GuessCards(cards, faceUp, match, quit);
        }
        if(match == 8) {
            ShowCards(cards, faceUp);
            cout << "Congratulations!\nYou have found each match!\n"
                    "Thanks for playing! Bye now!" << endl;
            outputFile << "It took " << name << " " << turns
                       << " turns to complete the game.";
        }
        else {
            cout << "Thanks for playing. Bye! Bye!" << endl;
            outputFile << name << " took " << turns << " turn(s).\n";
            outputFile << "Don't give up!" << endl;
        }
        outputFile.close();
    }

    return 0;
}

// This function receives an array representing the numbers
// on the board, a bool array, and a match and quit variable
// to display the player's guessed numbers. It then determines
// if the numbers guessed match and if the player wants to quit.
void GuessCards(int cards[][LENGTH], bool faceUp[][LENGTH],
                int &match, int &quit){
    int x1, y1, x2, y2;
    char decision;

    do {
        cout << "Enter the row and column of the first card: ";
        cin >> x1 >> y1;
    } while (x1 >= 4 || x1 < 0 || y1 >= 4 || y1 < 0);

    do {
        cout << "Enter the row and column of the second card: ";
        cin >> x2 >> y2;
    } while (x2 >= 4 || x2 < 0 || y2 >= 4 || y2 < 0);

    cout << "    0 1 2 3\n    =======\n";

    //Displaying the cards the player guessed
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 7; col++) {
            if (col == 0) {
                cout << row << " ";
            }
            if (col == 1 || col == 6) {
                cout << "| ";
            }
            if (col <= 5 && col >= 2) {
                if(faceUp[row][col - 2] == 1) {
                    cout << cards[row][col - 2] << " ";
                }
                if(faceUp[row][col - 2] == 0) {
                    if (row == x1 && col == (y1 + 2)) {
                        cout << cards[x1][y1] << " ";
                    }
                    else if (row == x2 && col == (y2 + 2)) {
                        cout << cards[x2][y2] << " ";
                    }
                    else {
                        cout << "* ";
                    }
                }
            }
        }
        cout << endl;
    }
    cout << "    =======\n";

    if (cards[x1][y1] == cards[x2][y2]) {
        cout << "Match found!" << endl;
        cout << "Enter 'q' to quit, or enter any key to continue... ";
        cin >> decision;
        if(decision == 'q'){
            quit = 1;
        }
        faceUp[x1][y1] = true;
        faceUp[x2][y2] = true;
        match++;
    }
    else if(cards[x1][y1] != cards[x2][y2]) {
        cout << "Match not found :(" << endl;
        cout << "Flipping cards over again.\n";
        cout << "Enter 'q' to quit, or enter any key to continue... ";
        cin >> decision;
        if(decision == 'q'){
            quit = 1;
        }
    }
}

// This function receives an array representing the numbers
// on the board and a bool array to display the correctly
// guessed and hidden cards on the board.
void ShowCards(int cards[][LENGTH], bool faceUp[][LENGTH]) {
    cout << "    0 1 2 3\n    =======\n";

    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 7; col++){
            if(col == 0){
                cout << row << " ";
            }
            if(col == 1 || col == 6){
                cout << "| ";
            }
            if(col <= 5 && col >= 2) {
                if(faceUp[row][col - 2] == 1) {
                    cout << cards[row][col - 2] << " ";
                }
                else{
                    cout << "* ";
                }
            }
        }
        cout << endl;
    }
    cout << "    =======\n";
}

//This function receives an array representing the numbers on the board
//and shuffles them, creating an array of randomly placed pairs of numbers
void InitializeCards(int cards[][LENGTH]) {
    srand(time(NULL));
    int x1, y1, x2, y2;
    int temp;
// Placing pairs in known locations
    cards[0][0] = 1; cards[0][1] = 1;
    cards[0][2] = 2; cards[0][3] = 2;
    cards[1][0] = 3; cards[1][1] = 3;
    cards[1][2] = 4; cards[1][3] = 4;
    cards[2][0] = 5; cards[2][1] = 5;
    cards[2][2] = 6; cards[2][3] = 6;
    cards[3][0] = 7; cards[3][1] = 7;
    cards[3][2] = 8; cards[3][3] = 8;
//Shuffling the board so that the pairs aren't right next to each other
    for (int i = 0; i < 30; i++) {
        y1 = rand() % LENGTH;
        x1 = rand() % LENGTH;
        y2 = rand() % LENGTH;
        x2 = rand() % LENGTH;

        temp = cards[x1][y1];
        cards[x1][y1] = cards[x2][y2];
        cards[x2][y2] = temp;
    }
}

/*
Welcome to my card matching game.
Please enter your full name: John Smith
Hi John Smith!
To complete the game you must find all the matching pairs on the board.
To begin enter 'start'...start
    0 1 2 3
    =======
0 | * * * * |
1 | * * * * |
2 | * * * * |
3 | * * * * |
    =======
Enter the row and column of the first card: 1 1
Enter the row and column of the second card: 0 0
    0 1 2 3
    =======
0 | 1 * * * |
1 | * 4 * * |
2 | * * * * |
3 | * * * * |
    =======
Match not found :(
Flipping cards over again.
Enter 'q' to quit, or enter any key to continue... n
    0 1 2 3
    =======
0 | * * * * |
1 | * * * * |
2 | * * * * |
3 | * * * * |
    =======
Enter the row and column of the first card: 2 9
Enter the row and column of the first card: 9 0
Enter the row and column of the first card: 3 3
Enter the row and column of the second card: 2 2
    0 1 2 3
    =======
0 | * * * * |
1 | * * * * |
2 | * * 8 * |
3 | * * * 3 |
    =======
Match not found :(
Flipping cards over again.
Enter 'q' to quit, or enter any key to continue... n
    0 1 2 3
    =======
0 | * * * * |
1 | * * * * |
2 | * * * * |
3 | * * * * |
    =======
Enter the row and column of the first card: 3 3
Enter the row and column of the second card: 1 0
    0 1 2 3
    =======
0 | * * * * |
1 | 3 * * * |
2 | * * * * |
3 | * * * 3 |
    =======
Match found!
Enter 'q' to quit, or enter any key to continue... n
    0 1 2 3
    =======
0 | * * * * |
1 | 3 * * * |
2 | * * * * |
3 | * * * 3 |
    =======
Enter the row and column of the first card: 2 1
Enter the row and column of the second card: 1 2
    0 1 2 3
    =======
0 | * * * * |
1 | 3 * 6 * |
2 | * 8 * * |
3 | * * * 3 |
    =======
Match not found :(
Flipping cards over again.
Enter 'q' to quit, or enter any key to continue... n
    0 1 2 3
    =======
0 | * * * * |
1 | 3 * * * |
2 | * * * * |
3 | * * * 3 |
    =======
Enter the row and column of the first card: 2 2
Enter the row and column of the second card: 2 1
    0 1 2 3
    =======
0 | * * * * |
1 | 3 * * * |
2 | * 8 8 * |
3 | * * * 3 |
    =======
Match found!
Enter 'q' to quit, or enter any key to continue... n
    0 1 2 3
    =======
0 | * * * * |
1 | 3 * * * |
2 | * 8 8 * |
3 | * * * 3 |
    =======
Enter the row and column of the first card: 0 3
Enter the row and column of the second card: 1 1
    0 1 2 3
    =======
0 | * * * 4 |
1 | 3 4 * * |
2 | * 8 8 * |
3 | * * * 3 |
    =======
Match found!
Enter 'q' to quit, or enter any key to continue... q
Thanks for playing. Bye! Bye!

Process finished with exit code 0
 */