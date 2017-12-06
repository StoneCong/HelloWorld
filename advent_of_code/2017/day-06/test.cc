#include "../../../include/txt_file.hpp"

void get_max(vector<int> numbers, int& value, int& index)
{
  value = -1;
  for (int i = 0; i < 16; i++) {
    if (numbers[i] > value) {
      value = numbers[i];
      index = i;
    }
  }
  return;
}

void rebalance(vector<int>& numbers)
{
  vector<int> new_numbers = numbers;
  int value;
  int index;
  get_max(numbers, value, index);
  new_numbers[index] = 0;
  for (int i = 0; i < value; i++) {
    new_numbers[(++index) % 16]++;
  }
  numbers = new_numbers;
}

vector<int> find_dup(vector<int> numbers)
{
  map<vector<int>, bool> dict;
  dict[numbers] = true;
  int steps = 0;
  for (;;) {
    steps++;
    rebalance(numbers);
    if (dict.find(numbers) != dict.end()) {
      cout << steps << "\n";
      return numbers;
    }
    dict[numbers] = true;
  }
}

int main()
{
  vector<string> data = get_lines();
  vector<int> numbers = get_numbers(data[0]);
  numbers = find_dup(numbers);
  numbers = find_dup(numbers);
  return 0;
}
