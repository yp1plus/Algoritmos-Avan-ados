#include <iostream>
#include <stdlib.h>
#include <limits.h>
#include <cstring>
#include <queue>
#include <map>

using namespace std;

struct position {
    int i;
    int j;
};

struct state {
    char board[3][3];
    int num_moves;
    position blank_position;
    int heuristic;
    vector<char> movements;
};

// up, down, left and right
const char MOVE[4][2] = {{-1, 0}, 
                         {0, 1}, 
                         {1, 0}, 
                         {0, -1}};
                    
const char DIRECTION[4] = {'u', 'r', 'd', 'l'};

const char TARGET_BOARD[3][3] = {{'1', '2', '3'}, 
                                 {'4', '5', '6'}, 
                                 {'7', '8', 'x'}};

int limit = 0, next_limit = 0;
map<string, bool> visited;

bool operator<(state const& s1, state const& s2) {
    return s1.heuristic > s2.heuristic;
}

void generateMovements(state current, state next_states[4]) {
    // Current position of x
    int new_position_i = 0;
    int new_position_j = 0;

    // Now we get the new states
    for (int i = 0; i < 4; i++) {
        new_position_i = current.blank_position.i + MOVE[i][0];
        new_position_j = current.blank_position.j + MOVE[i][1];

        if (new_position_i >= 0 && new_position_i < 3 && new_position_j >= 0 && new_position_j < 3) {
            next_states[i] = current;
            next_states[i].num_moves = current.num_moves + 1;
            next_states[i].movements.push_back(DIRECTION[i]);

            swap(next_states[i].board[current.blank_position.i][current.blank_position.j], next_states[i].board[new_position_i][new_position_j]);

            next_states[i].blank_position = {new_position_i, new_position_j};
        } else {
            next_states[i].heuristic = -1;
        }
    }
}

string convertToString(char board[3][3]) {
    string boardString;

    for (int i = 0; i < 9; i++) {
        boardString.push_back(board[i / 3][i % 3]);
    }

    return boardString;
}

int calculateHeuristic(state current) {
    int distance = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int value;

            if (current.board[i][j] == 'x') {
                continue;
            } else {
                value = current.board[i][j] - 48;
            }

            int real_i = (value - 1) / 3;
            int real_j = (value - 1) % 3;

            distance += abs(i - real_i) + abs(j - real_j);
        }
    }

    return current.num_moves + distance;
}

//Depth Limited Search
vector<char> DLS(state initial, int heuristic){
    state next_states[4];
    vector<char> path;

    if (memcmp(initial.board, TARGET_BOARD, sizeof(initial.board)) == 0)
        return initial.movements;
    
    //Didn't find anything in the specified limit
    if (heuristic > limit){
        next_limit = min(heuristic, next_limit);
        return path; //as null or empty
    }

    generateMovements(initial, next_states);

    for (int i = 0; i < 4; i++) {
        if (!visited[convertToString(next_states[i].board)] && next_states[i].heuristic != -1) {
            visited[convertToString(next_states[i].board)] = true;

            next_states[i].heuristic = calculateHeuristic(next_states[i]);
            
            path = DLS(next_states[i], next_states[i].heuristic);

            if (!path.empty())
                return path;
        }
    }

    return path;
}

vector<char> IDA(state initial){
    vector<char> path;
    limit = calculateHeuristic(initial);

    while(true){
        visited.clear();

        next_limit = INT_MAX;

        visited[convertToString(initial.board)] = true;

        path = DLS(initial, limit);
        
        if (!path.empty())
            return path;
        
        if (next_limit == INT_MAX)
            return path; //as null
        
        limit = next_limit;

        if (limit > 32) //maximum number of depth for this problem
            return path; //as null
    }
}

int isSolvable(string list){
    //The grid it's always odd, so let´s count inversions
    int num_inversions = 0;

    //O(n²) = O(81) -> acceptable
    for (int i = 0; i < 9; i++){
        for (int j = i + 1; j < 9; j++){
            if (i < j && list[i] != 'x' && list[j] != 'x' && list[i] > list[j]){
                num_inversions++;
            }
        }
    }

    return num_inversions % 2 == 0;
}

int main(void) {
    int numTests;
    state initial;
    vector<char> path;

    cin >> numTests;

    for (int i = 0; i < numTests; i++) {
        if (i > 0)
            cout << endl;
        
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                cin >> initial.board[j][k];

                if (initial.board[j][k] == 'x') {
                    initial.blank_position = {j, k};
                }
            }
        }

        initial.num_moves = 0;
        initial.heuristic = 0;

        if (!isSolvable(convertToString(initial.board))) {
            cout << "unsolvable" << endl;
        } else {
            path = IDA(initial);
            if (!path.empty())
                for (uint j = 0; j < path.size(); j++) {
                    cout << path[j];
                }
            cout << endl;
        }
    }

    return 0;
}