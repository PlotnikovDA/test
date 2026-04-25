#include <iostream>
#include <vector>

int main() {
  int n = 0;
  std::cin >> n;
  std::vector<long long> dp(n + 1, 0);
  dp[0] = 1;
  long long ans = 0;
  for (int a = n; a >= 1; --a) {
    ans += dp[n - a];
    if (a == 1) {
      break;
    }
    for (int j = n; j >= a; --j) {
      dp[j] += dp[j - a];
    }
    int r1 = 2 * a - 1;
    if (r1 <= n) {
      for (int j = r1; j <= n; ++j) {
        dp[j] -= dp[j - r1];
      }
    }
    int r2 = 2 * a - 2;
    if (r2 > 0 && r2 <= n) {
      for (int j = r2; j <= n; ++j) {
        dp[j] -= dp[j - r2];
      }
    }
  }
  std::cout << ans << '\n';
}
