#include <iostream>
#include <cstdio> //IO
#include <vector>
#include <cmath>

using namespace std;

#define ERROR 0.000000001

int p, q, r, s, t, u;

double function(double x){
    return p * exp(-x) + q * sin(x) + r * cos(x) + s * tan(x) + t * x * x + u;
}

//as long as there is extrems positive and negative it's possible to aplicate bisection and there is solution
//O(log (high - low)/ERROR)
double solve(){
    double low = 0, high = 1;

    while (high - low > ERROR){
        double middle = (low + high) / 2;
        if (function(low) * function(middle) <= 0){ //low and middle are extrems
            high = middle;
        } else { //middle and high are extrems
            low = middle;
        }
    }

    return (low + high) / 2;
}

int main(){
    double pos = 0;

    while (cin >> p){
        cin >> q >> r >> s >> t >> u;
        if (function(0) * function(1) > 0){
            cout << "No solution" << endl;
        } else {
            pos = solve();

            printf("%.4lf\n", pos);
        }
    }

    return 0;
}