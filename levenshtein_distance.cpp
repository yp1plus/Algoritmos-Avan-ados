#include <iostream>
#include <cstdio> //IO
#include <vector>
#include <algorithm>

using namespace std;

#define VALUE_A_ASCII 97

int getIndexLetter(char l){
    //index starts in one
    return l - VALUE_A_ASCII + 1;
}

/* Convert s1 to s2
 * Operations have costs
 * Replacing costs the difference between indexes numbers of the letters to be replaced
 * Inserting costs the index number of the letter to be inserted
 * Deleting costs the index number of the letter to be deleted
 */
int findLevenshteinDistance(string s1, string s2){
    int m = s1.length();
    int n = s2.length();

    int memo[m + 1][n + 1]; //the first column or line considers comparing to a null sequence

    for (int i = 0; i <= m; i++){
        for (int j = 0; j <= n; j++){
            if (i == 0)
                memo[i][j] = j == 0 ? j : getIndexLetter(s2[j - 1]) + memo[i][j - 1];
            
            else if (j == 0)
                memo[i][j] = i == 0 ? i : getIndexLetter(s1[i - 1]) + memo[i - 1][j];
            
            //if are the same, ignore this number and maintain the last result 
            else if (s1[i - 1] == s2[j - 1])
                memo[i][j] = memo[i - 1][j - 1];
            
            else
                memo[i][j] = min(abs(getIndexLetter(s1[i - 1]) - getIndexLetter(s2[j - 1])) + memo[i - 1][j - 1], //replace
                                    min(getIndexLetter(s2[j - 1]) + memo[i][j - 1], //insert
                                    getIndexLetter(s1[i - 1]) + memo[i - 1][j])); //remove
        }
    }

    return memo[m][n];
}

int main(){
    string s1;
    string s2;

    cin >> s1;
    cin >> s2;
    
    cout << findLevenshteinDistance(s1, s2) << endl;

    return 0;
}