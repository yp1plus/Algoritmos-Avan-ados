/* Algorithm by Yure Pablo 
    Valid for matrixs n x n */

#include <iostream>
#include <vector>
#include <cstdio>
#include <iterator>
#include <algorithm>

using namespace std;

const int FREE = -1;

/* Verifies if the man i is preferred to the man j actually engaged to a woman */
//O(1)
bool isPreferred(vector<int> inversePreferenceCurrentWoman, int comparableMan, int engagedMan){
    return inversePreferenceCurrentWoman[comparableMan] < inversePreferenceCurrentWoman[engagedMan];
}

//returns the pairs of woman i (vector index) equals to man j
vector<int> stableMarriage(vector< vector<int> > preferencesWomen, vector< vector<int> > preferencesMen){
    //O(n²) space
    int numMarriages = preferencesMen.size();
    vector<int> manPair (numMarriages), womanPair (numMarriages);
    vector<int> currentPreference (numMarriages);
    vector< vector<int> > inversePreferencesWomen (numMarriages, vector<int>(numMarriages));
    int currentWoman = 0, currentMan = 0;
    int i = 0, j = 0;

    /* Iniatialize the vectors */
    //O(n)
    for (i = 0; i < numMarriages; i++){
        womanPair[i] = FREE;
        manPair[i] = FREE;
        currentPreference[i] = 0;
    }

    //O(n²)
    for (i = 0; i < numMarriages; i++){
        for (j = 0; j < numMarriages; j++){
            inversePreferencesWomen[i][preferencesWomen[i][j] - 1] = j;
        }
    }

    //O(n²)
    while (/*O(n)*/ find(manPair.begin(), manPair.end(), FREE) != manPair.end()){
        //O(n)
        //considers that always there is a wife for him
        while (manPair[currentMan] == FREE){
            currentWoman = preferencesMen[currentMan][currentPreference[currentMan]] - 1;

            if (womanPair[currentWoman] == FREE){
                manPair[currentMan] = currentWoman;
                womanPair[currentWoman] = i;
            } else {
                if (isPreferred(inversePreferencesWomen[currentWoman], currentMan, womanPair[currentWoman])){
                    manPair[womanPair[currentWoman]] = FREE;
                    womanPair[currentWoman] = currentMan;
                    manPair[currentMan] = currentWoman;
                }
            }

            currentPreference[currentMan]++;
        }

        if (currentMan >= numMarriages - 1)
            currentMan = 0;
        else
            currentMan++;  
    }

    return manPair;
}

int main(){
    int numTestCases; //<=100
    int numMarriages; //<=500
    int index;
    int i, j, k; 

    cin >> numTestCases; 

    vector<int> pairs;
    vector<int>::iterator it;
    
    for (k = 0; k < numTestCases; k++){
        cin >> numMarriages;
        
        vector < vector<int> > preferencesWomen (numMarriages, vector<int>(numMarriages));
        vector < vector<int> > preferencesMen (numMarriages, vector<int>(numMarriages));

        //reads the preferences matrix of women
        for (i = 0; i < numMarriages; i++){
            cin >> index; 
            for (j = 0; j < numMarriages; j++){
                cin >> preferencesWomen[i][j];
            }
        }

        //reads the preferences matrix of men
        for (i = 0; i < numMarriages; i++){
            cin >> index; 
            for (j = 0; j < numMarriages; j++){
                cin >> preferencesMen[i][j];
            }
        }

        pairs = stableMarriage(preferencesWomen, preferencesMen);
        
        for (it = pairs.begin(), i = 0; it != pairs.end(); it++, i++){
            printf("%d %d\n", i + 1, *it + 1);
        }
    }
}