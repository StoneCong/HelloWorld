#include "../../../include/txt_file.hpp"

void reverse(vector<int>& numbers, int cur, int value)
{
  int size = numbers.size();
  cur = cur % size;
  value = value % size;
  vector<int> temp = numbers;
  temp.insert(temp.end(), numbers.begin(), numbers.end());
  reverse(temp.begin() + cur, temp.begin() + cur + value);
  numbers.clear();
  for (int i = size; i < size + cur; i++) {
    numbers.push_back(temp[i]);
  }
  for (int i = cur; i < size; i++) {
    numbers.push_back(temp[i]);
  }
}

void part_1()
{
  int skip = 0;
  int cur = 0;
  vector<int> numbers;
  vector<string> data = get_lines();
  vector<int> input = get_numbers(data[0]);

  for (int i = 0; i < 256; i++) {
    numbers.push_back(i);
  }

  for (auto e: input) {
    reverse(numbers, cur, e);
    cur += (e + skip++);
  }

  cout << numbers[0] * numbers[1] << endl;
}

void part_2()
{
  int skip = 0;
  int cur = 0;
  vector<int> numbers;
  vector<string> data = get_lines();
  vector<int> input;

  for (int i = 0; i < 256; i++) {
    numbers.push_back(i);
  }

  for (auto e: data[0]) {
    input.push_back(e);
  }

  input.push_back(17);
  input.push_back(31);
  input.push_back(73);
  input.push_back(47);
  input.push_back(23);

  for (int i = 0; i < 64; i++) {
    for (auto e: input) {
      reverse(numbers, cur, e);
      cur += (e + skip++);
    }
  }

  vector<int> dense;

  for (int outer = 0; outer < 256; outer += 16) {
    int value = 0;
    for (int inner = 0; inner < 16; inner++) {
      value ^= numbers[outer + inner];
    }
    dense.push_back(value);
  }

  cout << "hash result: ";
  for (auto e: dense) {
    printf("%2x", e);
  }
  cout << endl;
}

int main()
{
  part_1();
  part_2();
  return 0;
}
