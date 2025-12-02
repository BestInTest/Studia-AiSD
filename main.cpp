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

//przejście wszerz z ograniczeniem wysokości
bool bfs(vector<Node>& arr, int start, int end, int water_level) {
    if (arr[start].height < water_level || arr[end].height < water_level) {
        return false;
    }
    if (start == end) {
        return true;
    }

    queue<int> q;
    q.push(start);
    vector<bool> visited(arr.size());
    visited[start] = true;

    while (!q.empty()) {
        int z = q.front();
        //std::cout << z << "\n";
        q.pop();

        for (int neighbor : arr[z].neighbors) {
            //FIXME: >= czy > ?
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
        //std::cout << "Wierzchołek " << i << " ma wysokość " << graph[i].height << "\n";
    }

    for (int i = 0; i < krawedzie; i++) {
        int a, b;
        std::cin >> a;
        //std::cout << "a: " << a << "\n";

        // dodawanie sąsiada tylko jeśli jest podany
        if (std::cin >> b) {
            graph[a].neighbors.push_back(b);
        }
        //std::cout << "b: " << b << "\n";
    }

    // wczytywanie punktu początkowego i końcowego
    int start, end;
    std::cin >> start >> end;
    //std::cout << "Start: " << start << ", End: " << end << "\n";

    // wczytywanie zmian poziomu wody
    int current_water_level = 0;
    short zmiany_poziomu_wody;
    std::cin >> zmiany_poziomu_wody;

    // do przechowywania wyników dla różnych poziomów wody (może zawierać wartości ujemne)
    std::unordered_map<int, string> result_cache;

    for (int i = 0; i < zmiany_poziomu_wody; i++) {
        int change;
        std::cin >> change;
        current_water_level += change;
        //std::cout << "Aktualny poziom wody: " << current_water_level << "\n";

        if (result_cache[current_water_level].empty()) {
            string result = bfs(graph, start, end, current_water_level) ? "TAK\n" : "NIE\n";
            std::cout << result;
            result_cache[current_water_level] = result;
        } else {
            std::cout << result_cache[current_water_level];
        }
    }
}