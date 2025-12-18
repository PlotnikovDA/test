#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

const long long cPrime = 1000000007;
const int cTsz = 1000003;

struct HashTable {
  std::vector<int> table[cTsz];
  long long a;
  long long b;

  HashTable() {
    std::srand(std::time(0));
    a = (1LL * std::rand() * std::rand()) % (cPrime - 1);
    b = (1LL * std::rand() * std::rand()) % cPrime;
  }

  int Get(int x) const { return ((a * x + b) % cPrime) % cTsz; }

  bool Find(int x) {
    int h = Get(x);
    for (int val : table[h]) {
      if (val == x) {
        return true;
      }
    }
    return false;
  }

  void Insert(int x) {
    if (Find(x)) {
      return;
    }
    int h = Get(x);
    table[h].push_back(x);
  }

  void Erase(int x) {
    int h = Get(x);
    std::vector<int>& chain = table[h];
    for (size_t i = 0; i < chain.size(); ++i) {
      if (chain[i] == x) {
        chain[i] = chain.back();
        chain.pop_back();
        return;
      }
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  HashTable ht;
  int q = 0;
  std::cin >> q;
  while (q > 0) {
    char type;
    int x = 0;
    std::cin >> type >> x;
    if (type == '+') {
      ht.Insert(x);
    } else if (type == '-') {
      ht.Erase(x);
    } else if (type == '?') {
      if (ht.Find(x)) {
        std::cout << "YES\n";
      } else {
        std::cout << "NO\n";
      }
    }
    --q;
  }
}
