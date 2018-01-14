#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <utility>
#include <map>


using namespace std;

#define DEBUG false
#define ROW 17
#define COL 13
#define NONPLAYING '.'

char player;
char original[ROW][COL];
char board[ROW][COL];
int numMoves;
vector<vector<int>> moves;

vector<vector<int>> dists;

bool isInsideBoard ( int row, int col ) {
	return row >= 0 && row < ROW && col >= 0 && col < COL && board[row][col] != NONPLAYING;
}

vector<pair<int,int>> adjacent ( int row, int col ) {
	vector<vector<pair<int,int>>> adjacencies = {
		{
			{ row - 1, col - 1 },
			{ row - 1, col},
			{ row, col + 1},
			{ row + 1, col},
			{ row + 1, col - 1 },
			{ row, col - 1}
		},
	 	{
			{ row - 1, col },
			{ row - 1, col + 1 },
			{ row, col + 1},
			{ row + 1, col + 1},
			{ row + 1, col },
			{ row, col - 1 }
		}	
	};
	
	vector<pair<int,int>> adj;
	
	for ( auto m : adjacencies[ row % 2 ] ) {
		if ( isInsideBoard ( m.first, m.second ) ) {
			adj.push_back(m);
		}
	}

 	return adj;
	
}

void init_dists ( int row, int col ) {
	
	dists = vector<vector<int>> ( ROW, vector<int>( COL, -1 ) );
	vector<pair<int, int>> bfs = { { row, col } };
	
	int dist = 0;
	while ( bfs.size() ) {
		vector<pair<int,int>> bfs2;
		
		for ( auto m : bfs ) {
			if ( dists[m.first][m.second] > -1 ) continue;
			
			dists[m.first][m.second] = dist;
			
			auto next = adjacent( m.first, m.second );
			if ( DEBUG ) cout << "adj to : " << m.first << ' ' << m.second << ": ";
			if (DEBUG ) for ( auto u : next ) cout << '\t' << u.first << ' ' <<u.second << endl;
			bfs2.insert( bfs2.end(), next.begin(), next.end() );
			
		}
		
		++dist;
		bfs = bfs2;
	}
	
	if ( DEBUG ) {
		for ( int i = 0 ; i < dists.size(); ++i ) for ( int j = 0; j < dists.size(); ++j ) cout << i << ' ' << j << ' ' << dists[i][j] << endl;
	}	
	
}


// where is each color trying to move to?
map<char, pair<int,int>> goals = {
	{ 'R', {  16, 6 } },
	{ 'P', {  12, 0 } },
	{ 'B', {  4, 0 } },
	{ 'Y', {  0, 6 } },
	{ 'G', {  4, 12 } }
	{ 'W', {  12, 12 } },
};

int main() {
    cout << "Content-type:text/html" << endl << endl;
    // -----------------------------------------------------------------
    // Read in the data
    // -----------------------------------------------------------------
    string word;
    cin >> word; // PLAYER
    cin >> player;
    cin >> word; // ORIGINAL
    for (int i = 0; i < ROW; i ++) {
        for (int j = 0; j < COL; j ++) {
            cin >> original[i][j];
        }
    }
    cin >> word; // BOARD
    for (int i = 0; i < ROW; i ++) {
        for (int j = 0; j < COL; j ++) {
            cin >> board[i][j];
        }
    }
    cin >> word; // MOVES
    cin >> numMoves;
    moves = vector<vector<int>> ( numMoves, vector<int>( 4 ) );
    for (int i = 0; i < numMoves; i ++) {
    	
        cin >> moves[i][0] >> moves[i][1] >> moves[i][2] >> moves[i][3];
    }
    // -----------------------------------------------------------------
    // Do the processing
    // -----------------------------------------------------------------
    
    
    init_dists ( goals[player].first, goals[player].second );
    
    
    
    // for each of the moves, calculate the resulting change in distance from the goal post. 
    
    int largest_improvement = -1000000;
    vector<int> move_nums;
    int cur_move = 0;
    for ( auto m : moves ) {
    	int improvement = dists[m[0]][m[1]] - dists[m[2]][m[3]];
    	if ( improvement == largest_improvement ) {
    		move_nums.push_back( cur_move );
    	} else
    	if ( improvement > largest_improvement ) {
    		largest_improvement = improvement;
    		move_nums = { cur_move };
    	}
    	++cur_move;
    }
    
    // seed the random generator
    srand(time(NULL));
	cout << move_nums[rand() % move_nums.size()] << endl;
}