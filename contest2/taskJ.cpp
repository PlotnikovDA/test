#include <iostream>
#include <string>
#include <vector>

void Siftup(std::vector<std::pair<long long, int>>& heap, std::vector<int>& ind,
            size_t v) {
  while (v > 0 && heap[v] < heap[(v - 1) / 2]) {
    std::swap(heap[v], heap[(v - 1) / 2]);
    std::swap(ind[heap[v].second], ind[heap[(v - 1) / 2].second]);
    v = (v - 1) / 2;
  }
}

void Siftdown(std::vector<std::pair<long long, int>>& heap,
              std::vector<int>& ind, size_t v) {
  size_t n = heap.size();
  while (2 * v + 1 < n) {
    size_t l = 2 * v + 1;
    size_t r = 2 * v + 2;
    size_t chldr = l;
    if (r < n && heap[r] < heap[l]) {
      chldr = r;
    }
    if (heap[v] > heap[chldr]) {
      std::swap(heap[v], heap[chldr]);
      std::swap(ind[heap[v].second], ind[heap[chldr].second]);
      v = chldr;
    } else {
      break;
    }
  }
}

void Dkey(std::vector<std::pair<long long, int>>& heap, std::vector<int>& ind,
          size_t v, long long dlt) {
  heap[ind[v]].first -= dlt;
  Siftup(heap, ind, ind[v]);
}

void Extractmin(std::vector<std::pair<long long, int>>& heap,
                std::vector<int>& ind) {
  std::swap(heap[0], heap.back());
  std::swap(ind[heap[0].second], ind[heap.back().second]);
  heap.pop_back();
  Siftdown(heap, ind, 0);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n = 0;
  std::cin >> n;
  std::cin.ignore();
  std::string s;
  std::vector<std::pair<long long, int>> heap;
  std::vector<int> ind(n);
  heap.reserve(n);
  long long value = 0;
  long long v = 0;
  for (int i = 0; i < n; ++i) {
    std::cin >> s;
    if (s == "insert") {
      std::cin >> value;
      ind[i] = heap.size();
      heap.push_back({value, i});
      Siftup(heap, ind, heap.size() - 1);
    }
    if (s == "getMin") {
      std::cout << heap[0].first << '\n';
    }
    if (s == "extractMin") {
      Extractmin(heap, ind);
    }
    if (s == "decreaseKey") {
      std::cin >> v;
      std::cin >> value;
      Dkey(heap, ind, v - 1, value);
    }
  }
}
