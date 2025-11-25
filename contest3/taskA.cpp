#include <algorithm>
#include <iostream>
#include <vector>

const long long cInf = 1000000000 + 7;

struct Node {
  int first_value;
  int first_index;
  int second_value;
  int second_index;
};

Node Comb(const Node& l, const Node& r) {
  Node res;
  if (l.first_value < r.first_value) {
    res.first_value = l.first_value;
    res.first_index = l.first_index;
    if (l.second_value < r.first_value) {
      res.second_value = l.second_value;
      res.second_index = l.second_index;
    } else {
      res.second_value = r.first_value;
      res.second_index = r.first_index;
    }
  } else {
    res.first_value = r.first_value;
    res.first_index = r.first_index;
    if (l.first_value < r.second_value) {
      res.second_value = l.first_value;
      res.second_index = l.first_index;
    } else {
      res.second_value = r.second_value;
      res.second_index = r.second_index;
    }
  }
  return res;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int n = 0;
  int q = 0;
  std::cin >> n >> q;
  std::vector<int> lg2(n + 1);
  lg2[1] = 0;
  for (int i = 2; i <= n; ++i) {
    lg2[i] = lg2[i >> 1] + 1;
  }
  int mx = lg2[n];
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  std::vector<std::vector<Node>> st(mx + 1, std::vector<Node>(n));
  for (int j = 0; j < n; ++j) {
    st[0][j].first_value = a[j];
    st[0][j].first_index = j;
    st[0][j].second_value = cInf;
    st[0][j].second_index = -1;
  }
  for (int i = 1; i <= mx; ++i) {
    int ln = (1 << (i - 1));
    for (int j = 0; j + ln < n; ++j) {
      st[i][j] = Comb(st[i - 1][j], st[i - 1][j + ln]);
    }
    for (int j = n - ln; j < n; ++j) {
      int start = std::min(n - 1, j + ln);
      st[i][j] = Comb(st[i - 1][j], st[i - 1][start]);
    }
  }
  for (int k = 0; k < q; ++k) {
    int l = 0;
    int r = 0;
    std::cin >> l >> r;
    --l;
    --r;
    int len = r - l + 1;
    int p = lg2[len];
    Node left = st[p][l];
    Node right = st[p][r - (1 << p) + 1];
    int mn_2 = 0;
    if (left.first_value < right.first_value) {
      mn_2 = std::min(left.second_value, right.first_value);
    } else if (right.first_value < left.first_value) {
      mn_2 = std::min(left.first_value, right.second_value);
    } else {
      if (left.first_index != right.first_index) {
        mn_2 = left.first_value;
      } else {
        mn_2 = std::min(left.second_value, right.second_value);
      }
    }
    std::cout << mn_2 << "\n";
  }
}
