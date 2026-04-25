#include <algorithm>
#include <iostream>
#include <vector>

const int cMx = 400040;

std::vector<long long> tree_len(4 * cMx);
std::vector<int> cover(4 * cMx);
std::vector<int> ys;

void Update(int v, int tl, int tr, int l, int r, int val) {
  if (l > r) {
    return;
  }
  if (l == tl && r == tr) {
    cover[v] += val;
  } else {
    int tm = (tl + tr) / 2;
    Update(v * 2, tl, tm, l, std::min(r, tm), val);
    Update(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r, val);
  }
  if (cover[v] > 0) {
    tree_len[v] = static_cast<long long>(ys[tr + 1]) - ys[tl];
  } else {
    tree_len[v] = (tl == tr ? 0LL : tree_len[v * 2] + tree_len[v * 2 + 1]);
  }
}

struct Node {
  int x = 0;
  int ly = 0;
  int ry = 0;
  int sign = 0;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int n = 0;
  std::cin >> n;
  std::vector<int> x1(n);
  std::vector<int> y1(n);
  std::vector<int> x2(n);
  std::vector<int> y2(n);
  ys.reserve(2 * n);
  for (int i = 0; i < n; ++i) {
    std::cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
    ys.push_back(y1[i]);
    ys.push_back(y2[i]);
  }
  std::sort(ys.begin(), ys.end());
  auto last = std::unique(ys.begin(), ys.end());
  ys.erase(last, ys.end());
  int m = (int)ys.size();
  std::vector<Node> events;
  events.reserve(2 * n);
  for (int i = 0; i < n; ++i) {
    auto it1 = std::lower_bound(ys.begin(), ys.end(), y1[i]);
    int ly = (int)(it1 - ys.begin());
    auto it2 = std::lower_bound(ys.begin(), ys.end(), y2[i]);
    int ry = (int)(it2 - ys.begin()) - 1;
    if (ly <= ry && x1[i] < x2[i]) {
      events.push_back({x1[i], ly, ry, 1});
      events.push_back({x2[i], ly, ry, -1});
    }
  }
  std::sort(events.begin(), events.end(),
            [](const Node& a, const Node& b) { return a.x < b.x; });
  tree_len.assign(4 * cMx, 0LL);
  cover.assign(4 * cMx, 0);
  long long ans = 0;
  long long covered = 0;
  int prev_x = events.empty() ? 0 : events[0].x;
  for (size_t i = 0; i < events.size();) {
    int curr_x = events[i].x;
    ans += covered * 1LL * (curr_x - prev_x);
    size_t j = i;
    while (j < events.size() && events[j].x == curr_x) {
      Update(1, 0, m - 2, events[j].ly, events[j].ry, events[j].sign);
      ++j;
    }
    i = j;
    covered = tree_len[1];
    prev_x = curr_x;
  }
  std::cout << ans << '\n';
}
