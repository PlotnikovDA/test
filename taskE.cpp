#include <algorithm>
#include <iostream>
#include <vector>

struct Item {
    int c;
    int w;
    int id;
};

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<Item> items(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> items[i].w;
  }
  for (int i = 0; i < n; ++i) {
    std::cin >> items[i].c;
    items[i].id = i + 1;
  }
  std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      if (items[i - 1].w <= j) {
        dp[i][j] =
            std::max(dp[i - 1][j], dp[i - 1][j - items[i - 1].w] + items[i - 1].c);
      } else {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }
  std::vector<int> ans;
  int cur_m = m;
  for (int i = n; i > 0; --i) {
    if (dp[i][cur_m] != dp[i - 1][cur_m]) {
      ans.push_back(items[i - 1].id);
      cur_m -= items[i - 1].w;
    }
  }
  std::sort(ans.begin(), ans.end());
  for (size_t i = 0; i < ans.size(); ++i) {
    std::cout << ans[i] << '\n';
  }
}
