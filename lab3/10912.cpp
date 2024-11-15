#include <iostream>

int memo[352][27][27];

int collisions(int sum, int length, int last) {

    if (sum < 0 || length < 0 || last * length > sum) {
        return 0;
    }

    if (length == 0 && sum == 0) {
        return memo[sum][length][last] = 1;
    }

    if (memo[sum][length][last] != -1) {
        return memo[sum][length][last];
    }

    unsigned int count = 0;

    for (int i = last + 1; i < 27; i++) {
        count += collisions(sum - i, length - 1, i);
    }

    memo[sum][length][last] = count;
    return count;
}

int main() {
    for (int i = 0; i < 352; i++)
        for (int j = 0; j < 27; j++)
            for (int k = 0; k < 27; k++)
                memo[i][j][k] = -1;

    int i = 1;
    while (true) {
        int length, sum;
        std::cin >> length >> sum;

        if (length == 0 && sum == 0) {
            break;
        }

        if (length > 26 || sum > 351) {
            std::cout << "Case " << i << ": " << 0 << std::endl;
        } else {
            std::cout << "Case " << i << ": " << collisions(sum, length, 0) << std::endl;
        }

        i++;
    }

    return 0;
}
