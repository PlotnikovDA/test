#include <algorithm>
#include <iostream>
#include <vector>

struct Edge {
  int from_node;
  int to_node;
  long long edge_weight;
};

bool CompareEdgesByWeight(const Edge& first_edge, const Edge& second_edge) {
  return first_edge.edge_weight < second_edge.edge_weight;
}

int FindSetRoot(int current_node, std::vector<int>& parent_array) {
  if (current_node == parent_array[current_node]) {
    return current_node;
  }
  parent_array[current_node] =
      FindSetRoot(parent_array[current_node], parent_array);
  return parent_array[current_node];
}

void MergeSets(int node_a, int node_b, std::vector<int>& parent_array,
               std::vector<int>& size_array) {
  int root_a = FindSetRoot(node_a, parent_array);
  int root_b = FindSetRoot(node_b, parent_array);
  if (root_a != root_b) {
    if (size_array[root_a] < size_array[root_b]) {
      parent_array[root_a] = root_b;
      size_array[root_b] += size_array[root_a];
    } else {
      parent_array[root_b] = root_a;
      size_array[root_a] += size_array[root_b];
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int num_vertices;
  int num_edges;
  std::cin >> num_vertices >> num_edges;
  std::vector<Edge> graph_edges(num_edges);
  for (int i = 0; i < num_edges; ++i) {
    std::cin >> graph_edges[i].from_node >> graph_edges[i].to_node >>
        graph_edges[i].edge_weight;
  }
  std::sort(graph_edges.begin(), graph_edges.end(), CompareEdgesByWeight);
  std::vector<int> parent_array(num_vertices + 1);
  std::vector<int> component_size(num_vertices + 1, 1);
  for (int i = 1; i <= num_vertices; ++i) {
    parent_array[i] = i;
  }
  long long total_mst_weight = 0;
  for (int i = 0; i < num_edges; ++i) {
    int root_u = FindSetRoot(graph_edges[i].from_node, parent_array);
    int root_v = FindSetRoot(graph_edges[i].to_node, parent_array);
    if (root_u != root_v) {
      total_mst_weight += graph_edges[i].edge_weight;
      MergeSets(graph_edges[i].from_node, graph_edges[i].to_node, parent_array,
                component_size);
    }
  }
  std::cout << total_mst_weight << "\n";
}
