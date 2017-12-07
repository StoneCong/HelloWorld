#include "../../../include/txt_file.hpp"

enum instruction {
  turn_on = 1,
  toggle = 2,
  turn_off = 4
};

instruction get_instruction(string line)
{
  if (line.find("turn on") != string::npos) return turn_on;
  if (line.find("toggle") != string::npos) return toggle;
  if (line.find("turn off") != string::npos) return turn_off;
  assert(false); // should not be here!
  return turn_off;
}

void part_1()
{
  vector<string> data = get_lines();
  map<pair<int, int>, int> dict;
  for (auto e: data) {
    vector<int> numbers = get_numbers(e);
    assert(numbers.size() == 4);
    instruction inst = get_instruction(e);
    for (int row = numbers[0]; row <= numbers[2]; row++) {
      for (int col = numbers[1]; col <= numbers[3]; col++) {
        switch (inst) {
        case turn_on:
          dict[make_pair(row, col)] = 1;
          break;
        case toggle:
          if (dict.find(make_pair(row, col)) != dict.end()) {
            dict[make_pair(row, col)] = dict[make_pair(row, col)] ? 0 : 1;
          } else {
            dict[make_pair(row, col)] = 1;
          }
          break;
        case turn_off:
          dict[make_pair(row, col)] = 0;
          break;
        }
      }
    }
  }

  int count = 0;
  for (auto e: dict) {
    if (e.second) count++;
  }

  cout << "number of lights lit: " << count << endl;

}

void part_2()
{
  vector<string> data = get_lines();
  map<pair<int, int>, int> dict;
  for (auto e: data) {
    vector<int> numbers = get_numbers(e);
    assert(numbers.size() == 4);
    instruction inst = get_instruction(e);
    for (int row = numbers[0]; row <= numbers[2]; row++) {
      for (int col = numbers[1]; col <= numbers[3]; col++) {
        switch (inst) {
        case turn_on:
          if (dict.find(make_pair(row, col)) != dict.end()) {
            dict[make_pair(row, col)] += 1;
          } else {
            dict[make_pair(row, col)] = 1;
          }
          break;
        case toggle:
          if (dict.find(make_pair(row, col)) != dict.end()) {
            dict[make_pair(row, col)] += 2;
          } else {
            dict[make_pair(row, col)] = 2;
          }
          break;
        case turn_off:
          if (dict.find(make_pair(row, col)) != dict.end()) {
            if (dict[make_pair(row, col)]) {
              dict[make_pair(row, col)] -= 1;
            }
          }
          break;
        }
      }
    }
  }

  int count = 0;
  for (auto e: dict) {
    count += e.second;
  }

  cout << "total brightness: " << count << endl;
}

int main()
{
  part_2();
  return 0;
}
