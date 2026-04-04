#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

int tmr_v = 0;
std::vector<int> t_in;
std::vector<int> l_w;
std::vector<int> u_f;
std::vector<int> ans_b;

void Dfs(int v, int p_edge,
         const std::vector<std::vector<std::pair<int, int>>>& g) {
  u_f[v] = 1;
  tmr_v = tmr_v + 1;
  t_in[v] = tmr_v;
  l_w[v] = tmr_v;
  for (size_t i = 0; i < g[v].size(); ++i) {
    int to = g[v][i].first;
    int id = g[v][i].second;
    if (id == p_edge) {
      continue;
    }
    if (u_f[to] == 1) {
      if (t_in[to] < l_w[v]) {
        l_w[v] = t_in[to];
      }
    } else {
      Dfs(to, id, g);
      if (l_w[to] < l_w[v]) {
        l_w[v] = l_w[to];
      }
      if (l_w[to] > t_in[v]) {
        ans_b.push_back(id);
      }
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<std::vector<std::pair<int, int>>> g(n + 1);
  for (int i = 1; i <= m; ++i) {
    int u = 0;
    int v = 0;
    std::cin >> u >> v;
    g[u].push_back(std::make_pair(v, i));
    g[v].push_back(std::make_pair(u, i));
  }
  t_in.resize(n + 1, 0);
  l_w.resize(n + 1, 0);
  u_f.resize(n + 1, 0);
  for (int i = 1; i <= n; ++i) {
    if (u_f[i] == 0) {
      Dfs(i, -1, g);
    }
  }
  std::sort(ans_b.begin(), ans_b.end());
  std::cout << ans_b.size() << "\n";
  for (size_t i = 0; i < ans_b.size(); ++i) {
    std::cout << ans_b[i] << " ";
  }
  std::cout << "\n";
}
