#include <iostream>
#include <cstdio> //IO
#include <vector>
#include <climits>

using namespace std;

#define EMPTY -1

int coins[30];
int quant_coins = 0;

int recursiveCalculateMinimumCoins(int value){
    if (value == 0) //if value is equal to 0, there is not coin change 
        return 0;
    
    int minimum = INT_MAX;

    for (int i = 0; i < quant_coins; i++){
        if (value - coins[i] >= 0){
            minimum = min(1 + recursiveCalculateMinimumCoins(value - coins[i]), minimum); 
        }
    }

    return minimum;
}

int recursiveDPCalculateMinimumCoins(int value, vector<int> *v){
    if (value == 0) //if value is equal to 0, there is not coin change 
        return 0;
    
    if ((*v)[value] != EMPTY)
        return (*v)[value];
      
    (*v)[value] = INT_MAX;

    for (int i = 0; i < quant_coins; i++){
        if (value - coins[i] >= 0){
            (*v)[value] = min(1 + recursiveDPCalculateMinimumCoins(value - coins[i], v), (*v)[value]); 
        }
    }

    return (*v)[value];
}

int iterativeDPCalculateMinimumCoins(int value){
    vector<int> v (value + 1);
    int i = 1;

    v[0] = 0;

    for (i = 1; i <= value; i++){
        v[i] = INT_MAX;

        for (int j = 0; j < quant_coins; j++){
            if (i - coins[j] >= 0)
                v[i] = min(1 + v[i - coins[j]], v[i]);
        }
    }

    return v[value];
}

int main(){
    int numTests;
    int value;

    cin >> numTests;

    for (int i = 0; i < numTests; i++){
        cin >> value;
        cin >> quant_coins;

        for (int j = 0; j < quant_coins; j++){
            cin >> coins[j];
        }

        //vector<int> v(value + 1, -1);
        cout << iterativeDPCalculateMinimumCoins(value) << endl;
    }

}