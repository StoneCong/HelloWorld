#include "../../../include/txt_file.hpp"

int get_floor(string input)
{
  int result = 0;
  int index = 1;
  for (auto e: input) {
    if (e == '(') result++;
    if (e == ')') result--;
    if (result == -1) cout << "basement: " << index << "\n";
    index++;
  }
  return result;
}

int main()
{
  vector<string> data = get_lines();
  cout << data[0] << "\n";
  int floor = get_floor(data[0]);
  cout << "floor: " << floor << "\n";
  return 0;
}
