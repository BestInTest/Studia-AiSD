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
long long calcPairs(int num) {
    return waysAny[num];
}

vector<int> buildDp(const string& s) {
    int n = s.length();
    vector<int> dp(min(n + 1, 3));

    // Pętla poniżej iteruje od n-1 więc trzeba ręcznie ustawić dp[n] jeśli mieści się w wektorze
    if (n < dp.size()) {
        dp[n] = 1;
    }

    long long dpNext = 1;
    long long dpNext2 = 0;

    // Petla od konca
    for (int i = n - 1; i >= 0; i--) {
        int num = s[i] - '0'; // Zamiana znaku na liczbe
        long long possib = calcPairs(num) * dpNext;
        long long currentVal = possib;

        if (i + 1 < n && s[i] != '0') {
            num = (s[i] - '0') * 10 + (s[i + 1] - '0');
            possib = calcPairs(num) * dpNext2;
            currentVal += possib;
        }

        long long dp_i = currentVal % MOD;
        if (i < dp.size()) {
            dp[i] = dp_i;
        }

        // Przesunięcie wartości
        dpNext2 = dpNext;
        dpNext = dp_i;
    }

    return dp;
}

long long calcResult(const string& s, vector<int>& dp) {
    int n = s.length();
    long long result = 0;

    // Krok o 1 cyfre
    int num = s[0] - '0';
    long long way = (n == 1) ? waysAny[num] : waysBoth[num];
    result = (result + way * (long long) dp[1]) % MOD;

    // Krok o 2 cyfry
    if (n >= 2 && s[0] != '0') {
        num = (s[0] - '0') * 10 + (s[1] - '0');
        result = result + waysAny[num] * (long long) dp[2];
        result %= MOD;
    }

    if (s[0] == '0') return result;

    long long dpNext = 1;
    long long dpNext2 = 0;

    for (int i = n - 1; i >= 1; i--) {
        num = s[i] - '0';

        long long possib = calcPairs(num) * dpNext;
        long long currentVal = possib;

        if (i + 1 < n && s[i] != '0') {
            int num2 = (s[i] - '0') * 10 + (s[i + 1] - '0');
            possib = calcPairs(num2) * dpNext2;
            currentVal = currentVal + possib;
        }

        long long dp_i = currentVal % MOD;
        long long currentWays = 0;

        // Krok o 1 cyfre
        way = (i == n - 1) ? waysAny[num] : waysSecond[num];
        currentWays = currentWays + way * dpNext;
        currentWays %= MOD;

        // Krok o 2 cyfry
        if (i + 1 < n && s[i] != '0') {
            num = (s[i] - '0') * 10 + (s[i + 1] - '0');
            currentWays = currentWays + waysAny[num] * dpNext2;
            currentWays %= MOD;
        }

        result = result + 2 * currentWays;
        result %= MOD;

        // Przesunięcie wartości
        dpNext2 = dpNext;
        dpNext = dp_i;
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
    vector<int> dp = buildDp(s);
    long long result = calcResult(s, dp);

    cout << result << endl;

    return 0;
}