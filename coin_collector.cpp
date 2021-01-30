/* Yure Pablo */

#include <iostream> //cin, cout
#include <vector>
#include <cstdio> //IO

using namespace std;

/* The minimum and the maximum always be possible (x == minimum or x >= maximum) */
/* Greedy algorithm : take always the bet solution for every set {C1}, {C1, C2}, {C1, C2, C3}... */
int getMaxTypeCoins(vector<int> coins){
    int amount = coins[0];
    int numMaxTypeCoins = 1;
    int numCoins = coins.size();
    
    if (numCoins == 1)
        return numMaxTypeCoins;

    // Coins between the first and the last one
    for (int i = 1; i < numCoins - 1; i++){
        //If it'd be greater than or equal, the coin[i+1] it'd be choose 
        if (coins[i] + amount < coins[i + 1]){
            //The amount it's only relevant during the iteration
            amount += coins[i];
            numMaxTypeCoins++;
        }
    }

    //Sum the last and return
    return ++numMaxTypeCoins;
}

int main(){
    int numTestCases = 0;
    int numCoins = 0;

    cin >> numTestCases;

    for (int i = 0; i < numTestCases; i++){
        cin >> numCoins;

        vector<int> coins (numCoins);

        for (int j = 0; j < numCoins; j++){
            cin >> coins[j];
        }
                //O(N)
        cout << getMaxTypeCoins(coins) << endl;
    }
}