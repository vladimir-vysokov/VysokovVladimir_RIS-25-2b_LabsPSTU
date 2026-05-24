// demo.cpp - standalone console demo (no Qt required)
// Compile: g++ -std=c++17 demo.cpp -o demo && ./demo
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <limits>
#include <iomanip>
#include <algorithm>

const int INF = std::numeric_limits<int>::max() / 2;

// Graph from image: 6 vertices (1-6), directed weighted
// Index: 0=v1, 1=v2, 2=v3, 3=v4, 4=v5, 5=v6
const int N = 6;
const std::string NAMES[N] = {"1","2","3","4","5","6"};
int adj[N][N] = {
//    1   2   3   4   5   6
    { 0,  0,  0,  0,  0,  0},  // from 1
    {28,  0,  0, 20,  0,  0},  // from 2
    {13,  0,  0,  0,  0,  0},  // from 3
    {15, 39,  0,  0,  0, 31},  // from 4
    { 0, 21, 30,  0,  0,  0},  // from 5
    {18,  0,  0,  0,  0,  0},  // from 6
};

void printHeader(const std::string& title) {
    std::cout << "\n" << std::string(60,'=') << "\n";
    std::cout << "  " << title << "\n";
    std::cout << std::string(60,'=') << "\n";
}

void printMatrix(const std::vector<std::vector<int>>& mat, const std::string& label) {
    std::cout << "\n" << label << ":\n";
    std::cout << std::setw(5) << " ";
    for (int j = 0; j < N; j++) std::cout << std::setw(6) << NAMES[j];
    std::cout << "\n";
    for (int i = 0; i < N; i++) {
        std::cout << std::setw(4) << NAMES[i] << " ";
        for (int j = 0; j < N; j++) {
            if (mat[i][j] == INF) std::cout << std::setw(6) << "INF";
            else std::cout << std::setw(6) << mat[i][j];
        }
        std::cout << "\n";
    }
}

