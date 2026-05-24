#pragma once
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <queue>
#include <stack>
#include <functional>

const int INF = std::numeric_limits<int>::max() / 2;

struct Edge {
    int from, to, weight;
};

class Graph {
public:
    Graph();
    Graph(int n);

    // Graph editing
    void addVertex(const std::string& name);
    bool removeVertex(int idx);
    bool addEdge(int from, int to, int weight);
    bool removeEdge(int from, int to);
    bool setEdgeWeight(int from, int to, int weight);
    void clear();

    int vertexCount() const;
    int edgeCount() const;
    std::string vertexName(int idx) const;
    void setVertexName(int idx, const std::string& name);
    bool hasEdge(int from, int to) const;
    int edgeWeight(int from, int to) const;

    // Adjacency matrix
    const std::vector<std::vector<int>>& adjacencyMatrix() const;
    void setAdjacencyMatrix(const std::vector<std::vector<int>>& mat);

    // Algorithms
    // BFS from startVertex, returns visited order and parent map for path
    struct TraversalResult {
        std::vector<int> visitOrder;
        std::vector<int> parent;
        std::vector<std::string> steps; // step descriptions
    };

    TraversalResult bfs(int start) const;
    TraversalResult dfs(int start) const;

    // Dijkstra
    struct ShortestPathResult {
        std::vector<int> dist;
        std::vector<int> prev;
        std::vector<std::string> steps;
    };
    ShortestPathResult dijkstra(int start) const;
    std::vector<int> getPath(const std::vector<int>& prev, int to) const;

    // Floyd-Warshall
    struct FloydResult {
        std::vector<std::vector<int>> dist;   // distance matrix
        std::vector<std::vector<int>> next;   // next-hop matrix
        std::vector<std::vector<int>> initialDist; // D0
        std::vector<std::string> steps;
    };
    FloydResult floyd() const;
    std::vector<int> floydPath(const FloydResult& res, int from, int to) const;

    // Load the default graph from the image (variant graph)
    void loadDefaultGraph();

private:
    int n; // number of vertices
    std::vector<std::string> names;
    std::vector<std::vector<int>> adj; // adj[i][j] = weight, 0 = no edge, INF not used here
};
