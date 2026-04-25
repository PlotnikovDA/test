#include <deque>
#include <iostream>
#include <sstream>
#include <string>

struct MinQueue {
  std::deque<long long> dq;
  std::deque<long long> dq_min;
  
  void enqueue(long long value) {
    dq.push_back(value);
    while (!dq_min.empty() && value < dq_min.back()) {
      dq_min.pop_back();
    }
    dq_min.push_back(value);
  }
  
  void dequeue() {
    if (dq.empty()) {
      std::cout << "error" << '\n';
      return;
    }
    std::cout << dq.front() << '\n';
    if (dq.front() == dq_min.front()) {
      dq_min.pop_front();
    }
    dq.pop_front();
  }
  
  void front() {
    if (dq.empty()) {
      std::cout << "error" << '\n';
      return;
    }
    std::cout << dq.front() << '\n';
  }
  
  void size() {
    std::cout << dq.size() << '\n';
  }
  
  void clear() {
    dq.clear();
    dq_min.clear();
  }
  
  void min() {
    if (dq_min.empty()) {
      std::cout << "error" << '\n';
      return;
    }
    std::cout << dq_min.front() << '\n';
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int n = 0;
  std::cin >> n;
  std::cin.ignore();
  MinQueue queue;
  std::string s;
  std::string x;
  long long value;
  for (int i = 0; i < n; ++i) {
    std::getline(std::cin, s);
    std::stringstream ss(s);
    ss >> x;
    if (x == "enqueue") {
      ss >> value;
      queue.enqueue(value);
      std::cout << "ok" << '\n';
    } else if (x == "dequeue") {
      queue.dequeue();
    } else if (x == "front") {
      queue.front();
    } else if (x == "size") {
      queue.size();
    } else if (x == "clear") {
      queue.clear();
      std::cout << "ok" << '\n';
    } else if (x == "min") {
      queue.min();
    }
  }
}
