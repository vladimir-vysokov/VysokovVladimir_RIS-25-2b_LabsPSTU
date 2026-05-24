#include "graph.h"
#include <sstream>
#include <iomanip>

Graph::Graph() : n(0) {}

Graph::Graph(int n) : n(n), names(n), adj(n, std::vector<int>(n, 0)) {
    for (int i = 0; i < n; i++) names[i] = std::to_string(i + 1);
}

void Graph::addVertex(const std::string& name) {
    n++;
    names.push_back(name);
    for (auto& row : adj) row.push_back(0);
    adj.push_back(std::vector<int>(n, 0));
}

bool Graph::removeVertex(int idx) {
    if (idx < 0 || idx >= n) return false;
    n--;
    names.erase(names.begin() + idx);
    adj.erase(adj.begin() + idx);
    for (auto& row : adj) row.erase(row.begin() + idx);
    return true;
}

bool Graph::addEdge(int from, int to, int weight) {
    if (from < 0 || from >= n || to < 0 || to >= n || from == to) return false;
    adj[from][to] = weight;
    return true;
}

bool Graph::removeEdge(int from, int to) {
    if (from < 0 || from >= n || to < 0 || to >= n) return false;
    adj[from][to] = 0;
    return true;
}

bool Graph::setEdgeWeight(int from, int to, int weight) {
    if (from < 0 || from >= n || to < 0 || to >= n) return false;
    if (adj[from][to] == 0) return false;
    adj[from][to] = weight;
    return true;
}

void Graph::clear() {
    n = 0; names.clear(); adj.clear();
}

int Graph::vertexCount() const { return n; }

int Graph::edgeCount() const {
    int cnt = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (adj[i][j] != 0) cnt++;
    return cnt;
}

std::string Graph::vertexName(int idx) const {
    if (idx < 0 || idx >= n) return "";
    return names[idx];
}

void Graph::setVertexName(int idx, const std::string& name) {
    if (idx >= 0 && idx < n) names[idx] = name;
}

bool Graph::hasEdge(int from, int to) const {
    if (from < 0 || from >= n || to < 0 || to >= n) return false;
    return adj[from][to] != 0;
}

int Graph::edgeWeight(int from, int to) const {
    if (from < 0 || from >= n || to < 0 || to >= n) return 0;
    return adj[from][to];
}

const std::vector<std::vector<int>>& Graph::adjacencyMatrix() const { return adj; }

void Graph::setAdjacencyMatrix(const std::vector<std::vector<int>>& mat) {
    int sz = (int)mat.size();
    adj = mat;
    n = sz;
    while ((int)names.size() < n)
        names.push_back(std::to_string(names.size() + 1));
    names.resize(n);
}

// ═══════════════════════════════════════════
//  ОБХОД В ШИРИНУ (BFS)
// ═══════════════════════════════════════════
Graph::TraversalResult Graph::bfs(int start) const {
    TraversalResult res;
    res.parent.assign(n, -1);
    std::vector<bool> visited(n, false);
    std::queue<int> q;
    q.push(start);
    visited[start] = true;

    std::ostringstream ss;
    ss << "=== Обход в ширину (BFS) ===\n";
    ss << "Начальная вершина: " << names[start] << "\n";
    ss << "Начальная очередь: [" << names[start] << "]\n";
    res.steps.push_back(ss.str());

    while (!q.empty()) {
        int v = q.front(); q.pop();
        res.visitOrder.push_back(v);

        std::ostringstream st;
        st << "Посещаем вершину " << names[v] << "\n";
        st << "  Соседи: ";

        bool hasNeighbors = false;
        for (int u = 0; u < n; u++) {
            if (adj[v][u] != 0) {
                hasNeighbors = true;
                st << names[u] << "(вес=" << adj[v][u] << ") ";
                if (!visited[u]) {
                    visited[u] = true;
                    res.parent[u] = v;
                    q.push(u);
                    st << "[добавлен в очередь]  ";
                } else {
                    st << "[уже посещена]  ";
                }
            }
        }
        if (!hasNeighbors) st << "нет исходящих рёбер";

        // Состояние очереди
        std::queue<int> tmp = q;
        st << "\n  Очередь сейчас: [";
        bool first = true;
        while (!tmp.empty()) {
            if (!first) st << ", ";
            st << names[tmp.front()];
            tmp.pop();
            first = false;
        }
        st << "]";

        res.steps.push_back(st.str());
    }

    std::ostringstream fin;
    fin << "─────────────────────────────\n";
    fin << "BFS завершён.\nПорядок посещения вершин: ";
    for (int v : res.visitOrder) fin << names[v] << " → ";
    // Убираем последнюю стрелку
    std::string s = fin.str();
    if (s.size() >= 4) s = s.substr(0, s.size() - 4);
    res.steps.push_back(s);
    return res;
}

