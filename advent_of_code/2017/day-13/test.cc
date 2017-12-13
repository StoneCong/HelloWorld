#include "../../../include/txt_file.hpp"

bool can_pass(map<int, pair<int, int>> dict, int max_layer_num)
{
  for (int i = 0; i <= max_layer_num; i++) {
    for (auto it = dict.begin(); it != dict.end(); it++) {
      if (it->first == i) {
        if (it->second.second == 0) {
          return false;
        }
      }
      it->second.second++;
      if (it->second.second == it->second.first) {
        it->second.second = -1 * it->second.first + 2;
      }
    }
  }
  return true;
}

int main()
{
  vector<string> data = get_lines();
  map<int, pair<int, int>> dict;
  for (auto e: data) {
    vector<int> numbers = get_numbers(e);
    dict[numbers[0]] = make_pair(numbers[1], 0);
  }
  int max_layer_num = 0;
  for (auto e: dict) {
    max_layer_num = max(max_layer_num, e.first);
  }
  int cost = 0;
  for (int i = 0; i <= max_layer_num; i++) {
    for (auto it = dict.begin(); it != dict.end(); it++) {
      if (it->first == i) {
        if (it->second.second == 0) {
          cost += it->second.first * it->first;
        }
      }
      it->second.second++;
      if (it->second.second == it->second.first) {
        it->second.second = -1 * it->second.first + 2;
      }
    }
  }
  cout << cost << endl;

  // part 2
  for (auto it = dict.begin(); it != dict.end(); it++) {
    it->second.second = 0;
  }
  for (int delay = 0; ; delay++) {
    if (can_pass(dict, max_layer_num)) {
      cout << "delay = " << delay << endl;
      break;
    }
    for (auto it = dict.begin(); it != dict.end(); it++) {
      it->second.second++;
      if (it->second.second == it->second.first) {
        it->second.second = -1 * it->second.first + 2;
      }
    }
  }

  return 0;
}
