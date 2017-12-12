#include "../../../include/txt_file.hpp"

void breath_first_traverse(int start,
                           map<int, vector<int>>& dict,
                           map<int, bool>& reached)
{
  queue<int> frontier;
  frontier.push(start);
  reached[start] = true;
  while (frontier.size()) {
    int current = frontier.front();
    frontier.pop();
    for (auto e: dict[current]) {
      if (reached[e]) continue;
      reached[e] = true;
      frontier.push(e);
    }
  }
}

int main()
{
  vector<string> data = get_lines();
  map<int, vector<int>> dict;
  map<int, bool> reached;
  for (auto e: data) {
    vector<int> numbers = get_numbers(e);
    vector<int> value;
    for (int i = 1; i < numbers.size(); i++) {
      value.push_back(numbers[i]);
    }
    dict[numbers[0]] = value;
  }

  // part 1
  breath_first_traverse(0, dict, reached);
  cout << reached.size() << endl;

  // part 2
  reached.clear();
  int group_count = 0;
  for (int i = 0; i < 2000; i++) {
    if (reached[i]) continue;
    group_count++;
    breath_first_traverse(i, dict, reached);
  }
  cout << group_count << endl;
  return 0;
}
