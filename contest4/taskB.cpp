#include <iostream>
#include <string>

struct SplayNode {
  int key;
  SplayNode* left = nullptr;
  SplayNode* right = nullptr;
  SplayNode* parent = nullptr;
  int sz = 1;

  SplayNode(int k) : key(k) {}

  ~SplayNode() {
    delete left;
    delete right;
  }

  void Update() {
    sz = 1 + (left != nullptr ? left->sz : 0) +
         (right != nullptr ? right->sz : 0);
    if (left != nullptr) {
      left->parent = this;
    }
    if (right != nullptr) {
      right->parent = this;
    }
  }
};

class SplayTree {
 private:
  SplayNode* root_ = nullptr;

  static int Size(SplayNode* node) { return node != nullptr ? node->sz : 0; }

  static SplayNode* RotateRight(SplayNode* x) {
    SplayNode* y = x->left;
    x->left = y->right;
    if (y->right != nullptr) {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent != nullptr) {
      if (x->parent->left == x) {
        x->parent->left = y;
      } else {
        x->parent->right = y;
      }
    }
    y->right = x;
    x->parent = y;
    x->Update();
    y->Update();
    return y;
  }

  static SplayNode* RotateLeft(SplayNode* x) {
    SplayNode* y = x->right;
    x->right = y->left;
    if (y->left != nullptr) {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent != nullptr) {
      if (x->parent->left == x) {
        x->parent->left = y;
      } else {
        x->parent->right = y;
      }
    }
    y->left = x;
    x->parent = y;
    x->Update();
    y->Update();
    return y;
  }

  static void Splay(SplayNode*& t, SplayNode* x) {
    if (x == nullptr) {
      return;
    }
    while (x->parent != nullptr) {
      SplayNode* p = x->parent;
      SplayNode* g = p->parent;

      if (g == nullptr) {
        if (x == p->left) {
          t = RotateRight(p);
        } else {
          t = RotateLeft(p);
        }
      } else if (p == g->left && x == p->left) {
        t = RotateRight(g);
        t = RotateRight(p);
      } else if (p == g->right && x == p->right) {
        t = RotateLeft(g);
        t = RotateLeft(p);
      } else if (p == g->left && x == p->right) {
        t = RotateLeft(p);
        t = RotateRight(g);
      } else {
        t = RotateRight(p);
        t = RotateLeft(g);
      }
    }
    t = x;
  }

  static SplayNode* Find(SplayNode*& t, int x) {
    SplayNode* cur = t;
    SplayNode* last = nullptr;
    while (cur != nullptr) {
      last = cur;
      if (x == cur->key) {
        break;
      }
      if (x < cur->key) {
        cur = cur->left;
      } else {
        cur = cur->right;
      }
    }
    if (last != nullptr) {
      Splay(t, last);
    }
    return (last != nullptr && last->key == x) ? last : nullptr;
  }

  static std::pair<SplayNode*, SplayNode*> Split(SplayNode* t, int x) {
    if (t == nullptr) {
      return {nullptr, nullptr};
    }
    Find(t, x);
    if (t->key < x) {
      SplayNode* r = t->right;
      if (r != nullptr) {
        r->parent = nullptr;
      }
      t->right = nullptr;
      t->Update();
      return {t, r};
    }
    SplayNode* l = t->left;
    if (l != nullptr) {
      l->parent = nullptr;
    }
    t->left = nullptr;
    t->Update();
    return {l, t};
  }

  static SplayNode* Merge(SplayNode* l, SplayNode* r) {
    if (l == nullptr) {
      return r;
    }
    if (r == nullptr) {
      return l;
    }

    SplayNode* max_l = l;
    while (max_l->right != nullptr) {
      max_l = max_l->right;
    }
    Splay(l, max_l);
    l->right = r;
    if (r != nullptr) {
      r->parent = l;
    }
    l->Update();
    return l;
  }

  static SplayNode* FindPrev(SplayNode*& t, int x) {
    auto [l, r] = Split(t, x);
    if (l == nullptr) {
      t = r;
      return nullptr;
    }

    SplayNode* cur = l;
    while (cur->right != nullptr) {
      cur = cur->right;
    }
    Splay(l, cur);

    t = Merge(l, r);
    return cur;
  }

  static SplayNode* FindNext(SplayNode*& t, int x) {
    auto [l, r] = Split(t, x);
    if (r == nullptr) {
      t = l;
      return nullptr;
    }

    SplayNode* cur = r;
    while (cur->left != nullptr) {
      cur = cur->left;
    }
    Splay(r, cur);

    t = Merge(l, r);
    return cur;
  }

 public:
  ~SplayTree() { delete root_; }

  bool Exist(int x) { return Find(root_, x) != nullptr; }

  void Insert(int x) {
    if (Exist(x)) {
      return;
    }

    auto [l, r] = Split(root_, x);
    SplayNode* node = new SplayNode(x);
    root_ = Merge(Merge(l, node), r);
  }

  void Erase(int x) {
    if (!Exist(x)) {
      return;
    }

    SplayNode* node = root_;
    SplayNode* l = node->left;
    SplayNode* r = node->right;

    if (l != nullptr) {
      l->parent = nullptr;
    }
    if (r != nullptr) {
      r->parent = nullptr;
    }
    node->left = node->right = nullptr;
    delete node;

    root_ = Merge(l, r);
  }

  SplayNode* Next(int x) { return FindNext(root_, x); }

  SplayNode* Prev(int x) { return FindPrev(root_, x); }

  SplayNode* Kth(int k) {
    if (root_ == nullptr || k < 1 || k > root_->sz) {
      return nullptr;
    }

    SplayNode* cur = root_;
    while (cur != nullptr) {
      int ls = Size(cur->left);
      if (k == ls + 1) {
        break;
      }
      if (k <= ls) {
        cur = cur->left;
      } else {
        k -= ls + 1;
        cur = cur->right;
      }
    }
    Splay(root_, cur);
    return cur;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::string s;
  SplayTree tree;
  while (std::cin >> s) {
    int x;
    std::cin >> x;
    if (s == "insert") {
      tree.Insert(x);
    }
    if (s == "exists") {
      if (tree.Exist(x)) {
        std::cout << "true\n";
      } else {
        std::cout << "false\n";
      }
    }
    if (s == "delete") {
      tree.Erase(x);
    }
    if (s == "next") {
      SplayNode* it = tree.Next(x);
      if (it == nullptr) {
        std::cout << "none\n";
      } else {
        std::cout << it->key << '\n';
      }
    }
    if (s == "prev") {
      SplayNode* it = tree.Prev(x);
      if (it == nullptr) {
        std::cout << "none\n";
      } else {
        std::cout << it->key << '\n';
      }
    }
    if (s == "kth") {
      ++x;
      SplayNode* it = tree.Kth(x);
      if (it == nullptr) {
        std::cout << "none\n";
      } else {
        std::cout << it->key << '\n';
      }
    }
  }
}
