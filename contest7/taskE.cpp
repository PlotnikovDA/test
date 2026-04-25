#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

int timer = 0;
std::vector<int> time_in;
std::vector<int> min_reachable_time;
std::vector<int> visited;
std::vector<int> bridge_indices;

void Dfs(int current_node, int parent_edge_index,
                    const std::vector<std::vector<std::pair<int, int>>>& adj_list) {
  visited[current_node] = 1;
  timer = timer + 1;
  time_in[current_node] = timer;
  min_reachable_time[current_node] = timer;
  for (size_t i = 0; i < adj_list[current_node].size(); ++i) {
    int neighbor = adj_list[current_node][i].first;
    int edge_index = adj_list[current_node][i].second;
    if (edge_index == parent_edge_index) {
      continue;
    }
    if (visited[neighbor] == 1) {
      if (time_in[neighbor] < min_reachable_time[current_node]) {
        min_reachable_time[current_node] = time_in[neighbor];
      }
    } else {
      Dfs(neighbor, edge_index, adj_list);
      if (min_reachable_time[neighbor] < min_reachable_time[current_node]) {
        min_reachable_time[current_node] = min_reachable_time[neighbor];
      }
      if (min_reachable_time[neighbor] > time_in[current_node]) {
        bridge_indices.push_back(edge_index);
      }
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int num_vertices = 0;
  int num_edges = 0;
  std::cin >> num_vertices >> num_edges;
  std::vector<std::vector<std::pair<int, int>>> adj_list(num_vertices + 1);
  for (int i = 1; i <= num_edges; ++i) {
    int from = 0;
    int to = 0;
    std::cin >> from >> to;
    adj_list[from].push_back(std::make_pair(to, i));
    adj_list[to].push_back(std::make_pair(from, i));
  }
  time_in.resize(num_vertices + 1, 0);
  min_reachable_time.resize(num_vertices + 1, 0);
  visited.resize(num_vertices + 1, 0);
  for (int i = 1; i <= num_vertices; ++i) {
    if (visited[i] == 0) {
      Dfs(i, -1, adj_list);
    }
  }
  std::sort(bridge_indices.begin(), bridge_indices.end());
  std::cout << bridge_indices.size() << "\n";
  for (size_t i = 0; i < bridge_indices.size(); ++i) {
    std::cout << bridge_indices[i] << " ";
  }
  std::cout << "\n";
}
