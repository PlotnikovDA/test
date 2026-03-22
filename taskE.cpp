#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<std::array<int, 3>> w(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> w[i][1];
  }
  for (int i = 0; i < n; ++i) {
    std::cin >> w[i][0];
    w[i][2] = i + 1;
  }
  std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      if (w[i - 1][1] <= j) {
        dp[i][j] =
            std::max(dp[i - 1][j], dp[i - 1][j - w[i - 1][1]] + w[i - 1][0]);
      } else {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }
  std::vector<int> ans;
  int cur_m = m;
  for (int i = n; i > 0; --i) {
    if (dp[i][cur_m] != dp[i - 1][cur_m]) {
      ans.push_back(w[i - 1][2]);
      cur_m -= w[i - 1][1];
    }
  }
  std::sort(ans.begin(), ans.end());
  for (size_t i = 0; i < ans.size(); ++i) {
    std::cout << ans[i] << '\n';
  }
}
