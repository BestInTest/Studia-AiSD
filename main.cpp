#include <iostream>
#include <vector>
#include <queue>

using std::string;
using std::vector;
using std::queue;

// zrobić (zmodyfikowane?) przejście wszerz
// trzeba ograniczyć liczbę przejść wszerz
// bfs?
// są różne sposoby ograniczania przejść wszerz
// nie dsu
/*
 * kod przejścia wszerz
 * bfs(vector<vector<int>>& arr, int start) {
 *     queue<int> q;
 *     q.push(start);
 *     vector<bool> visited(arr.size(), false);
 *     visited[start] = true;
 *
 *     while (!q.empty()) {
 *         int z = q.front();
 *         cout << z << "\n";
 *         q.pop();
 *
 *         for (int neighbor : arr[z]) {
 *             if (!visited[neighbor]) {
 *                 q.push(neighbor);
 *                 visited[neighbor] = true;
 *             }
 *         }
 *     }
 * }
 */

struct Node {
    int id = 0;
    int height = 0;
    vector<int> neighbors;
};

//przejście wszerz z ograniczeniem głębokości/dystansu
bool bfs(vector<Node>& arr, int start, int end, int water_level) {
    queue<int> q;
    q.push(start);
    vector<bool> visited(arr.size());
    visited[start] = true;

    while (!q.empty()) {
        int z = q.front();
        //std::cout << z << "\n";
        q.pop();

        for (int neighbor : arr[z].neighbors) {
            //std::cout << "Sprawdzam sąsiada: " << neighbor << "\n";
            if (!visited[neighbor]) {
                q.push(neighbor);
                visited[neighbor] = true;
            }
            //FIXME: >= czy > ?
            if (neighbor == end && arr[neighbor].height > water_level) {
                return true;
            }
        }
    }
    return false; // ścieżka nie istnieje
}

// bfs(vector<vector<int>>& graph, int start, int target, int max_depth)???


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int szczyty, krawedzie;
    std::cin >> szczyty >> krawedzie;

    vector<Node> graph(szczyty);

    for (int i = 0; i < szczyty; ++i) {
        //TODO: trzeba będzie posortować?
        graph[i].id = i;
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

    for (int i = 0; i < zmiany_poziomu_wody; i++) {
        int change;
        std::cin >> change;
        current_water_level += change;
        //std::cout << "Aktualny poziom wody: " << current_water_level << "\n";

        //TODO: jeżeli tutaj będzie wąskie gardło to może trzeba będzie zrobić tak żeby zapisywać (poprzednie) wyniki?
        bfs(graph, start, end, current_water_level) ? std::cout << "TAK\n" : std::cout << "NIE\n";
    }
}