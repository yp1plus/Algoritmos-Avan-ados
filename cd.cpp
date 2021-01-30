/* Yure Pablo */
#include <iostream> //cin, cout
#include <vector>
#include <cstdio> //IO
#include <iterator>
#include <climits>

using namespace std;

#define MAX_TRACKS 20

int tracks[MAX_TRACKS];
vector<int> aux;
vector<int> tracksForTape;

int maximum = INT_MIN;

void getSequenceTracks(int minutesTape, int numTracks, int sum, int currentIndex){
    //Break when the tracks over or when already come to the greatest solution 
    for (int i = currentIndex; i < numTracks; i++){
        if (maximum == minutesTape || (int) tracksForTape.size() == numTracks){
            break;
        }

        if (tracks[i] + sum <= minutesTape){
            sum += tracks[i];
            maximum = max(sum, maximum);
            aux.push_back(tracks[i]);   
            if (maximum == sum)
                tracksForTape = aux;         
            getSequenceTracks(minutesTape, numTracks, sum, i + 1);
            sum -= tracks[i];
            aux.pop_back();
        }
    }
}

int main(){
    int minutesTape;
    int numTracks;

    while (cin >> minutesTape){
        cin >> numTracks;

        for (int i = 0; i < numTracks; i++){
            cin >> tracks[i];
        }

        maximum = INT_MIN;
        getSequenceTracks(minutesTape, numTracks, 0, 0);

        for (vector<int>::iterator it = tracksForTape.begin(); it != tracksForTape.end(); it++){
            printf("%d ", *it);
        }

        printf("sum:%d\n", maximum);

        tracksForTape.clear();
        aux.clear();
    }
}