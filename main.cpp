#include <iostream>

struct Dzik {
    int x;
    int y;
    bool p; // 0 - samica, 1 - samiec
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int s;
    std::cin >> s; // liczba stad dzikow

    for (int i = 0; i < s; ++i) {
        int n;
        std::cin >> n; // liczba dzikow w stadzie

        for (int j = 0; j < n; ++j) {

        }
    }

    return 0;
}