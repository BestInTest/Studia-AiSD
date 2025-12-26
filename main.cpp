#include <iostream>
#include <vector>

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

        std::vector<Dzik> dziki(n);
        for (int j = 0; j < n; ++j) {
            std::cin >> dziki[j].x >> dziki[j].y >> dziki[j].p;
        }

        int m;
        std::cin >> m;
        for (int k = 0; k < m; ++k) {
            int idx, dx, dy;
            std::cin >> idx >> dx >> dy;
            dziki[idx].x += dx;
            dziki[idx].y += dy;
        }
    }

    return 0;
}