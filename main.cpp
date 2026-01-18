#include <iostream>
#include <string>
#include <vector>

using namespace std;

const long long MOD = 1e9 + 7;

// Obliczanie ile jest par cyfr takich że ich iloczyn daje result
long long calcPairs(int result) {
    long long count = 0;
    for (int i = 0; i <= 9; i++) {
        for (int j = 0; j <= 9; j++) {
            if (i * j == result) {
                count++;
            }
        }
    }
    return count;
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

long long calcResult(vector<long long>& dp) {
    int n = dp.size() - 1;
    long long result = dp[0]; // Przypadki równej długości

    // Dodajemy przypadki gdzie jedna liczba była dłuższa
    for (int i = 1; i < n; i++) {
        result = result + 2 * dp[i];
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

    vector<long long> dp = buildDp(s);
    long long result = calcResult(dp);

    cout << result << endl;

    return 0;
}
