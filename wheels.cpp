#include <iostream>
#include <cstdio> //IO
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

struct state{
	int digits[4];
	int depth;
	int heuristic;
};

#define TOTAL_NUM_DIGITS 10
#define ERROR -1
#define DIGITS_PER_state 4
#define POSSIBLE_COMBINATIONS 8

int visited[TOTAL_NUM_DIGITS][TOTAL_NUM_DIGITS][TOTAL_NUM_DIGITS][TOTAL_NUM_DIGITS];

/* Function to compare in priority_queue and create a min heap */
bool operator<(const state &s1, const state &s2) {
		return s1.heuristic > s2.heuristic;
}

int getVisited(int configuration[4]){
    return visited[configuration[0]][configuration[1]][configuration[2]][configuration[3]];
}

void setVisited(int configuration[4], int n){
    visited[configuration[0]][configuration[1]][configuration[2]][configuration[3]] = n;
}

int calculateHeuristic(state current, state target){
	int distance = 0;
    int h = 0; //Manhattan Distance

	for (int i = 0; i < DIGITS_PER_state; i++){
		distance = abs(current.digits[i] - target.digits[i]);
        //compare the distance in clockwise and the opposite direction
		h += min(distance, 10 - distance);
	}

	return h + current.depth;
}

void readDigits(state *s){
    for (int j = 0; j < DIGITS_PER_state; j++){
            cin >> s->digits[j];
    }
}

int clamp(int value, int min, int max){
    if (value < min) //goes to clockwise with the left (-) arrow
        return max;
    
    if (value > max) //goes to anticlockwise with the right (+) arrow
        return min;
    
    return value;
}

int AStar(state current, state target){
    state configurations[8];
    int moveController = -1;
    priority_queue<state> q;

    /* if the initial configurations it's not forbidden */
    if (!getVisited(current.digits)){
        setVisited(current.digits, 1);
        q.push(current);

        while(!q.empty()){
            current = q.top();
            q.pop();
            
            /* Found the target */
            if (memcmp(current.digits, target.digits, sizeof(current.digits)) == 0){
                return current.depth;
            }

            /* Make the all eight possible transitions */
            for (int i = 0, j = 0; i < 8; i++, j = i/2){
                configurations[i] = current;
                configurations[i].depth = current.depth + 1;
                configurations[i].digits[j] = clamp(configurations[i].digits[j] + moveController, 0, 9);
                moveController *= -1;
            }

            /* Goes through the transitions to search the target */
            for (int i = 0; i < POSSIBLE_COMBINATIONS; i++){
                if (!getVisited(configurations[i].digits)){
                    setVisited(configurations[i].digits, 1);
                    configurations[i].heuristic = calculateHeuristic(configurations[i], target);
                    q.push(configurations[i]);
                }
            }
		}
	}

    return ERROR;
}

int main(){
    int numTests, numForbiddens;
    int i, j;
    state initial, target, aux;

    cin >> numTests;

    for (i = 0; i < numTests; i++){
        readDigits(&initial);
        readDigits(&target);
        cin >> numForbiddens;

        memset(visited, 0, sizeof(int)*10000);

        for (j = 0; j < numForbiddens; j++){
            readDigits(&aux);
            setVisited(aux.digits, 1);
        }

        initial.depth = 0;
        cout << AStar(initial, target) << endl;  
    }

    return 0;
}