// ─── BFS ───
void bfs(int start) {
    printHeader("BFS (Breadth-First Search) from vertex " + NAMES[start]);
    std::vector<bool> visited(N, false);
    std::vector<int> order;
    std::queue<int> q;
    q.push(start);
    visited[start] = true;
    std::cout << "Queue: [" << NAMES[start] << "]\n";
    while (!q.empty()) {
        int v = q.front(); q.pop();
        order.push_back(v);
        std::cout << "Visit " << NAMES[v] << " → neighbors: ";
        for (int u = 0; u < N; u++) {
            if (adj[v][u] && !visited[u]) {
                visited[u] = true;
                q.push(u);
                std::cout << NAMES[u] << "(w=" << adj[v][u] << ") ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\nBFS order: ";
    for (int v : order) std::cout << NAMES[v] << " ";
    std::cout << "\n";
}

// ─── DFS ───
void dfs(int start) {
    printHeader("DFS (Depth-First Search) from vertex " + NAMES[start]);
    std::vector<bool> visited(N, false);
    std::vector<int> order;
    std::stack<int> stk;
    stk.push(start);
    while (!stk.empty()) {
        int v = stk.top(); stk.pop();
        if (visited[v]) continue;
        visited[v] = true;
        order.push_back(v);
        std::cout << "Visit " << NAMES[v] << " → push neighbors: ";
        std::vector<int> nbrs;
        for (int u = 0; u < N; u++) if (adj[v][u] && !visited[u]) nbrs.push_back(u);
        for (int i = (int)nbrs.size()-1; i >= 0; i--) {
            stk.push(nbrs[i]);
            std::cout << NAMES[nbrs[i]] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\nDFS order: ";
    for (int v : order) std::cout << NAMES[v] << " ";
    std::cout << "\n";
}

// ─── DIJKSTRA ───
void dijkstra(int start) {
    printHeader("Dijkstra from vertex " + NAMES[start]);
    std::vector<int> dist(N, INF), prev(N, -1);
    dist[start] = 0;
    using pii = std::pair<int,int>;
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
    pq.push({0, start});
    std::vector<bool> settled(N, false);

    while (!pq.empty()) {
        auto [d, v] = pq.top(); pq.pop();
        if (settled[v]) continue;
        settled[v] = true;
        std::cout << "Settle " << NAMES[v] << " (d=" << d << ")";
        for (int u = 0; u < N; u++) {
            if (adj[v][u] && !settled[u]) {
                int nd = dist[v] + adj[v][u];
                if (nd < dist[u]) {
                    dist[u] = nd;
                    prev[u] = v;
                    pq.push({nd, u});
                    std::cout << "  relax→" << NAMES[u] << "=" << nd;
                }
            }
        }
        std::cout << "\n";
    }
    std::cout << "\nShortest distances from " << NAMES[start] << ":\n";
    for (int i = 0; i < N; i++) {
        std::cout << "  to " << NAMES[i] << ": ";
        if (dist[i] == INF) std::cout << "INF";
        else std::cout << dist[i];
        // Reconstruct path
        if (dist[i] != INF) {
            std::vector<int> path;
            for (int v = i; v != -1; v = prev[v]) path.push_back(v);
            std::reverse(path.begin(), path.end());
            std::cout << "  (path: ";
            for (int k = 0; k < (int)path.size(); k++) {
                if (k) std::cout << "→";
                std::cout << NAMES[path[k]];
            }
            std::cout << ")";
        }
        std::cout << "\n";
    }
}

// ─── FLOYD-WARSHALL ───
void floyd() {
    printHeader("Floyd-Warshall – All Pairs Shortest Paths");

    // Build initial D0
    std::vector<std::vector<int>> D(N, std::vector<int>(N, INF));
    std::vector<std::vector<int>> nxt(N, std::vector<int>(N, -1));
    for (int i = 0; i < N; i++) D[i][i] = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (i != j && adj[i][j]) { D[i][j] = adj[i][j]; nxt[i][j] = j; }

    printMatrix(D, "D0 (initial)");

    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (D[i][k] != INF && D[k][j] != INF && D[i][k]+D[k][j] < D[i][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                    nxt[i][j] = nxt[i][k];
                }
        printMatrix(D, "D" + std::to_string(k+1) + " (after intermediate vertex " + NAMES[k] + ")");
    }

    // Path reconstruction example: 5→1 (indices 4→0)
    std::cout << "\n--- Path reconstruction (Floyd) ---\n";
    std::vector<std::pair<int,int>> queries = {{4,0},{4,1},{4,2},{4,3},{4,5}};
    for (auto [s,e] : queries) {
        std::cout << "Path " << NAMES[s] << "→" << NAMES[e] << ": ";
        if (nxt[s][e] == -1) { std::cout << "no path\n"; continue; }
        int cur = s;
        std::vector<int> path;
        path.push_back(cur);
        while (cur != e) { cur = nxt[cur][e]; path.push_back(cur); }
        for (int k = 0; k < (int)path.size(); k++) {
            if (k) std::cout << "→";
            std::cout << NAMES[path[k]];
        }
        std::cout << "  cost=" << D[s][e] << "\n";
    }
}

int main() {
    std::cout << "Graph Algorithms Demo\n";
    std::cout << "Graph from Lab Work #2 (directed, weighted)\n";
    std::cout << "Vertices: 1,2,3,4,5,6\n";
    std::cout << "START VERTEX: 5 (index 4)\n";

    // Print adjacency matrix
    std::vector<std::vector<int>> adjVec(N, std::vector<int>(N));
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) adjVec[i][j] = adj[i][j];
    printMatrix(adjVec, "Adjacency Matrix (D0 initial)");

    bfs(4);   // start from vertex 5
    dfs(4);   // start from vertex 5
    dijkstra(4); // start from vertex 5
    floyd();

    return 0;
}
