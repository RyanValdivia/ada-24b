#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>

int maxScore (const std::vector<std::vector<int>>& combinations);

int maxScoreRec (std::vector<bool>& taken, const std::vector<std::vector<int>>& combinations, int groups, std::unordered_map<std::string, int> memo);

int maxScore (const std::vector<std::vector<int>>& combinations, std::unordered_map<std::string, int>& memo) {
    std::vector<bool> taken(9, false);
    return maxScoreRec(taken, combinations, 0, memo);
}

int maxScoreRec (std::vector<bool>& taken, const std::vector<std::vector<int>>& combinations, int groups, std::unordered_map<std::string, int> memo) {
    if (groups == 3) {
        return 0;
    }

    std::string state = "";
    for (bool taken : taken) {
        state += taken ? "1" : "0";
    }

    if (memo.find(state) != memo.end()) {
        return memo[state];
    }

    int maxScore = -1;

    for (auto& comb : combinations) {
        int a = comb[0], b = comb[1], c = comb[2], score = comb[3];

        if (!taken[a - 1] && !taken[b - 1] && !taken[c - 1]) {
            taken[a - 1] = taken[b - 1] = taken[c - 1] = true;

            int newScore = maxScoreRec(taken, combinations, groups + 1, memo);

            if (newScore != -1) {
                maxScore = std::max(maxScore, newScore + score);
            }

            taken[a - 1] = taken[b - 1] = taken[c - 1] = false;
        }
    }

    memo[state] = maxScore;
    return maxScore;
}



int main () {
    std::unordered_map<std::string, int> memo;

    for (int i = 0; i < 1000; i++) {
        int n;
        std::cin >> n;

        if (n == 0) {
            break;
        }

        std::vector<std::vector<int>> combinations;

        for (int j = 0; j < n; j++) {
            int a, b, c, s;
            std::cin >> a >> b >> c >> s;

            combinations.push_back(std::vector<int>({a, b, c, s}));
        }
        std::cout << "Case " << i + 1 << ": " << maxScore(combinations, memo) << std::endl;
    }
    return 0;
}


