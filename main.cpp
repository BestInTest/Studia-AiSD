#include <iostream>
#include <vector>
#include <queue>

using std::string;
using std::vector;
using std::queue;

struct Node {
    int height = 0;
    vector<int> neighbors;
};

bool bfs(vector<Node>& arr, int start, int end, long water_level) {
    if (arr[start].height < water_level || arr[end].height < water_level) {
        return false;
    }
    if (start == end) {
        return true;
    }

    queue<int> q;
    q.push(start);
    vector<bool> visited(arr.size(), false);
    visited[start] = true;

    while (!q.empty()) {
        int z = q.front();
        q.pop();

        for (int neighbor : arr[z].neighbors) {
            // Pomijamy odwiedzone lub zalane miejsca
            if (visited[neighbor] || arr[neighbor].height < water_level) {
                continue;
            }

            if (neighbor == end) {
                return true;
            }

            q.push(neighbor);
            visited[neighbor] = true;
        }
    }
    return false; // ścieżka nie istnieje
}

long max(long& a, long& b) {
    return (a > b) ? a : b;
}

long min(long& a, long& b) {
    return (a < b) ? a : b;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int szczyty, krawedzie;
    std::cin >> szczyty >> krawedzie;

    vector<Node> graph(szczyty);

    for (int i = 0; i < szczyty; ++i) {
        std::cin >> graph[i].height;
    }

    for (int i = 0; i < krawedzie; i++) {
        int a, b;
        std::cin >> a >> b;
        graph[a].neighbors.push_back(b);
        graph[b].neighbors.push_back(a);
    }

    // wczytywanie punktu początkowego i końcowego
    int start, end;
    std::cin >> start >> end;

    // wczytywanie zmian poziomu wody
    long current_water_level = 0;
    int zmiany_poziomu_wody;
    std::cin >> zmiany_poziomu_wody;

    long max_yes = -10000000L;  // maksymalny poziom przy którym była ścieżka
    long min_no = 10000000L; // minimalny poziom przy którym nie było ścieżki

    for (int i = 0; i < zmiany_poziomu_wody; i++) {
        int change;
        std::cin >> change;
        current_water_level += change;

        bool result;

        // Jeśli poziom <= max_yes to na pewno jest ściezka (mniej wody = więcej dostępnych miejsc)
        if (current_water_level <= max_yes) {
            result = true;
        } else if (current_water_level >= min_no) { // Jeśli poziom >= min_no to na pewno nie ma ścieżki
            result = false;
        } else {
            result = bfs(graph, start, end, current_water_level);

            if (result) {
                max_yes = max(max_yes, current_water_level);
            } else {
                min_no = min(min_no, current_water_level);
            }
        }

        std::cout << (result ? "TAK\n" : "NIE\n");
    }

    return 0;
}