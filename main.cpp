#include <iostream>

using std::string;

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

/*
 * kod przejścia wszerz z ograniczeniem głębokości/dystansu
 * bfs(vector<vector<int>>& arr, int start) {
 *     queue<int> q;
 *     q.push(start);
 *     vector<bool> visited(arr.size(), false);
 *     visited[start] = true;
 *     vector<int> dist(arr.size()-1);
 *     dist[start] = 0;
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
 *                 dist[neighbor] = dist[z] + 1;
 *             }
 *             // tutaj albo za nawiasem ponizej jakis if ma byc
 *         }
 *     }
 * }
 */

// bfs(vector<vector<int>>& graph, int start, int target, int max_depth)???


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
}