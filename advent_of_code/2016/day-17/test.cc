#include "../../../include/txt_file.hpp"
#include "md5.h"

vector<bool> get_door_states(string input)
{
  string hash_result = md5(input.c_str());
  hash_result = hash_result.substr(0, 4);
  vector<bool> result;
  for (auto e: hash_result) {
    result.push_back(e > 'a');
  }
  return result;
}

bool add_neighbors(tuple<int, int, string> current,
		   queue<tuple<int, int, string>>& frontier,
		   vector<string>& ways)
{
  int          row = get<0>(current);
  int          col = get<1>(current);
  string       path = get<2>(current);
  vector<bool> state = get_door_states(path);

  if (state[0] && row > 0) {
    frontier.push(make_tuple(row - 1, col, path + "U"));
  }
  if (state[1] && row < 3) {
    if (row + 1 == 3 && col == 3) {
      cout << path + "D" << endl;
      ways.push_back(path + "D");
    } else {
      frontier.push(make_tuple(row + 1, col, path + "D"));
    }
  }
  if (state[2] && col > 0) {
    frontier.push(make_tuple(row, col - 1, path + "L"));
  }
  if (state[3] && col < 3) {
    if (row == 3 && col + 1 == 3) {
      cout << path + "R" << endl;
      ways.push_back(path + "R");
    } else {
      frontier.push(make_tuple(row, col + 1, path + "R"));
    }
  }
  return false;
}

int main()
{
  string input = "bwnlcvfs";
  queue<tuple<int, int, string>> frontier;
  frontier.push(make_tuple(0, 0, input));
  vector<string> ways;
  while (frontier.size()) {
    tuple<int, int, string> current = frontier.front();
    frontier.pop();
    add_neighbors(current, frontier, ways);
  }
  int max_length = 0;
  for (auto e: ways) {
    if (e.size() > max_length) max_length = e.size();
  }
  cout << max_length - input.size() << endl;
  return 0;
}
