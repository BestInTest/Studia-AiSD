#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;
long long pairs[100] = {};

// Obliczanie wszystkich sposobów iloczynu dwóch cyfr
void calcPairs() {
    for (int i = 0; i <= 9; i++) {
        for (int j = 0; j <= 9; j++) {
            pairs[i * j]++;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    calcPairs();

    string inputStr;
    cin >> inputStr;

    int len = inputStr.length();
    vector<long long> dp(len + 1);

    // pusty sufiks można uzyskać na 1 sposób (nic nie robiąc)
    dp[len] = 1;

    // Pętla od końca
    for (int i = len - 1; i >= 0; i--) {
        int num1 = inputStr[i] - '0'; // konwersja znaku na liczbe
        long long possib = pairs[num1] * dp[i + 1];
        dp[i] = (dp[i] + possib) % MOD;

        // Sprawdzamy czy możemy wziąć dwie cyfry
        if (i + 1 < len && inputStr[i] != '0') {
            int dzies = (inputStr[i] - '0') * 10;
            int jedn = inputStr[i + 1] - '0';
            int num2 = dzies + jedn; // liczba z dwóch cyfr

            possib = pairs[num2] * dp[i + 2];
            dp[i] = (dp[i] + possib) % MOD;

        }
    }

    long long result = dp[0];
    for (int i = 1; i < len; i++) {
        result = (result + 2 * dp[i]) % MOD;
    }

    cout << result << endl;

    return 0;
}