// ═══════════════════════════════════════════
//  ОБХОД В ГЛУБИНУ (DFS)
// ═══════════════════════════════════════════
Graph::TraversalResult Graph::dfs(int start) const {
    TraversalResult res;
    res.parent.assign(n, -1);
    std::vector<bool> visited(n, false);
    std::stack<int> stk;
    stk.push(start);

    std::ostringstream ss;
    ss << "=== Обход в глубину (DFS) ===\n";
    ss << "Начальная вершина: " << names[start] << "\n";
    ss << "Начальный стек: [" << names[start] << "]\n";
    res.steps.push_back(ss.str());

    while (!stk.empty()) {
        int v = stk.top(); stk.pop();
        if (visited[v]) continue;
        visited[v] = true;
        res.visitOrder.push_back(v);

        std::ostringstream st;
        st << "Посещаем вершину " << names[v] << "\n";
        st << "  Добавляем в стек непосещённых соседей: ";

        std::vector<int> nbrs;
        for (int u = 0; u < n; u++)
            if (adj[v][u] != 0 && !visited[u]) nbrs.push_back(u);

        if (nbrs.empty()) {
            st << "нет новых соседей";
        } else {
            for (int i = (int)nbrs.size() - 1; i >= 0; i--) {
                stk.push(nbrs[i]);
                if (res.parent[nbrs[i]] == -1) res.parent[nbrs[i]] = v;
                st << names[nbrs[i]] << " ";
            }
        }

        // Состояние стека
        std::stack<int> tmp = stk;
        std::vector<int> sv;
        while (!tmp.empty()) { sv.push_back(tmp.top()); tmp.pop(); }
        st << "\n  Стек сейчас: [";
        for (int i = (int)sv.size() - 1; i >= 0; i--) {
            st << names[sv[i]];
            if (i) st << ", ";
        }
        st << "]";

        res.steps.push_back(st.str());
    }

    std::ostringstream fin;
    fin << "─────────────────────────────\n";
    fin << "DFS завершён.\nПорядок посещения вершин: ";
    for (int v : res.visitOrder) fin << names[v] << " → ";
    std::string s = fin.str();
    if (s.size() >= 4) s = s.substr(0, s.size() - 4);
    res.steps.push_back(s);
    return res;
}

// ═══════════════════════════════════════════
//  АЛГОРИТМ ДЕЙКСТРЫ
// ═══════════════════════════════════════════
Graph::ShortestPathResult Graph::dijkstra(int start) const {
    ShortestPathResult res;
    res.dist.assign(n, INF);
    res.prev.assign(n, -1);
    res.dist[start] = 0;

    using pii = std::pair<int,int>;
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
    pq.push({0, start});

    std::ostringstream init;
    init << "=== Алгоритм Дейкстры ===\n";
    init << "Начальная вершина: " << names[start] << "\n";
    init << "Начальные расстояния: до всех вершин = INF,\n";
    init << "  кроме " << names[start] << " = 0\n";
    res.steps.push_back(init.str());

    std::vector<bool> settled(n, false);

    while (!pq.empty()) {
        auto [d, v] = pq.top(); pq.pop();
        if (settled[v]) continue;
        settled[v] = true;

        std::ostringstream st;
        st << "Фиксируем вершину " << names[v]
           << "  (кратчайшее расстояние = " << d << ")\n";
        st << "  Релаксация исходящих рёбер:\n";

        bool anyEdge = false;
        for (int u = 0; u < n; u++) {
            if (adj[v][u] != 0 && !settled[u]) {
                anyEdge = true;
                int nd = res.dist[v] + adj[v][u];
                st << "    " << names[v] << " → " << names[u]
                   << "  вес=" << adj[v][u]
                   << "  новое=" << nd
                   << "  старое=";
                if (res.dist[u] == INF) st << "INF";
                else                    st << res.dist[u];

                if (nd < res.dist[u]) {
                    res.dist[u] = nd;
                    res.prev[u] = v;
                    pq.push({nd, u});
                    st << "  → ОБНОВЛЕНО";
                } else {
                    st << "  (не улучшилось)";
                }
                st << "\n";
            }
        }
        if (!anyEdge) st << "    нет непосещённых соседей\n";

        res.steps.push_back(st.str());
    }

    std::ostringstream fin;
    fin << "─────────────────────────────\n";
    fin << "Дейкстра завершён.\n";
    fin << "Кратчайшие расстояния от вершины " << names[start] << ":\n";
    for (int i = 0; i < n; i++) {
        fin << "  до вершины " << names[i] << ": ";
        if (res.dist[i] == INF) fin << "недостижима (INF)";
        else                    fin << res.dist[i];
        fin << "\n";
    }
    res.steps.push_back(fin.str());
    return res;
}

std::vector<int> Graph::getPath(const std::vector<int>& prev, int to) const {
    std::vector<int> path;
    for (int v = to; v != -1; v = prev[v]) path.push_back(v);
    std::reverse(path.begin(), path.end());
    return path;
}

