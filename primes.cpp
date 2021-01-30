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

map<int,int> primeFactors(ll number){
    map<int, int> factors;

    for (int i = 0; i < (int) primes.size() && (ll) primes[i]*primes[i] <= number && number != 1; i++){
       while(number % primes[i] == 0){
           number /= primes[i];
           factors[primes[i]]++;
       }
    }

    if (number != 1) //number is actually a prime
        factors[number]++;
    
    return factors;
}

bool isDivisibleBy(int a, int b){
    if (b == 0){
        return false;
    }

    if ((a == 0 || a == 1) && b != 1){
        return false;
    }

    if (b <= a){
        return true;
    }

    map<int, int> factors;
    int primeFactorFatorial;

    if (isPrime(b)){
        factors[b]++;
        primeFactorFatorial = primeFactorFactorialNumbers(a, b);
        if (primeFactorFatorial < factors[b])
            return false;
        
        return true;
    }
    
    for (int i = 0; i < (int) primes.size() && (ll) primes[i]*primes[i] <= b && b != 1; i++){
       while(b % primes[i] == 0){
           b /= primes[i];
           factors[primes[i]]++;
       }

       if (factors[primes[i]] > 0){
           primeFactorFatorial = primeFactorFactorialNumbers(a, primes[i]);
           if (primeFactorFatorial < factors[primes[i]])
               return false;
       }
    }

    if (b != 1) {//number is actually a prime
        factors[b]++;
        primeFactorFatorial = primeFactorFactorialNumbers(a, b);
        if (primeFactorFatorial < factors[b])
            return false;
    }

    return true;
}

int main(){
    int factorial_index, number;

    sieve(ROOT_FROM_2_HIGH_TO_31);
    
    while(cin >> factorial_index){
        cin >> number;

        if (isDivisibleBy(factorial_index, number)){
            cout << number << " divides " << factorial_index << "!" << endl;
        } else {
            cout << number << " does not divide " << factorial_index << "!" << endl;
        }
    }

    return 0;
}



