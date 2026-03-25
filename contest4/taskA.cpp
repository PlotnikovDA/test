#include <cassert>
#include <iostream>

const long long cMOD = 1e9;

struct AvlNode {
  AvlNode* left;
  AvlNode* right;
  AvlNode* parent;
  int depth;
  int key;
  int size;

  AvlNode(int key)
      : left(nullptr),
        right(nullptr),
        parent(nullptr),
        depth(1),
        key(key),
        size(1) {}

  void Recalc() {
    size = depth = 1;
    if (left != nullptr) {
      left->parent = this;
      depth = std::max(depth, left->depth + 1);
      size += left->size;
    }
    if (right != nullptr) {
      right->parent = this;
      depth = std::max(depth, right->depth + 1);
      size += right->size;
    }
  }

  ~AvlNode() {
    delete left;
    delete right;
  }
};

class AvlTree {
 private:
  AvlNode* root_;

  static int Depth(AvlNode* x) { return (x == nullptr ? 0 : x->depth); }

  static int Size(AvlNode* x) { return (x == nullptr ? 0 : x->size); }

  static AvlNode* SmallLeftRotate(AvlNode* x) {
    AvlNode* xr = x->right;
    if (xr == nullptr) {
      return x;
    }
    x->right = xr->left;
    xr->left = x;
    x->Recalc();
    xr->Recalc();
    return xr;
  }

  static AvlNode* SmallRightRotate(AvlNode* x) {
    AvlNode* xl = x->left;
    if (xl == nullptr) {
      return x;
    }
    x->left = xl->right;
    xl->right = x;
    x->Recalc();
    xl->Recalc();
    return xl;
  }

  static AvlNode* BigLeftRotate(AvlNode* x) {
    if (x->right == nullptr) {
      return x;
    }
    AvlNode* xrl = x->right->left;
    if (xrl == nullptr) {
      return SmallLeftRotate(x);
    }
    x->right->left = xrl->right;
    xrl->right = x->right;
    x->right = xrl->left;
    xrl->left = x;
    xrl->left->Recalc();
    xrl->right->Recalc();
    xrl->Recalc();
    return xrl;
  }

  static AvlNode* BigRightRotate(AvlNode* x) {
    if (x->left == nullptr) {
      return x;
    }
    AvlNode* xlr = x->left->right;
    if (xlr == nullptr) {
      return SmallRightRotate(x);
    }
    x->left->right = xlr->left;
    xlr->left = x->left;
    x->left = xlr->right;
    xlr->right = x;
    xlr->left->Recalc();
    xlr->right->Recalc();
    xlr->Recalc();
    return xlr;
  }

  static void Recalculate(AvlNode*& x) {
    if (std::abs(Depth(x->right) - Depth(x->left)) < 2) {
      return;
    }
    if (Depth(x->left) < Depth(x->right)) {
      if (Depth(x->right != nullptr ? x->right->left : nullptr) <=
          Depth(x->right != nullptr ? x->right->right : nullptr)) {
        x = SmallLeftRotate(x);
      } else {
        x = BigLeftRotate(x);
      }
    } else {
      if (Depth(x->left != nullptr ? x->left->left : nullptr) >=
          Depth(x->left != nullptr ? x->left->right : nullptr)) {
        x = SmallRightRotate(x);
      } else {
        x = BigRightRotate(x);
      }
    }
    assert(std::abs(Depth(x->right) - Depth(x->left)) < 2);
  }

  void Fix(AvlNode* cur) {
    while (true) {
      cur->Recalc();
      AvlNode* pred = cur->parent;
      bool is_left = (pred != nullptr && pred->left == cur);
      Recalculate(cur);
      cur->parent = pred;
      if (pred == nullptr) {
        root_ = cur;
        break;
      }
      if (is_left) {
        pred->left = cur;
      } else {
        pred->right = cur;
      }
      cur = pred;
    }
  }

