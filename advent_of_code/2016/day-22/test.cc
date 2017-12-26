#include "../../../include/txt_file.hpp"

int main()
{
  vector<string> data = get_lines();
  vector<vector<int>> nodes;
  for (auto e: data) {
    nodes.push_back(get_numbers(e));
  }
  int count = 0;
  for (int i = 0; i < nodes.size() - 1; i++) {
    if (nodes[i][3] == 0) continue;
    for (int j = i + 1; j < nodes.size(); j++) {
      if (nodes[i][3] <= nodes[j][4]) count++;
    }
  }
  cout << count << endl;
  return 0;
}
