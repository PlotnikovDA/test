#include <iostream>
#include <queue>
#include <vector>

bool FindPath(int src, int sink, int nodes_c,
              std::vector<std::vector<long long>>& cap,
              std::vector<std::vector<long long>>& flow,
              std::vector<int>& prnt) {
  std::vector<int> vis(nodes_c + 1, 0);
  std::queue<int> q;
  q.push(src);
  vis[src] = 1;
  prnt[src] = -1;
  while (!q.empty()) {
    int curr_node = q.front();
    q.pop();
    if (curr_node == sink) {
      return true;
    }
    for (int next_node = 1; next_node <= nodes_c; ++next_node) {
      long long res_cap =
          cap[curr_node][next_node] - flow[curr_node][next_node];
      if (vis[next_node] == 0 && res_cap > 0) {
        vis[next_node] = 1;
        prnt[next_node] = curr_node;
        q.push(next_node);
      }
    }
  }
  return false;
}

void Find(int curr_node, int nodes_c, std::vector<std::vector<long long>>& cap,
          std::vector<std::vector<long long>>& flow, std::vector<int>& rch) {
  rch[curr_node] = 1;
  for (int next_node = 1; next_node <= nodes_c; ++next_node) {
    long long res_cap = cap[curr_node][next_node] - flow[curr_node][next_node];
    if (rch[next_node] == 0 && res_cap > 0) {
      Find(next_node, nodes_c, cap, flow, rch);
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<int> edge_u(m);
  std::vector<int> edge_v(m);
  std::vector<long long> edge_c(m);
  std::vector<std::vector<long long>> cap(n + 1,
                                          std::vector<long long>(n + 1, 0));
  std::vector<std::vector<long long>> flow(n + 1,
                                           std::vector<long long>(n + 1, 0));
  for (int i = 0; i < m; ++i) {
    std::cin >> edge_u[i] >> edge_v[i] >> edge_c[i];
    cap[edge_u[i]][edge_v[i]] += edge_c[i];
    cap[edge_v[i]][edge_u[i]] += edge_c[i];
  }
  const long long cC = 2000000000000000000;
  std::vector<int> prnt(n + 1, -1);
  while (FindPath(1, n, n, cap, flow, prnt)) {
    long long path_flow = cC;
    int curr = n;
    while (curr != 1) {
      int prev = prnt[curr];
      long long resd = cap[prev][curr] - flow[prev][curr];
      if (resd < path_flow) {
        path_flow = resd;
      }
      curr = prev;
    }
    curr = n;
    while (curr != 1) {
      int prev = prnt[curr];
      flow[prev][curr] += path_flow;
      flow[curr][prev] -= path_flow;
      curr = prev;
    }
  }
  std::vector<int> rch(n + 1, 0);
  Find(1, n, cap, flow, rch);
  std::vector<int> cut_edges;
  long long sum_cap = 0;
  for (int i = 0; i < m; ++i) {
    int u = edge_u[i];
    int v = edge_v[i];
    if ((rch[u] == 1 && rch[v] == 0) || (rch[u] == 0 && rch[v] == 1)) {
      cut_edges.push_back(i + 1);
      sum_cap += edge_c[i];
    }
  }
  std::cout << cut_edges.size() << " " << sum_cap << "\n";
  for (size_t i = 0; i < cut_edges.size(); ++i) {
    std::cout << cut_edges[i] << " ";
  }
  std::cout << "\n";
}