  void Insert(AvlNode* x) {
    AvlNode* cur = root_;
    while (x->key != cur->key) {
      if (x->key < cur->key) {
        if (cur->left == nullptr) {
          cur->left = x;
          x->parent = cur;
          break;
        }
        cur = cur->left;
      } else {
        if (cur->right == nullptr) {
          cur->right = x;
          x->parent = cur;
          break;
        }
        cur = cur->right;
      }
    }
    if (cur->key == x->key) {
      delete x;
      return;
    }
    Fix(cur);
  }

  static AvlNode* MinElement(AvlNode* cur) {
    while (cur->left != nullptr) {
      cur = cur->left;
    }
    return cur;
  }

  void EraseElement(int key) {
    AvlNode* cur = root_;
    while (cur != nullptr && cur->key != key) {
      if (key < cur->key) {
        cur = cur->left;
      } else {
        cur = cur->right;
      }
    }
    if (cur == nullptr) {
      return;
    }
    if (cur->left != nullptr && cur->right != nullptr) {
      AvlNode* nxt = MinElement(cur->right);
      std::swap(cur->key, nxt->key);
      std::swap(cur, nxt);
    }
    AvlNode* son = (cur->left != nullptr ? cur->left : cur->right);
    if (cur->parent == nullptr) {
      root_ = son;
      if (son != nullptr) {
        son->parent = nullptr;
      }
      cur->left = cur->right = nullptr;
      delete cur;
      return;
    }
    (cur->parent->right == cur ? cur->parent->right : cur->parent->left) = son;
    if (son != nullptr) {
      son->parent = cur->parent;
    }
    Fix(cur->parent);
    cur->left = cur->right = nullptr;
    delete cur;
  }

  bool ExistElement(int key) {
    AvlNode* cur = root_;
    while (cur != nullptr && cur->key != key) {
      if (key < cur->key) {
        cur = cur->left;
      } else {
        cur = cur->right;
      }
    }
    return cur != nullptr;
  }

  AvlNode* FindNext(int key) {
    AvlNode* cur = root_;
    AvlNode* save = nullptr;
    while (cur != nullptr) {
      if (cur->key > key) {
        save = cur;
        cur = cur->left;
      } else {
        cur = cur->right;
      }
    }
    return save;
  }

  AvlNode* FindPrev(int key) {
    AvlNode* cur = root_;
    AvlNode* save = nullptr;
    while (cur != nullptr) {
      if (cur->key < key) {
        save = cur;
        cur = cur->right;
      } else {
        cur = cur->left;
      }
    }
    return save;
  }

  AvlNode* FindKth(int k) {
    if (root_ == nullptr || k > root_->size || k <= 0) {
      return nullptr;
    }
    AvlNode* cur = root_;
    while (true) {
      if (k == Size(cur->left) + 1) {
        return cur;
      }
      if (Size(cur->left) >= k) {
        cur = cur->left;
      } else {
        k -= Size(cur->left) + 1;
        cur = cur->right;
      }
    }
  }

 public:
  AvlTree() : root_(nullptr) {}

  void Insert(int key) {
    AvlNode* x = new AvlNode(key);
    if (root_ == nullptr) {
      root_ = x;
    } else {
      Insert(x);
    }
  }

  void Erase(int key) { EraseElement(key); }

  bool Exist(int key) { return ExistElement(key); }

  AvlNode* Next(int key) { return FindNext(key); }

  AvlNode* Prev(int key) { return FindPrev(key); }

  AvlNode* Kth(int k) { return FindKth(k); }

  ~AvlTree() { delete root_; }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int q;
  std::cin >> q;
  AvlTree tree;
  int pred = 0;
  while (q != 0) {
    q--;
    char c;
    std::cin >> c;
    if (c == '+') {
      int x;
      std::cin >> x;
      x = (x + pred + cMOD) % cMOD;
      pred = 0;
      tree.Insert(x);
    }
    if (c == '?') {
      int x;
      std::cin >> x;
      AvlNode* v = tree.Next(x - 1);
      int res = -1;
      if (v != nullptr) {
        res = v->key;
      }
      std::cout << res << '\n';
      pred = res;
    }
  }
}
