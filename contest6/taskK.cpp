#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int n;
  std::cin >> n;
  std::vector<long long> values(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i];
  }
  std::vector<long long> dp_values;
  std::vector<int> dp_indices;
  std::vector<int> parent_index(n);
  for (int i = 0; i < n; i++) {
    long long current_val;
    current_val = -values[i];
    int insert_pos;
    insert_pos = (int)(std::upper_bound(dp_values.begin(), dp_values.end(),
                                        current_val) -
                       dp_values.begin());
    if (insert_pos == (int)dp_values.size()) {
      dp_values.push_back(current_val);
      dp_indices.push_back(i);
    } else {
      dp_values[insert_pos] = current_val;
      dp_indices[insert_pos] = i;
    }
    if (insert_pos > 0) {
      parent_index[i] = dp_indices[insert_pos - 1];
    } else {
      parent_index[i] = -1;
    }
  }
  int sequence_length = (int)dp_indices.size();
  std::cout << sequence_length << "\n";
  std::vector<int> answer;
  int current_node = dp_indices.back();
  while (current_node != -1) {
    answer.push_back(current_node + 1);
    current_node = parent_index[current_node];
  }
  std::reverse(answer.begin(), answer.end());
  for (int i = 0; i < sequence_length; i++) {
    std::cout << answer[i] << " ";
  }
  std::cout << "\n";
}
