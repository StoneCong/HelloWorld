#include "../../../include/txt_file.hpp"

vector<int> get_side_area(vector<int> dims)
{
  vector<int> sides;
  sides.push_back(dims[0] * dims[1]);
  sides.push_back(dims[0] * dims[2]);
  sides.push_back(dims[1] * dims[2]);
  return sides;
}

int get_min(vector<int> areas)
{
  int min_side = areas[0];
  for (auto e: areas) {
    min_side = min(min_side, e);
  }
  return min_side;
}

int get_area(vector<string> data)
{
  int result = 0;
  for (auto e: data) {
    vector<int> numbers = get_numbers(e);
    assert (numbers.size() == 3);
    vector<int> areas = get_side_area(numbers);
    int cur_size = 2 * (areas[0] + areas[1] + areas[2]);
    cur_size += get_min(areas);
    result += cur_size;
  }
  return result;
}

int get_length(vector<string> data)
{
  int result = 0;
  for (auto e: data) {
    vector<int> sides = get_numbers(e);
    sort(sides.begin(), sides.end());
    int length = 2 * (sides[0] + sides[1]);
    length += sides[0] * sides[1] * sides[2];
    result += length;
  }
  return result;
}

int main()
{
  vector<string> data = get_lines();
  for (auto e: data) {
    cout << e << endl;
  }
  cout << "wrap: " << get_area(data) << endl;
  cout << "ribbon: " << get_length(data) << endl;
  return 0;
}
