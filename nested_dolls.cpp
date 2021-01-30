#include <iostream>
#include <cstdio> //IO
#include <numeric>
#include <cstring>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> lnis;

bool compare(pair<int, int> a, pair<int, int> b){
    if (a.first == b.first)
        return a.second > b.second; //height
    
    return a.first < b.first; //width
}

int LNIS(vector< pair<int,int> > measures){
    int num_dolls = measures.size();

    sort(measures.begin(), measures.end(), compare);
    
    lnis[0] = 1;
    int maximum = 1;

    for (int i = 1; i < num_dolls; i++){
        for (int j = 0; j < i; j++){
            //Dilworth's theorem: longest non increasing subsequence equal to 
            //smallest number of increasing subsequences in a partially ordered vector
            if (measures[i].second <= measures[j].second){
                lnis[i] = max(lnis[j] + 1, lnis[i]);
            }   
        }

        maximum = max(maximum, lnis[i]);
    }

    return maximum;
}

int main(){
    int num_tests;
    int num_dolls;

    cin >> num_tests;
    
    vector<pair<int,int> > measures;

    for (int i = 0; i < num_tests; i++){
        cin >> num_dolls;
        lnis.resize(num_dolls);
        measures.resize(num_dolls);

        for (int j = 0; j < num_dolls; j++){
            cin >> measures[j].first >> measures[j].second;
        }

        lnis.assign(lnis.size(), 1);

        cout << LNIS(measures) << endl;
    }

    return 0;
}

