#include <iostream>
#include <cstdio> //IO
#include <vector>
#include <bitset>
#include <map>
#include <math.h>

using namespace std;

typedef long long ll;

#define ROOT_FROM_2_HIGH_TO_31 46341

ll sieve_size;
bitset<ROOT_FROM_2_HIGH_TO_31> bs_prime;
vector<int> primes;


//(O(n): space memory    O(n* log(log n)): time complexity)
void sieve(ll upperBound){
    sieve_size = upperBound + 1;
    bs_prime.set(); //set all bits to 1
    bs_prime[0] = bs_prime[1] = 0;

    for (ll i = 2; i <= sieve_size; i++){
        if (bs_prime[i]){
            for (ll j = i * i; j <= sieve_size; j += i){
                bs_prime[j] = 0;
            }

            primes.push_back((int) i);
        }
    }
}

bool isPrime(ll number){
    if (number <= sieve_size){
        return bs_prime[number]; //O(1)
    }

    for (int i = 0; i < (int) primes.size() && (ll) primes[i]*primes[i] <= number; i++){
        if (number % primes[i] == 0)
            return false;
    }

    return true;
}

int primeFactorFactorialNumbers(ll number, int prime){
    int primeFactor = 0;

    for (ll j = prime; j <= number; j *= prime){
        primeFactor += (int) (number/j); 
    }

    return primeFactor;
}

map<int,int> primeFactorsFactorialNumbers(ll number){
    map<int, int> factorsFatorial;
    
    for (int i = 0; i < (int) primes.size() && primes[i] <= number; i++){
        factorsFatorial[primes[i]] = primeFactorFactorialNumbers(number, primes[i]);
    }

    return factorsFatorial;
}

void printPrimesFactors(int n){
    if (n == 0 || n == 1){
        return;
    }

    printf("%3d! =", n);

    for (int i = 0; i < (int) primes.size() && primes[i] <= n; i++){
        if ((i + 1) > 15 && i % 15 == 0){
            printf("\n");
            printf("      ");
        }

        printf("%3d", primeFactorFactorialNumbers(n, primes[i]));

    }

    printf("\n");
}

int main(){
    int n;

    sieve(ROOT_FROM_2_HIGH_TO_31);
    
    while(cin >> n){
        printPrimesFactors(n);
    }

    return 0;
}



