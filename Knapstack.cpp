#include <iostream>
#include <cstdio> //IO
#include <numeric>
#include <sstream>
#include <cstring>

#define N 20
#define MAX_WEIGHT 100

using namespace std;

int weight[N + 1];
int MEMO[N + 1][MAX_WEIGHT + 1];

int recursive2BootsProblem(int i, int w){
    if (i == 0 || w == 0)
        return 0;

    if (weight[i] > w)
        return recursive2BootsProblem(i - 1, w);
    
    return max(weight[i] + recursive2BootsProblem(i - 1, w - weight[i]), recursive2BootsProblem(i - 1, w));
}

int recursivePD2BootsProblem(int i, int w){
    if (i == 0 || w == 0)
        return 0;
    
    if (MEMO[i][w] != -1) //already calculated
        return MEMO[i][w];
    
    if (weight[i] > w)
        MEMO[i][w] = recursivePD2BootsProblem(i - 1, w);
    else
        MEMO[i][w] = max(weight[i] + recursivePD2BootsProblem(i - 1, w - weight[i]), recursivePD2BootsProblem(i - 1, w));
    
    return MEMO[i][w];
}

int iterativePD2BootsProblem(int n, int max_weight){
    for (int i = 1; i <= n; i++){
        for (int w = 0; w <= max_weight; w++){
            if (weight[i] > w)
                MEMO[i][w] = MEMO[i - 1][w];
            else{
                MEMO[i][w] = max(weight[i] + MEMO[i - 1][w - weight[i]], MEMO[i - 1][w]);
            }
        }
    }

    return MEMO[n][max_weight];
}

void print_matrix()
{
    for (int i = 0; i < N + 1; i++){
        for (int j = 0; j < MAX_WEIGHT + 1; j++){
            cout << MEMO[i][j];
        }
        cout << endl;
    }
}

int main(){
    int num_tests;
    int sum = 0;
    int j = 0;
    char c;

    memset(MEMO[0], 0, sizeof(MEMO[0]));
    cin >> num_tests;

    for (int i = 0; i < num_tests; i++)
    {  
        weight[0] = 0;
        //memset(MEMO, -1, sizeof(MEMO));

        while (scanf("%d%c", &weight[++j], &c) != EOF && c == ' ') { ; }    
            
        sum = accumulate(weight, weight + (j + 1), 0);
        
        if (sum % 2 != 0)
            cout << "NO" << endl;
        else
            if (iterativePD2BootsProblem(j, sum/2) == sum/2)
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
        j = 0;
    }

    return 0;
}