#include <bits/stdc++.h>

using namespace std;

char player;
char board[17][13];
int numMoves;
int moves[200][4];

int main() {
    cout << "Content-type:text/html" << endl << endl;
    // -----------------------------------------------------------------
    // Read in the data
    // -----------------------------------------------------------------
    string word;
    cin >> word; // PLAYER
    cin >> player;
    cin >> word; // BOARD
    for (int i = 0; i < 17; i ++) {
        for (int j = 0; j < 13; j ++) {
            cin >> board[i][j];
        }
    }
    cin >> word; // MOVES
    cin >> numMoves;
    for (int i = 0; i < numMoves; i ++) {
        cin >> moves[i][0] >> moves[i][1] >> moves[i][2] >> moves[i][3];
    }
    // -----------------------------------------------------------------
    // Do the processing
    // -----------------------------------------------------------------
    
    // seed the random generator
    srand(time(NULL));
    
    cout << (rand() % numMoves) << endl;
}