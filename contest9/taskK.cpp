#include <iostream>
#include <queue>
#include <vector>

std::vector<int> edge_to;
std::vector<long long> edge_cap;
std::vector<long long> edge_flow;
std::vector<long long> edge_cost;
std::vector<int> edge_rev;
std::vector<std::vector<int>> g;

const long long cInf = 2e18;

void AddEdge(int u, int v, long long cap, long long cost) {
  int id1 = edge_to.size();
  edge_to.push_back(v);
  edge_cap.push_back(cap);
  edge_flow.push_back(0);
  edge_cost.push_back(cost);
  edge_rev.push_back(id1 + 1);
  g[u].push_back(id1);
  int id2 = edge_to.size();
  edge_to.push_back(u);
  edge_cap.push_back(0);
  edge_flow.push_back(0);
  edge_cost.push_back(-cost);
  edge_rev.push_back(id1);
  g[v].push_back(id2);
}

bool Spfa(int s, int t, int n, std::vector<long long>& dist,
          std::vector<int>& p_edge) {
  for (int i = 0; i <= n; ++i) {
    dist[i] = cInf;
    p_edge[i] = -1;
  }
  std::vector<int> in_q(n + 1, 0);
  std::queue<int> q;
  dist[s] = 0;
  q.push(s);
  in_q[s] = 1;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    in_q[u] = 0;
    for (size_t i = 0; i < g[u].size(); ++i) {
      int id = g[u][i];
      int v = edge_to[id];
      if (edge_cap[id] - edge_flow[id] > 0 &&
          dist[u] + edge_cost[id] < dist[v]) {
        dist[v] = dist[u] + edge_cost[id];
        p_edge[v] = id;
        if (in_q[v] == 0) {
          q.push(v);
          in_q[v] = 1;
        }
      }
    }
  }
  return dist[t] != cInf;
}

long long Flow(int s, int t, int n) {
  long long total_cost = 0;
  std::vector<long long> dist(n + 1);
  std::vector<int> p_edge(n + 1);
  while (Spfa(s, t, n, dist, p_edge)) {
    long long push = cInf;
    int curr = t;
    while (curr != s) {
      int id = p_edge[curr];
      long long avail = edge_cap[id] - edge_flow[id];
      if (avail < push) {
        push = avail;
      }
      curr = edge_to[edge_rev[id]];
    }
    curr = t;
    while (curr != s) {
      int id = p_edge[curr];
      int rev_id = edge_rev[id];
      edge_flow[id] += push;
      edge_flow[rev_id] -= push;
      total_cost += push * edge_cost[id];
      curr = edge_to[rev_id];
    }
  }
  return total_cost;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  g.assign(n + 1, std::vector<int>());
  for (int i = 0; i < m; ++i) {
    int u = 0;
    int v = 0;
    long long c = 0;
    long long w = 0;
    std::cin >> u >> v >> c >> w;
    AddEdge(u, v, c, w);
  }
  std::cout << Flow(1, n, n) << "\n";
}
