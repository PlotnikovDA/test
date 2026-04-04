#include <iostream>
#include <vector>

const long long cInf = 1000000000000000000LL;
long long exact = -cInf;
long long st_val = 0;

void Bfs(std::vector<std::vector<int>>& g, std::vector<std::vector<int>>& gw,
         std::vector<int>& used, std::vector<int>& sign_v,
         std::vector<long long>& val_v, std::vector<int>& q) {
  int head = 0;
  q.push_back(1);
  used[1] = 1;
  sign_v[1] = 1;
  val_v[1] = 0;
  while (head < (int)q.size()) {
    int v = q[head];
    ++head;
    for (size_t i = 0; i < g[v].size(); ++i) {
      int to = g[v][i];
      long long w = gw[v][i];
      if (used[to] == 0) {
        used[to] = 1;
        sign_v[to] = -sign_v[v];
        val_v[to] = w - val_v[v];
        q.push_back(to);
      } else if (sign_v[to] == sign_v[v]) {
        long long diff = w - val_v[v] - val_v[to];
        exact = diff / (sign_v[v] + sign_v[to]);
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
  std::vector<std::vector<int>> g(n + 1);
  std::vector<std::vector<int>> gw(n + 1);
  std::vector<int> used(n + 1, 0);
  std::vector<int> sign_v(n + 1, 0);
  std::vector<long long> val_v(n + 1, 0);
  std::vector<int> q;
  for (int i = 0; i < m; ++i) {
    int u = 0;
    int v = 0;
    int w = 0;
    std::cin >> u >> v >> w;
    g[u].push_back(v);
    gw[u].push_back(w);
    g[v].push_back(u);
    gw[v].push_back(w);
  }
  Bfs(g, gw, used, sign_v, val_v, q);
  if (exact != -cInf) {
    st_val = exact;
  } else {
    long long min_a = cInf;
    long long min_b = cInf;
    for (int i = 1; i <= n; ++i) {
      if (sign_v[i] == 1) {
        if (val_v[i] < min_a) {
          min_a = val_v[i];
        }
      } else {
        if (val_v[i] < min_b) {
          min_b = val_v[i];
        }
      }
    }
    st_val = 1 - min_a;
    int k = 1;
    std::vector<int> chk_p(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
      long long ans = sign_v[i] * st_val + val_v[i];
      if (ans < 1 || ans > n) {
        k = 0;
        break;
      }
      if (chk_p[ans] == 1) {
        k = 0;
        break;
      }
      chk_p[ans] = 1;
    }
    if (k == 0) {
      st_val = min_b - 1;
    }
  }
  for (int i = 1; i <= n; ++i) {
    long long ans = sign_v[i] * st_val + val_v[i];
    std::cout << ans << " ";
  }
  std::cout << "\n";
}
