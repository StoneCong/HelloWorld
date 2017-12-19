#include "../../../include/txt_file.hpp"

pair<int, int> get_start(vector<string>& data)
{
  int row = 0;
  int col = 0;
  for (int i = 0; i < data.size(); i++) {
    size_t pos = data[i].find("|");
    if (pos != string::npos)
      return make_pair(i, pos);
  }
  return make_pair(-1, -1);
}

enum direction {
  up    = 1,
  right = 2,
  down  = 3,
  left  = 4
};

char get_graph_char(pair<int, int> cur_pos, vector<string>& data)
{
  if (cur_pos.first < 0 || cur_pos.first >= data.size()) {
    return ' ';
  }
  string line = data[cur_pos.first];
  if (cur_pos.second < 0 || cur_pos.second >= line.size()) {
    return ' ';
  }
  return line[cur_pos.second];
}

int main()
{
  vector<string> data = get_lines();
  pair<int, int> start = get_start(data);
  assert(start != make_pair(-1, -1));
  cout << start.first << ", " << start.second << endl;
  direction cur_dir = down;
  pair<int, int> cur_pos = start;
  string trail = "";
  char cur_char;
  int steps = 0;
  for (;;) {
    switch (cur_dir) {
    case up:
      cur_pos.first--;
      break;
    case direction::right:
      cur_pos.second++;
      break;
    case down:
      cur_pos.first++;
      break;
    case direction::left:
      cur_pos.second--;
      break;
    }
    steps++;
    cur_char = get_graph_char(cur_pos, data);
    if (cur_char == ' ') break;
    if (cur_char >= 'A' && cur_char <= 'Z') trail.append(1, cur_char);
    if (cur_char == '+') {
      switch (cur_dir) {
      case up:
      case down:
        // left or right
        if (get_graph_char(make_pair(cur_pos.first, cur_pos.second + 1), data) == ' ') {
          cur_dir = direction::left;
        } else {
          cur_dir = direction::right;
        }
        break;
      case direction::left:
      case direction::right:
        // up or down
        if (get_graph_char(make_pair(cur_pos.first + 1, cur_pos.second), data) == ' ') {
          cur_dir = up;
        } else {
          cur_dir = down;
        }
        break;
      }
    }
  }
  cout << trail << endl;
  cout << steps << endl;
}
