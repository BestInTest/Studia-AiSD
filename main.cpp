#include <iostream>
#include <string>
#include <vector>

using namespace std;

const long long MOD = 1e9 + 7;

long long waysAny[100];
long long waysBoth[100];
long long waysSecond[100];

void initCountsCache() {
    for (int i = 0; i <= 9; i++) {
        for (int j = 0; j <= 9; j++) {
            int p = i * j;
            waysAny[p]++;

            if (i != 0 && j != 0) {
                waysBoth[p]++;
            }
            if (j != 0) {
                waysSecond[p]++;
            }
        }
    }
}

// Obliczanie ile jest par cyfr takich że ich iloczyn daje result
long long calcPairs(int result) {
    return waysAny[result];
}

vector<long long> buildDp(const string& s) {
    int n = s.length();
    vector<long long> dp(n + 1);
    dp[n] = 1;

    // Petla od konca
    for (int i = n - 1; i >= 0; i--) {
        int num = s[i] - '0'; // Zamiana znaku na liczbe
        long long possib = calcPairs(num) * dp[i + 1];
        dp[i] = dp[i] + possib;
        dp[i] %= MOD;

        // Bierzemy dwie cyfry jeśli się da
        if (i + 1 < n && s[i] != '0') {
            num = (s[i] - '0') * 10 + (s[i + 1] - '0');
            possib = calcPairs(num) * dp[i + 2];
            dp[i] = dp[i] + possib;
            dp[i] %= MOD;
        }
    }

    return dp;
}

long long calcResult(const string& s, vector<long long>& dp) {
    int n = s.length();
    long long result = 0;

    // Krok o 1 cyfre
    int num = s[0] - '0';
    long long w1 = (n == 1) ? waysAny[num] : waysBoth[num];
    result = (result + w1 * dp[1]) % MOD;

    // Krok o 2 cyfry
    if (n >= 2 && s[0] != '0') {
        num = (s[0] - '0') * 10 + (s[1] - '0');
        result = result + waysAny[num] * dp[2];
        result %= MOD;
    }

    if (s[0] == '0') return result;

    for (int i = 1; i < n; i++) {
        long long currentWays = 0;

        // Krok o 1 cyfre
        int val1 = s[i] - '0';
        long long w2 = (i == n - 1) ? waysAny[val1] : waysSecond[val1];
        currentWays = currentWays + w2 * dp[i + 1];
        currentWays %= MOD;

        // Krok o 2 cyfry
        if (i + 1 < n && s[i] != '0') {
            int val2 = (s[i] - '0') * 10 + (s[i + 1] - '0');
            currentWays = currentWays + waysAny[val2] * dp[i + 2];
            currentWays %= MOD;
        }

        result = result + 2 * currentWays;
        result %= MOD;
    }

    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    string s;
    cin >> s;

    initCountsCache();
    vector<long long> dp = buildDp(s);
    long long result = calcResult(s, dp);

    cout << result << endl;

    return 0;
}
