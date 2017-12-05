/*
  http://adventofcode.com/2017/day/5
 */

#include "../../../include/txt_file.hpp"

int main()
{
  vector<string> data = get_lines();
  vector<int> instructions;
  for (auto e: data) {
    int number = stoi(e);
    instructions.push_back(number);
    cout << number << "\n";
  }
  int steps = 0;
  int cur = 0;
  for (;;) {
    if (cur < 0 || cur >= instructions.size()) break;
    int inst = instructions[cur];
    if (inst >= 3)
      instructions[cur]--;
    else
      instructions[cur]++;
    cur += inst;
    steps++;
  }
  cout << "steps: " << steps << "\n";
  return 0;
}
