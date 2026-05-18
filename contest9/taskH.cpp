#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

struct Edge {
  int to = 0;
  long long cap = 0;
  long long flow = 0;
  int rev = 0;
};

struct EdgeRef {
  int u = 0;
  int idx = 0;
};

std::vector<std::vector<Edge>> adj;
std::vector<int> lvl;
std::vector<int> ptr;
std::vector<EdgeRef> edges_order;

void AddEdge(int from, int to, long long cap) {
  int from_size = adj[from].size();
  int to_size = adj[to].size();
  Edge e1;
  e1.to = to;
  e1.cap = cap;
  e1.flow = 0;
  e1.rev = to_size;
  adj[from].push_back(e1);
  Edge e2;
  e2.to = from;
  e2.cap = 0;
  e2.flow = 0;
  e2.rev = from_size;
  adj[to].push_back(e2);
}

bool Bfs(int s, int t) {
  for (size_t i = 0; i < lvl.size(); ++i) {
    lvl[i] = -1;
  }
  lvl[s] = 0;
  std::queue<int> q;
  q.push(s);
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (size_t j = 0; j < adj[v].size(); ++j) {
      int to = adj[v][j].to;
      long long cap = adj[v][j].cap;
      long long flow = adj[v][j].flow;
      if (lvl[to] != -1) {
        continue;
      }
      if (cap > flow) {
        lvl[to] = lvl[v] + 1;
        q.push(to);
      }
    }
  }
  bool res = (lvl[t] != -1);
  return res;
}

long long Dfs(int v, int t, long long pushed) {
  if (pushed == 0) {
    return 0;
  }
  if (v == t) {
    return pushed;
  }
  for (size_t cid = ptr[v]; cid < adj[v].size(); ++cid) {
    ptr[v] = cid;
    int to = adj[v][cid].to;
    long long cap = adj[v][cid].cap;
    long long flow = adj[v][cid].flow;
    int tr = lvl[to];
    if (tr != lvl[v] + 1) {
      continue;
    }
    if (cap == flow) {
      continue;
    }
    long long mn = std::min(pushed, cap - flow);
    long long push = Dfs(to, t, mn);
    if (push == 0) {
      continue;
    }
    adj[v][cid].flow += push;
    int rev = adj[v][cid].rev;
    adj[to][rev].flow -= push;
    return push;
  }
  ptr[v] = adj[v].size();
  return 0;
}

long long Dinic(int s, int t, long long c_inf) {
  long long flow = 0;
  while (Bfs(s, t)) {
    for (size_t i = 0; i < ptr.size(); ++i) {
      ptr[i] = 0;
    }
    long long pushed = Dfs(s, t, c_inf);
    while (pushed != 0) {
      flow += pushed;
      pushed = Dfs(s, t, c_inf);
    }
  }
  return flow;
}

void ReadGraph(int m) {
  for (int i = 0; i < m; ++i) {
    int u = 0;
    int v = 0;
    long long c = 0;
    std::cin >> u >> v >> c;
    --u;
    --v;
    EdgeRef er;
    er.u = u;
    er.idx = adj[u].size();
    edges_order.push_back(er);
    AddEdge(u, v, c);
  }
}

void PrintFlow(int m) {
  for (int i = 0; i < m; ++i) {
    int u = edges_order[i].u;
    int idx = edges_order[i].idx;
    long long flow = adj[u][idx].flow;
    std::cout << flow << "\n";
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  const long long cInf = 2000000000000000000;
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  adj.resize(n);
  lvl.resize(n);
  ptr.resize(n);
  ReadGraph(m);
  long long max_flow = Dinic(0, n - 1, cInf);
  std::cout << max_flow << "\n";
  PrintFlow(m);
}
