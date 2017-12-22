#include "../../../include/txt_file.hpp"

enum state {
  Clean = 0,
  Weakened = 1,
  Infected = 2,
  Flagged = 3
};

int main()
{
  vector<string> data = get_lines();
  map<pair<int, int>, state> dict;
  for (int row = 0; row < data.size(); row++) {
    for (int col = 0; col < data[row].size(); col++) {
      if (data[row][col] == '#') {
        dict[make_pair(row, col)] = Infected;
      } else {
        dict[make_pair(row, col)] = Clean;
      }
    }
  }

  direction cur_dir = N;
  pair<int, int> cur_pos = make_pair(data.size() / 2, data.size() / 2);
  int count = 0;

  for (int i = 0; i < 10000000; i++) {
    switch(dict[cur_pos]) {
    case Clean:
      cur_dir = turn_left(cur_dir);
      dict[cur_pos] = Weakened;
      break;
    case Weakened:
      count++;
      dict[cur_pos] = Infected;
      break;
    case Infected:
      cur_dir = turn_right(cur_dir);
      dict[cur_pos] = Flagged;
      break;
    case Flagged:
      cur_dir = turn_right(cur_dir);
      cur_dir = turn_right(cur_dir);
      dict[cur_pos] = Clean;
      break;
    }
    cur_pos = next_location(cur_pos, cur_dir);
  }

  cout << count << endl;
  
  return 0;
}
