#include "../../../include/txt_file.hpp"

int main()
{
  vector<string> data = get_lines();
  vector<vector<int>> nodes;
  for (auto e: data) {
    nodes.push_back(get_numbers(e));
  }

  // Note: because of pairs are not symmetrical,
  //       it is not right to get ordered pair &
  //       then time it by two. Do it slow way.
  int count = 0;
  for (int i = 0; i < nodes.size(); i++) {
    if (nodes[i][3] == 0)
      continue;
    for (int j = 0; j < nodes.size(); j++) {
      if (i == j)
	continue;
      if (nodes[i][3] <= nodes[j][4])
	count++;
    }
  }
  cout << count << endl;
  return 0;
}
