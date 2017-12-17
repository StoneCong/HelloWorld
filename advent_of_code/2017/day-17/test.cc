#include "../../../include/txt_file.hpp"
#include <list>

void part_1()
{
  vector<int> numbers;
  numbers.push_back(0);
  int cur = 0;
  for (int i = 1; i <= 2017; i++) {
    cur = (cur + 337) % numbers.size();
    numbers.insert(numbers.begin() + cur + 1, i);
    cur++;
    if (i == 2017) cout << numbers[(cur + 1) % numbers.size()] << endl;
  }
}

// This is slow once n > 2M
void n_squared_part_2()
{
  vector<int> numbers;
  numbers.push_back(0);
  int cur = 0;
  for (int i = 1; i <= 50000000; i++) {
    if (i % 1000 == 0) cout << i << endl;
    cur = (cur + 337) % numbers.size();
    numbers.insert(numbers.begin() + cur + 1, i);
    cur++;
  }
  for (int i = 0; i <= 50000000; i++) {
    if (numbers[i] == 0) {
      cout << numbers[(i + 1) % 50000000] << endl;
      break;
    }
  }
}

void linear_part_2()
{
  list<int> numbers = {0};
  int cur = 0;
  auto it = numbers.begin();

  // brute force calculation. good enough for now.
  // need to find a better way later.
  for (int i = 1; i <= 50000000; i++) {
    if (i % 1000 == 0) cout << i << endl;
    int new_pos = (cur + 337) % numbers.size();
    if (new_pos >= cur) {
      for (int j = cur; j < new_pos; j++) it++;
    } else {
      it = numbers.begin();
      for (int j = 0; j < new_pos; j++) it++;
    }
    cur = new_pos;
    numbers.insert(it, i);
    cur++;
  }

  // Get the result out
  it = numbers.begin();
  for (int i = 0; i <= 50000000; i++) {
    if (*it == 0) {
      it++;
      if (it == numbers.end()) {
        cout << *numbers.begin() << endl;
      } else {
        cout << *it << endl;
      }
      break;
    }
    it++;
  }
}

int main()
{
  linear_part_2();
}
