#include <iostream>
#include <cstdio> //IO
#include <vector>

using namespace std;

#define _fi(n) for (int i = 0; i < n; i++)
#define _fj(n) for (int j = 0; j < n; j++)

#define OPEN_CELL 0
#define BLOCKED_CELL 1

int numPaths = 0;

void findNumPaths(vector< vector<int> > maze, int n, int i, int j){
    if (i == n - 1 && j == n -1){
        numPaths++;
        return;
    }

    if (j == n || i == n || i < 0 || j < 0){
        return;
    }    

    if (maze[i][j] == OPEN_CELL){
        maze[i][j] = BLOCKED_CELL;
        findNumPaths(maze, n, i, j+1);
        findNumPaths(maze, n, i+1, j);
        findNumPaths(maze, n, i-1, j);
        findNumPaths(maze, n, i, j-1);
        maze[i][j] = OPEN_CELL;
    }
}

int main(){
    int n;

    cin >> n;

    vector< vector<int> > maze (n, vector<int>(n));
    
    _fi(n)
        _fj(n)
            cin >> maze[i][j];
    
    findNumPaths(maze, n, 0, 0);
    
    cout <<  numPaths  << endl;
}