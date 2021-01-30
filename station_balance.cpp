#include <iostream>
#include <cstdio> //IO
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

//O(n*logn) execution and O(n) space
void balancing(vector<int> specimens, int numChambers){
    int sizeVector = specimens.size();
    int i = 0, j = 0, k = 0;
    vector<int> allSpecimens(2*numChambers);
    float imbalance = 0;
    float average = 0;

    for (i = 0; i < sizeVector; i++){
        allSpecimens[i] = specimens[i];
        average += specimens[i];
    }

    average /= numChambers;

    /* Completes with zero to make an estrategy of the extremes */
    for (i = sizeVector; i < 2*numChambers; i++){
        allSpecimens[i] = 0;
    }

    stable_sort(allSpecimens.begin(), allSpecimens.end());

    for (j = 0, k = 2*numChambers - 1; k >= numChambers; j++, k--){
        printf(" %d:", j);
        if (allSpecimens[j] != 0)
            printf(" %d", allSpecimens[j]);
        if (allSpecimens[k] != 0)
            printf(" %d", allSpecimens[k]);
        printf("\n");
        imbalance += abs(allSpecimens[j] + allSpecimens[k] - average);
    }

    printf("IMBALANCE = %.5F\n\n", imbalance);
}

int main(){
    int numChambers;
    int numSpecimens;
    int i = 1;

    while (cin >> numChambers){
        cin >> numSpecimens;

        vector<int> specimens (numSpecimens);

        for (int i = 0; i < numSpecimens; i++){
            cin >> specimens[i];
        }

        printf("Set #%d\n", i++);

        balancing(specimens, numChambers);
    }

}