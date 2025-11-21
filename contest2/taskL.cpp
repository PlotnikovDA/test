#include <iostream>
#include <vector>

struct DoubleHeap {
  std::vector<std::pair<long long, int>> mn_heap_;
  std::vector<std::pair<long long, int>> mx_heap_;
  std::vector<int> mn_pos_;
  std::vector<int> mx_pos_;
  int curr_s_;
  int n_id_;

  void MnSiftup(size_t v) {
    while (v > 0 && mn_heap_[v] < mn_heap_[(v - 1) / 2]) {
      std::swap(mn_heap_[v], mn_heap_[(v - 1) / 2]);
      std::swap(mn_pos_[mn_heap_[v].second],
                mn_pos_[mn_heap_[(v - 1) / 2].second]);
      v = (v - 1) / 2;
    }
  }

  void MnSiftdown(size_t v) {
    size_t n = mn_heap_.size();
    while (2 * v + 1 < n) {
      size_t l = 2 * v + 1;
      size_t r = 2 * v + 2;
      size_t chldr = l;
      if (r < n && mn_heap_[r] < mn_heap_[l]) {
        chldr = r;
      }
      if (mn_heap_[v] > mn_heap_[chldr]) {
        std::swap(mn_heap_[v], mn_heap_[chldr]);
        std::swap(mn_pos_[mn_heap_[v].second], mn_pos_[mn_heap_[chldr].second]);
        v = chldr;
      } else {
        break;
      }
    }
  }

  void MnErase(size_t v) {
    int id_rem = mn_heap_[v].second;
    std::swap(mn_heap_[v], mn_heap_.back());
    if (v < mn_heap_.size() - 1) {
      mn_pos_[mn_heap_[v].second] = v;
    }
    mn_pos_[id_rem] = -1;
    mn_heap_.pop_back();
    if (v < mn_heap_.size()) {
      if (v > 0 && mn_heap_[v].first < mn_heap_[(v - 1) / 2].first) {
        MnSiftup(v);
      } else {
        MnSiftdown(v);
      }
    }
  }

  void MxSiftup(size_t v) {
    while (v > 0 && mx_heap_[v] > mx_heap_[(v - 1) / 2]) {
      std::swap(mx_heap_[v], mx_heap_[(v - 1) / 2]);
      std::swap(mx_pos_[mx_heap_[v].second],
                mx_pos_[mx_heap_[(v - 1) / 2].second]);
      v = (v - 1) / 2;
    }
  }

  void MxSiftdown(size_t v) {
    size_t n = mx_heap_.size();
    while (2 * v + 1 < n) {
      size_t l = 2 * v + 1;
      size_t r = 2 * v + 2;
      size_t chldr = l;
      if (r < n && mx_heap_[r] > mx_heap_[l]) {
        chldr = r;
      }
      if (mx_heap_[v] < mx_heap_[chldr]) {
        std::swap(mx_heap_[v], mx_heap_[chldr]);
        std::swap(mx_pos_[mx_heap_[v].second], mx_pos_[mx_heap_[chldr].second]);
        v = chldr;
      } else {
        break;
      }
    }
  }

  void MxErase(size_t v) {
    int id_rem = mx_heap_[v].second;
    std::swap(mx_heap_[v], mx_heap_.back());
    if (v < mx_heap_.size() - 1) {
      mx_pos_[mx_heap_[v].second] = v;
    }
    mx_pos_[id_rem] = -1;
    mx_heap_.pop_back();
    if (v < mx_heap_.size()) {
      if (v > 0 && mx_heap_[v].first > mx_heap_[(v - 1) / 2].first) {
        MxSiftup(v);
      } else {
        MxSiftdown(v);
      }
    }
  }

  DoubleHeap(int max_q) : curr_s_(0), n_id_(0) {
    mn_pos_.resize(max_q, -1);
    mx_pos_.resize(max_q, -1);
    mn_heap_.reserve(max_q);
    mx_heap_.reserve(max_q);
  }

  void Ins(long long x) {
    int id = ++n_id_;
    mn_pos_[id] = mn_heap_.size();
    mn_heap_.push_back({x, id});
    MnSiftup(mn_heap_.size() - 1);
    mx_pos_[id] = mx_heap_.size();
    mx_heap_.push_back({x, id});
    MxSiftup(mx_heap_.size() - 1);
    ++curr_s_;
    std::cout << "ok" << '\n';
  }

  void Extractmn() {
    if (curr_s_ == 0) {
      std::cout << "error" << '\n';
    } else {
      long long min_val = mn_heap_[0].first;
      int id = mn_heap_[0].second;
      std::cout << min_val << '\n';
      int pos_in_max_heap = mx_pos_[id];
      MnErase(0);
      MxErase(pos_in_max_heap);
      --curr_s_;
    }
  }

  void Getmn() {
    if (curr_s_ == 0) {
      std::cout << "error" << '\n';
    } else {
      std::cout << mn_heap_[0].first << '\n';
    }
  }

  void Extractmx() {
    if (curr_s_ == 0) {
      std::cout << "error" << '\n';
    } else {
      long long max_val = mx_heap_[0].first;
      int id = mx_heap_[0].second;
      std::cout << max_val << '\n';
      int pos_in_min_heap = mn_pos_[id];
      MxErase(0);
      MnErase(pos_in_min_heap);
      --curr_s_;
    }
  }

  void Getmx() {
    if (curr_s_ == 0) {
      std::cout << "error" << '\n';
    } else {
      std::cout << mx_heap_[0].first << '\n';
    }
  }

  void Sz() const { std::cout << curr_s_ << '\n'; }

  void Clear() {
    mn_heap_.clear();
    mx_heap_.clear();
    curr_s_ = 0;
    std::cout << "ok" << '\n';
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n;
  const int cMN = 6;
  std::cin >> n;
  DoubleHeap heap_ds(n);
  for (int i = 0; i < n; ++i) {
    int val;
    std::cin >> val;
    if (val == 0) {
      long long x;
      std::cin >> x;
      heap_ds.Ins(x);
    } else if (val == 1) {
      heap_ds.Extractmn();
    } else if (val == 2) {
      heap_ds.Getmn();
    } else if (val == 3) {
      heap_ds.Extractmx();
    } else if (val == 4) {
      heap_ds.Getmx();
    } else if (val == 5) {
      heap_ds.Sz();
    } else if (val == cMN) {
      heap_ds.Clear();
    }
  }
}
