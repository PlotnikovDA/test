#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int n = 0;
  std::cin >> n;
  const int cC = 100000;
  std::vector<std::vector<int>> w(n, std::vector<int>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> w[i][j];
    }
  }
  std::vector<int> dist(n, 0);
  std::vector<int> p(n, -1);
  int x = -1;
  for (int i = 0; i < n; ++i) {
    x = -1;
    for (int u = 0; u < n; ++u) {
      for (int v = 0; v < n; ++v) {
        if (w[u][v] != cC) {
          if (dist[u] + w[u][v] < dist[v]) {
            dist[v] = dist[u] + w[u][v];
            p[v] = u;
            x = v;
          }
        }
      }
    }
  }
  if (x == -1) {
    std::cout << "NO\n";
  } else {
    std::cout << "YES\n";
    int y = x;
    for (int i = 0; i < n; ++i) {
      y = p[y];
    }
    std::vector<int> path;
    int cur = y;
    while (true) {
      path.push_back(cur);
      if (cur == y) {
        if (path.size() > 1) {
          break;
        }
      }
      cur = p[cur];
    }
    std::reverse(path.begin(), path.end());
    std::cout << path.size() << "\n";
    for (size_t i = 0; i < path.size(); ++i) {
      std::cout << path[i] + 1;
      if (i + 1 < path.size()) {
        std::cout << " ";
      }
    }
    std::cout << "\n";
  }
}
