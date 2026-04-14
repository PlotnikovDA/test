#include <iostream>
#include <vector>

const long long INF = 1000000000000000000LL;
long long exact_first_val = -INF;
long long final_first_val = 0;

void Bfs(std::vector<std::vector<int>>& adj_list, std::vector<std::vector<int>>& edge_weights,
         std::vector<int>& visited, std::vector<int>& coefficient,
         std::vector<long long>& constant_term, std::vector<int>& queue) {
  int head = 0;
  queue.push_back(1);
  visited[1] = 1;
  coefficient[1] = 1;
  constant_term[1] = 0;
  while (head < (int)queue.size()) {
    int current_node = queue[head];
    ++head;
    for (size_t i = 0; i < adj_list[current_node].size(); ++i) {
      int neighbor = adj_list[current_node][i];
      long long weight = edge_weights[current_node][i];
      if (visited[neighbor] == 0) {
        visited[neighbor] = 1;
        coefficient[neighbor] = -coefficient[current_node];
        constant_term[neighbor] = weight - constant_term[current_node];
        queue.push_back(neighbor);
      } else if (coefficient[neighbor] == coefficient[current_node]) {
        long long remaining_weight = weight - constant_term[current_node] - constant_term[neighbor];
        exact_first_val = remaining_weight / (coefficient[current_node] + coefficient[neighbor]);
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
  std::vector<std::vector<int>> adj_list(num_vertices + 1);
  std::vector<std::vector<int>> edge_weights(num_vertices + 1);
  std::vector<int> visited(num_vertices + 1, 0);
  std::vector<int> coefficient(num_vertices + 1, 0);
  std::vector<long long> constant_term(num_vertices + 1, 0);
  std::vector<int> queue;
  for (int i = 0; i < num_edges; ++i) {
    int u = 0;
    int v = 0;
    int weight = 0;
    std::cin >> u >> v >> weight;
    adj_list[u].push_back(v);
    edge_weights[u].push_back(weight);
    adj_list[v].push_back(u);
    edge_weights[v].push_back(weight);
  }
  Bfs(adj_list, edge_weights, visited, coefficient, constant_term, queue);
  if (exact_first_val != -INF) {
    final_first_val = exact_first_val;
  } else {
    long long min_pos_const = INF;
    long long min_neg_const = INF;
    for (int i = 1; i <= num_vertices; ++i) {
      if (coefficient[i] == 1) {
        if (constant_term[i] < min_pos_const) {
          min_pos_const = constant_term[i];
        }
      } else {
        if (constant_term[i] < min_neg_const) {
          min_neg_const = constant_term[i];
        }
      }
    }
    final_first_val = 1 - min_pos_const;
    int is_valid = 1;
    std::vector<int> seen_values(num_vertices + 1, 0);
    for (int i = 1; i <= num_vertices; ++i) {
      long long current_val = coefficient[i] * final_first_val + constant_term[i];
      if (current_val < 1 || current_val > num_vertices) {
        is_valid = 0;
        break;
      }
      if (seen_values[current_val] == 1) {
        is_valid = 0;
        break;
      }
      seen_values[current_val] = 1;
    }
    if (is_valid == 0) {
      final_first_val = min_neg_const - 1;
    }
  }
  for (int i = 1; i <= num_vertices; ++i) {
    long long current_val = coefficient[i] * final_first_val + constant_term[i];
    std::cout << current_val << " ";
  }
  std::cout << "\n";
}
