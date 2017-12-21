#include "../../../include/txt_file.hpp"
#include <algorithm>

void print_vector(vector<int>& numbers)
{
  printf("v(%d):", (int)numbers.size());
  for (auto e: numbers) {
    printf(" %d", e);
  }
  printf("\n");
}

bool is_valid_triangle(vector<int> sizes)
{
  sort(sizes.begin(), sizes.end());
  return sizes[0] + sizes[1] > sizes[2];
}

vector<vector<int>> transform_lines(vector<vector<int>>& lines)
{
  vector<vector<int>> result;

  for (int i = 0; i < lines.size(); i += 3) {
    for (int j = 0; j < 3; j++) {
      vector<int> triangle;
      for (int k = 0; k < 3; k++) {
        triangle.push_back(lines[i + k][j]);
      }
      result.push_back(triangle);
    }
  }

  return result;
}

int main()
{
  vector<string> raw_lines = get_lines("data.txt");
  vector<vector<int>> lines;
  for (auto e: raw_lines) {
    vector<int> numbers = get_numbers(e);
    lines.push_back(numbers);
  }

  int count = 0;
  for (auto e: lines) {
    if (is_valid_triangle(e)) {
      ++count;
    }
  }

  printf("Result: %d\n", count);

  vector<vector<int>> new_lines = transform_lines(lines);

  count = 0;
  for (auto e: new_lines) {
    if (is_valid_triangle(e)) {
      ++count;
    }
  }

  printf("Result: %d\n", count);

  return 0;
}
