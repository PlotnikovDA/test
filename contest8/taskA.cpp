#include <iostream>
#include <queue>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int t = 0;
  const long long cC = 2009000999;
  std::cin >> t;
  while (t != 0) {
    --t;
    int n = 0;
    int m = 0;
    std::cin >> n >> m;
    std::vector<std::vector<std::pair<int, int>>> adj(n);
    for (int i = 0; i < m; ++i) {
      int u = 0;
      int v = 0;
      int w = 0;
      std::cin >> u >> v >> w;
      adj[u].push_back({v, w});
      adj[v].push_back({u, w});
    }
    int s = 0;
    std::cin >> s;
    std::vector<int> dist(n, cC);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>>
        pq;
    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
      int d = pq.top().first;
      int u = pq.top().second;
      pq.pop();
      if (d > dist[u]) {
        continue;
      }
      for (const auto& edge : adj[u]) {
        int v = edge.first;
        int w = edge.second;
        if (dist[u] + w < dist[v]) {
          dist[v] = dist[u] + w;
          pq.push({dist[v], v});
        }
      }
    }
    for (int i = 0; i < n; ++i) {
      std::cout << dist[i];
      if (i < n - 1) {
        std::cout << " ";
      }
    }
    std::cout << "\n";
  }
}
