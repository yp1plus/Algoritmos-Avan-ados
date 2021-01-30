#include <iostream>
#include <cstdio> //IO
#include <vector>

using namespace std;

int findTallestShorter(vector<long int> v, int begin, int end, long int x){
    int middle = (begin + end) / 2;

    if (v[middle] < x){
        if (middle + 1 > end || v[middle + 1] >= x){
            return middle;
        } else {
            return findTallestShorter(v, middle + 1, end, x);
        }
    } else {
        return findTallestShorter(v, begin, middle, x);
    }
}

int findShortestTaller(vector<long int> v, int begin, int end, long int x){
    int middle = (begin + end) / 2;

    if (v[middle] > x){
        if (middle - 1 < begin || v[middle - 1] <= x){
            return middle;
        } else {
            return findShortestTaller(v, begin, middle, x);
        }
    } else {
        return findShortestTaller(v, middle + 1, end, x);
    }

}

/* Vector it is in ascending onder */
void findLadies(vector<long int> heightLadyChimps, int heightGoofyChimp){
    int n = heightLadyChimps.size();
    int pos = 0;
    
    if (heightLadyChimps[0] < heightGoofyChimp){
        pos = findTallestShorter(heightLadyChimps, 0, n-1, heightGoofyChimp);
        cout << heightLadyChimps[pos] << " ";
    } else { //there is not lady shorter than goofy chimp
        cout << "X ";
    }
        
    if (heightLadyChimps[n - 1] > heightGoofyChimp){
        pos = findShortestTaller(heightLadyChimps, 0, n-1, heightGoofyChimp);
        cout << heightLadyChimps[pos] << endl;
    } else { //there is not lady taller than goofy chimp
        cout << "X" << endl;
    }
}

int main(){
    int i = 0;
    int numLadyChimps;

    cin >> numLadyChimps;

    vector<long int> heightLadyChimps (numLadyChimps);

    for (i = 0; i < numLadyChimps; i++){
        cin >> heightLadyChimps[i];
    }

    int numQueries;
    long int heightGoofyChimp;

    cin >> numQueries;

    for (i = 0; i < numQueries; i++){
        cin >> heightGoofyChimp;
        findLadies(heightLadyChimps, heightGoofyChimp);
    }

    return 0;
}