#include <algorithm>
#include <iostream>
#include <vector>

std::vector<std::vector<int>> tree;
std::vector<int> a;

void Build(int v, int tl, int tr) {
  if (tl == tr) {
    tree[v].push_back(a[tl]);
    return;
  }
  int tm = (tl + tr) / 2;
  Build(v * 2 + 1, tm + 1, tr);
  Build(v * 2, tl, tm);
  tree[v].clear();
  int sz_l = tree[v * 2].size();
  for (int j = 0; j < sz_l; ++j) {
    tree[v].push_back(tree[v * 2][j]);
  }
  int sz_r = tree[v * 2 + 1].size();
  for (int j = 0; j < sz_r; ++j) {
    tree[v].push_back(tree[v * 2 + 1][j]);
  }
  std::sort(tree[v].begin(), tree[v].end());
}

int Get(int v, int tl, int tr, int l, int r, int val) {
  if (l > tr || r < tl) {
    return 0;
  }
  if (tl >= l && tr <= r) {
    return std::upper_bound(tree[v].begin(), tree[v].end(), val) -
           tree[v].begin();
  }
  int tm = (tl + tr) / 2;
  int res_r = Get(v * 2 + 1, tm + 1, tr, l, r, val);
  int res_l = Get(v * 2, tl, tm, l, r, val);
  return res_r + res_l;
}

int Query(int l, int r, int x, int y) {
  int total_l_y = Get(1, 1, (int)a.size() - 1, l, r, y);
  int total_l_x;
  if (x == 1) {
    total_l_x = 0;
  } else {
    total_l_x = Get(1, 1, (int)a.size() - 1, l, r, x - 1);
  }
  return total_l_y - total_l_x;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int n = 0;
  int q = 0;
  std::cin >> n >> q;
  a = std::vector<int>(n + 1);
  for (int i = 1; i <= n; ++i) {
    std::cin >> a[i];
  }
  tree = std::vector<std::vector<int>>(4 * (n + 1));
  Build(1, 1, n);
  for (int i = 0; i < q; ++i) {
    int l = 0;
    int r = 0;
    int x = 0;
    int y = 0;
    std::cin >> l >> r >> x >> y;
    std::cout << Query(l, r, x, y) << '\n';
  }
}
