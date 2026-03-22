#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

const int cInf = 1e9;

void ProcIns(std::vector<std::vector<int>>& dp, int start_j, int end_j) {
  int k = dp[0].size() - 1;
  for (int j = start_j; j < end_j; ++j) {
    for (int e = 0; e < k; ++e) {
      if (dp[j][e] != cInf) {
        dp[j + 1][e + 1] = std::min(dp[j + 1][e + 1], dp[j][e]);
      }
    }
  }
}

void ProcTrans(std::vector<std::vector<int>>& nxt_dp,
               const std::vector<std::vector<int>>& dp, int start_j, int end_j,
               char u_char, const std::string& v) {
  int m = v.length();
  int k = dp[0].size() - 1;
  for (int j = start_j; j <= end_j; ++j) {
    for (int e = 0; e <= k; ++e) {
      if (dp[j][e] == cInf) {
        continue;
      }
      if (e + 1 <= k) {
        nxt_dp[j][e + 1] = std::min(nxt_dp[j][e + 1], dp[j][e]);
      }
      if (j < m) {
        int cost = 1;
        if (u_char == v[j]) {
          cost = 0;
        }
        nxt_dp[j + 1][e] = std::min(nxt_dp[j + 1][e], dp[j][e] + cost);
        if (e + 1 <= k) {
          nxt_dp[j + 1][e + 1] = std::min(nxt_dp[j + 1][e + 1], dp[j][e]);
        }
      }
    }
  }
}

int main() {
  std::string u;
  std::string v;
  int k = 0;
  std::cin >> u >> v >> k;
  int n = u.length();
  int m = v.length();
  std::vector<std::vector<int>> dp(m + 1, std::vector<int>(k + 1, cInf));
  dp[0][0] = 0;
  for (int i = 0; i <= n; ++i) {
    int start_j = std::max(0, i - k - 2);
    int end_j = std::min(m, i + k + 2);
    ProcIns(dp, start_j, end_j);
    if (i == n) {
      break;
    }
    std::vector<std::vector<int>> nxt_dp(m + 1, std::vector<int>(k + 1, cInf));
    ProcTrans(nxt_dp, dp, start_j, end_j, u[i], v);
    dp = std::move(nxt_dp);
  }
  int ans = cInf;
  for (int e = 0; e <= k; ++e) {
    ans = std::min(ans, dp[m][e]);
  }
  if (ans == cInf) {
    std::cout << -1 << '\n';
  } else {
    std::cout << ans << '\n';
  }
}
