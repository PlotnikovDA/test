#include <algorithm>
#include <cmath>
#include <deque>
#include <iostream>
#include <string>

struct QueueWithMiddle {
  std::deque<int> dq;
  
  void add(int x) {
    dq.push_back(x);
  }
  
  void insert_middle(int x) {
    int total_size = dq.size();
    int in_pos = (total_size + 1) / 2;
    auto it = dq.begin();
    std::advance(it, in_pos);
    dq.insert(it, x);
  }
  
  int remove() {
    int front = dq.front();
    dq.pop_front();
    return front;
  }
};

int main() {
  int n = 0;
  std::cin >> n;
  std::cin.ignore();
  QueueWithMiddle queue;
  std::string s;
  for (int i = 0; i < n; ++i) {
    std::getline(std::cin, s);
    if (s[0] == '+') {
      int x = std::stoi(s.substr(2));
      queue.add(x);
    } else if (s[0] == '*') {
      int x = std::stoi(s.substr(2));
      queue.insert_middle(x);
    } else if (s[0] == '-') {
      std::cout << queue.remove() << '\n';
    }
  }
}
