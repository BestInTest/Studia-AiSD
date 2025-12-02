#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

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

    std::unordered_map<long, bool> result_cache;

    for (int i = 0; i < zmiany_poziomu_wody; i++) {
        int change;
        std::cin >> change;
        current_water_level += change;

        bool result;
        // Sprawdzamy czy mamy już wynik dla tego poziomu wody
        if (result_cache.find(current_water_level) != result_cache.end()) {
            result = result_cache[current_water_level];
        } else {
            result = bfs(graph, start, end, current_water_level);
            result_cache[current_water_level] = result;
        }

        std::cout << (result ? "TAK\n" : "NIE\n");
    }

    return 0;
}