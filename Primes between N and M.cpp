#include <iostream>
#include <vector>
using namespace std;


/*
Segmented Sieve of Eratosthenes Algorithm (https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes).
It is used for calculating all the primes in the interval [N, M]. 
It's time is O((M-N)log(M)), which is faster than the conventional sieve algorithm when (M-N)/M << 1 and M is really big (~10^9).
It seems to work until M ~ 10^19 :D
It can also calculate the average distance between the primes in the interval.
*/

void averageDistance(vector<bool> is_prime, unsigned long long int N, unsigned long long int M)
{
    int n; 
    int sum = 0;
    float avg = 0;
    vector<unsigned long long int> primes;

    for (int i = 0; i < is_prime.size(); i++) {
        if (is_prime[i])
            primes.push_back(i + N);
    }

    n = primes.size();

    for(int i = 0; i < n - 1; i++)
        sum += primes[i+1] - primes[i];

    avg = (float)sum/n;
    
    cout << "Number of primes: " << n << endl;
    cout << "Average distance between consequent primes in the interval: " << avg << endl;
}

void segmentedSieve(vector<bool> &is_prime, unsigned long long int N, unsigned long long int M)
{
    for (int i = 2; i * i <= M ; i++) {
        unsigned long long int start = ((unsigned long long int)((N - 1) / i) + 1) * i;
        for (unsigned long long int j = start; j <= M ; j+= i) {
            if (j >= N && j <= M && j != i) 
                is_prime[j - N] = false;
        }
    }

    cout << "Primes in the interval [" << N << ", " << M << "]: " << endl; 
    cout << "-------------------------" << endl; 

    for (int i = 0; i < is_prime.size(); i++) {
        if (is_prime[i])
            cout <<(unsigned long long int) i + N << " ";
    }

    cout << endl << "-------------------------" << endl << endl; 
}

int main() {
    
    unsigned long long int N, M;
    bool flag = false;
    
    cout << "Specify the interval [N, M] to calculate the primes in the form 'N M': ";
    cin >> N >> M;
    
    vector<bool> is_prime(M-N+1, true);

    cout << "Do you want to calculate the average distance between this primes (1 for yes, 0 for no): ";
    cin >> flag;
    cout << endl;

    segmentedSieve(is_prime, N, M);

    if(flag)
        averageDistance(is_prime, N, M);

    return 0;
}