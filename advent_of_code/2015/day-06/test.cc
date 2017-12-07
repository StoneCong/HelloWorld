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
  assert(line.find("turn on") != string::npos);
  return turn_off;
}

int main()
{
  vector<string> data = get_lines();
  map<pair<int, int>, int> dict;
  for (auto e: data) {
    switch (get_instruction(e)) {
    case turn_on:
      break;
    case toggle:
      break;
    case turn_off:
      break;
    }
  }

  return 0;
}