// ═══════════════════════════════════════════
//  АЛГОРИТМ ФЛОЙДА–УОРШЕЛЛА
// ═══════════════════════════════════════════
Graph::FloydResult Graph::floyd() const {
    FloydResult res;
    int sz = n;

    res.dist.assign(sz, std::vector<int>(sz, INF));
    res.next.assign(sz, std::vector<int>(sz, -1));

    for (int i = 0; i < sz; i++) res.dist[i][i] = 0;
    for (int i = 0; i < sz; i++)
        for (int j = 0; j < sz; j++)
            if (i != j && adj[i][j] != 0) {
                res.dist[i][j] = adj[i][j];
                res.next[i][j] = j;
            }

    res.initialDist = res.dist;

    // ── D0 ──
    std::ostringstream d0;
    d0 << "=== Алгоритм Флойда–Уоршелла ===\n\n";
    d0 << "D0 — начальная матрица расстояний:\n";
    d0 << "  (значения берутся из матрицы смежности;\n";
    d0 << "   INF = прямого ребра нет, 0 = та же вершина)\n\n";
    d0 << "     ";
    for (int j = 0; j < sz; j++) d0 << std::setw(6) << names[j];
    d0 << "\n";
    for (int i = 0; i < sz; i++) {
        d0 << std::setw(4) << names[i] << " ";
        for (int j = 0; j < sz; j++) {
            if (res.dist[i][j] == INF) d0 << std::setw(6) << "INF";
            else                        d0 << std::setw(6) << res.dist[i][j];
        }
        d0 << "\n";
    }
    res.steps.push_back(d0.str());

    // ── Итерации ──
    for (int k = 0; k < sz; k++) {
        bool anyUpdate = false;
        std::vector<std::vector<int>> prev_dist = res.dist;

        for (int i = 0; i < sz; i++)
            for (int j = 0; j < sz; j++)
                if (res.dist[i][k] != INF && res.dist[k][j] != INF) {
                    int nd = res.dist[i][k] + res.dist[k][j];
                    if (nd < res.dist[i][j]) {
                        res.dist[i][j] = nd;
                        res.next[i][j] = res.next[i][k];
                        anyUpdate = true;
                    }
                }

        std::ostringstream sk;
        sk << "D" << (k + 1)
           << " — промежуточная вершина: " << names[k] << "\n";
        sk << "  (проверяем: путь через " << names[k]
           << " короче прямого?)\n\n";
        sk << "     ";
        for (int j = 0; j < sz; j++) sk << std::setw(6) << names[j];
        sk << "\n";
        for (int i = 0; i < sz; i++) {
            sk << std::setw(4) << names[i] << " ";
            for (int j = 0; j < sz; j++) {
                bool upd = (res.dist[i][j] != prev_dist[i][j]);
                if (res.dist[i][j] == INF) sk << std::setw(6) << "INF";
                else                        sk << std::setw(6) << res.dist[i][j];
                sk << (upd ? "*" : " ");   // * = ячейка обновлена
            }
            sk << "\n";
        }
        sk << (anyUpdate ? "  (* — ячейки, которые улучшились на этом шаге)\n"
                         : "  (изменений нет)\n");
        res.steps.push_back(sk.str());
    }

    // ── Итоговая матрица ──
    std::ostringstream fin;
    fin << "─────────────────────────────\n";
    fin << "Флойд завершён.\n";
    fin << "Итоговая матрица кратчайших расстояний:\n\n";
    fin << "     ";
    for (int j = 0; j < sz; j++) fin << std::setw(6) << names[j];
    fin << "\n";
    for (int i = 0; i < sz; i++) {
        fin << std::setw(4) << names[i] << " ";
        for (int j = 0; j < sz; j++) {
            if (res.dist[i][j] == INF) fin << std::setw(6) << "INF";
            else                        fin << std::setw(6) << res.dist[i][j];
            fin << " ";
        }
        fin << "\n";
    }
    res.steps.push_back(fin.str());
    return res;
}

std::vector<int> Graph::floydPath(const FloydResult& res, int from, int to) const {
    if (res.next[from][to] == -1) return {};
    std::vector<int> path;
    path.push_back(from);
    int cur = from;
    while (cur != to) {
        cur = res.next[cur][to];
        if (cur == -1) return {};
        path.push_back(cur);
    }
    return path;
}

// ═══════════════════════════════════════════
//  ГРАФ ПО УМОЛЧАНИЮ (из методички, вариант)
//  Вершины 1–6, ориентированный взвешенный
// ═══════════════════════════════════════════
void Graph::loadDefaultGraph() {
    clear();
    n = 6;
    names = {"1","2","3","4","5","6"};
    adj.assign(6, std::vector<int>(6, 0));

    adj[4][1] = 21;  // 5 → 2  (вес 21)
    adj[1][3] = 20;  // 2 → 4  (вес 20)
    adj[4][3] = 39;  // 5 → 4  (вес 39)
    adj[3][4] = 39;  // 4 → 5  (вес 39)
    adj[1][0] = 28;  // 2 → 1  (вес 28)
    adj[0][3] = 15;  // 1 → 4  (вес 15, НЕ 4→1!)
    adj[3][5] = 31;  // 4 → 6  (вес 31)
    adj[0][2] = 13;  // 1 → 3  (вес 13, НЕ 3→1!)
    adj[2][4] = 30;  // 3 → 5  (вес 30, НЕ 5→3!)
    adj[5][0] = 18;  // 6 → 1  (вес 18)
}
