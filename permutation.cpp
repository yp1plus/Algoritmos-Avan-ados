#include <iostream>
#include <cstdio> //IO
#include <vector>
#include <algorithm>

using namespace std;

int findMinimumEditDistance(vector<int> p1, vector<int> p2){
    int m = p1.size();
    int n = p2.size();

    int memo[m + 1][n + 1]; //the first column or line considers comparing to a null sequence

    for (int i = 0; i <= m; i++){
        for (int j = 0; j <= n; j++){
            if (i == 0)
                memo[i][j] = j;
            
            else if (j == 0)
                memo[i][j] = i;
            
            //if are the same, ignore this number and maintain the last result 
            else if (p1[i - 1] == p2[j - 1])
                memo[i][j] = memo[i - 1][j - 1];
            
            else
                memo[i][j] = 1 + min(memo[i][j - 1], //insert
                                     memo[i - 1][j]); //remove
        }
    }

    return memo[m][n];
}

void readVector(vector<int> &v){
    int n = v.size();

    for (int k = 0; k < n; k++){
        cin >> v[k];
    }
}

int main(){
    int num_tests;
    int n;
    vector<int> p1;
    vector<int> p2;

    cin >> num_tests;

    for (int i = 0; i < num_tests; i++){
        cin >> n;
        p1.resize(n);
        p2.resize(n);
        
        readVector(p1);
        readVector(p2);
        
        printf("Case %d: %d\n", i + 1, findMinimumEditDistance(p1, p2));
    }

    return 0;
}