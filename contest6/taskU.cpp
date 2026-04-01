#include <iostream>
#include <string>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int n = 0;
  std::cin >> n;
  std::vector<long long> g(n, 0);
  for (int i = 0; i < n; ++i) {
    std::string s;
    std::cin >> s;
    for (int j = 0; j < n; ++j) {
      if (s[j] == '1') {
        g[i] |= (1LL << j);
      }
    }
    g[i] |= (1LL << i);
  }
  int n1 = n / 2;
  int n2 = n - n1;
  std::vector<int> dp(1 << n1, -1);
  dp[0] = (1 << n2) - 1;
  int oldest_l = -1;
  for (int mask = 1; mask < (1 << n1); ++mask) {
    if (mask == (1 << (oldest_l + 1))) {
      ++oldest_l;
    }
    int v = oldest_l;
    int mask_without_v = mask ^ (1 << v);
    if (dp[mask_without_v] != -1) {
      int neighbors_in_l = g[v] & ((1 << n1) - 1);
      if ((mask_without_v & neighbors_in_l) == mask_without_v) {
        int neighbors_in_r = (g[v] >> n1) & ((1 << n2) - 1);
        dp[mask] = dp[mask_without_v] & neighbors_in_r;
      }
    }
  }
  std::vector<int> count_r(1 << n2, 0);
  count_r[0] = 1;
  int oldest_r = -1;
  for (int mask = 1; mask < (1 << n2); ++mask) {
    if (mask == (1 << (oldest_r + 1))) {
      ++oldest_r;
    }
    int v = oldest_r;
    int actual_v = n1 + v;
    int mask_without_v = mask ^ (1 << v);
    if (count_r[mask_without_v] == 1) {
      int neighbors_in_r = (g[actual_v] >> n1) & ((1 << n2) - 1);
      if ((mask_without_v & neighbors_in_r) == mask_without_v) {
        count_r[mask] = 1;
      }
    }
  }
  for (int i = 0; i < n2; ++i) {
    int half = 1 << i;
    int step = 1 << (i + 1);
    for (int mask = 0; mask < (1 << n2); mask += step) {
      for (int j = 0; j < half; ++j) {
        count_r[mask + half + j] += count_r[mask + j];
      }
    }
  }
  long long total_cliques = 0;
  for (int mask = 0; mask < (1 << n1); ++mask) {
    if (dp[mask] != -1) {
      total_cliques += count_r[dp[mask]];
    }
  }
  std::cout << total_cliques << "\n";
}
