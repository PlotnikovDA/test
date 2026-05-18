#include <iostream>
#include <vector>

bool Kyn(int v, std::vector<std::vector<int>>& g, std::vector<int>& used,
         std::vector<int>& mt) {
  if (used[v] == 1) {
    return false;
  }
  used[v] = 1;
  for (size_t i = 0; i < g[v].size(); ++i) {
    int to = g[v][i];
    if (mt[to] == 0 || Kyn(mt[to], g, used, mt)) {
      mt[to] = v;
      return true;
    }
  }
  return false;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int n = 0;
  int k = 0;
  std::cin >> n >> k;
  std::vector<std::vector<int>> g(n + 1);
  for (int i = 1; i <= n; ++i) {
    int to = 0;
    while (std::cin >> to && to != 0) {
      g[i].push_back(to);
    }
  }
  std::vector<int> mt(k + 1, 0);
  std::vector<int> used(n + 1, 0);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      used[j] = 0;
    }
    Kyn(i, g, used, mt);
  }
  int matches = 0;
  for (int i = 1; i <= k; ++i) {
    if (mt[i] != 0) {
      ++matches;
    }
  }
  std::cout << matches << "\n";
  for (int i = 1; i <= k; ++i) {
    if (mt[i] != 0) {
      std::cout << mt[i] << " " << i << "\n";
    }
  }
}
