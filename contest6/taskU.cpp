#include <iostream>
#include <string>
#include <vector>

const int cM = 55;
long long adj[cM];
int n_1 = 0;
std::vector<int> dp;
long long total = 0;

void Dfs(int idx, long long allowed_a, long long allowed_b) {
  if (idx == n_1) {
    total += dp[allowed_b];
    return;
  }
  Dfs(idx + 1, allowed_a, allowed_b);
  if (((allowed_a >> idx) & 1) != 0) {
    long long next_a = allowed_a & adj[idx];
    long long next_b = allowed_b & (adj[idx] >> n_1);
    Dfs(idx + 1, next_a, next_b);
  }
}

int main() {
  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::string s;
    std::cin >> s;
    adj[i] = 0;
    for (int j = 0; j < n; ++j) {
      if (s[j] == '1') {
        adj[i] |= (1LL << j);
      }
    }
    adj[i] |= (1LL << i);
  }
  n_1 = n / 2;
  long long k = n - n_1;
  dp.assign(1 << k, 0);
  dp[0] = 1;
  for (int i = 0; i < k; ++i) {
    int v = n_1 + i;
    long long neigh = (adj[v] >> n_1) & ((1LL << k) - 1);
    for (int mask = 0; mask < (1 << i); ++mask) {
      if (dp[mask] != 0) {
        if ((mask & neigh) == mask) {
          dp[mask | (1 << i)] = 1;
        }
      }
    }
  }
  for (int i = 0; i < k; ++i) {
    int half = 1 << i;
    int step = 1 << (i + 1);
    for (int mask = 0; mask < (1 << k); mask += step) {
      for (int j = 0; j < half; ++j) {
        dp[mask + half + j] += dp[mask + j];
      }
    }
  }
  Dfs(0, (1LL << n_1) - 1, (1LL << k) - 1);
  std::cout << total << "\n";
}
