#include <iostream>
#include <vector>
#include <unordered_map>

std::vector<int> generatePrimes (int n);

int countWays (int n, int k, std::vector<int>& primes);

int countWays (int n, int k, std::vector<int>& primes, int index, std::vector<std::vector<std::vector<int>>>& memo);

std::vector<int> generatePrimes (int n) {
    std::vector<int> primes;
    std::vector<bool> isPrime(n + 1, true);

    for (int p = 2; p <= n; ++p) {
        if (isPrime[p]) {
            primes.push_back(p);
            for (int i = p * p; i <= n; i += p) {
                isPrime[i] = false;
            }
        }
    }
    return primes;
}

int countWays (int n, int k, std::vector<int> &primes, std::vector<std::vector<std::vector<int>>>& memo) {
    return countWays(n, k, primes, 0, memo);
}


int countWays (int n, int k, std::vector<int>& primes, int index, std::vector<std::vector<std::vector<int>>>& memo) {
    if (k == 0) {
        return n == 0 ? 1 : 0;
    }
    if (n <= 0 || index >= primes.size()) {
        return 0;
    }

    if (memo[n][k][index] != -1) {
        return memo[n][k][index];
    }

    int include = countWays(n - primes[index], k - 1, primes, index + 1, memo);
    int exclude = countWays(n, k, primes, index + 1, memo);

    int result = include + exclude;
    memo[n][k][index] = result;
    return result;
}


int main () {
    std::vector<int> primes = generatePrimes(1120);
    int maxN = 1120;
    int maxK = 14;
    int maxIndex = primes.size();
    std::vector<std::vector<std::vector<int>>> memo(maxN + 1, std::vector<std::vector<int>>(maxK + 1, std::vector<int>(maxIndex, -1)));

    while (true) {
        int n, k;
        std::cin >> n >> k;

        if (n == 0 && k == 0) {
            break;
        }

        std::cout << countWays(n, k, primes, memo) << std::endl;
    }

    return 0;
}
