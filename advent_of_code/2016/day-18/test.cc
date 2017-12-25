#include "../../../include/txt_file.hpp"

char get_tile_type(char left, char center, char right)
{
  if (left == '^' && center == '^' && right == '.') return '^';
  if (left == '.' && center == '^' && right == '^') return '^';
  if (left == '^' && center == '.' && right == '.') return '^';
  if (left == '.' && center == '.' && right == '^') return '^';
  return '.';
}

string get_next_row(string input)
{
  string result;
  for (int col = 0; col < input.size(); col++) {
    char left  = (col == 0) ? '.' : input[col - 1];
    char right = (col == input.size() - 1) ? '.' : input[col + 1];
    result.append(1, get_tile_type(left, input[col], right));
  }
  return result;
}

int main()
{
  string input = ".^..^....^....^^.^^.^.^^.^.....^.^..^...^^^^^^.^^^^.^.^^^^^^^.^^^^^..^.^^^.^^..^.^^.^....^.^...^^.^.";
  vector<string> rows;
  rows.push_back(input);
  for (int row = 1; row < 400000; row++) {
    rows.push_back(get_next_row(rows[row - 1]));
  }
  int count = 0;
  for (auto row: rows) {
    for (auto c: row) {
      if (c == '.') count++;
    }
  }
  cout << count << endl;
  return 0;
}
