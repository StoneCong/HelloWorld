
#include <assert.h>
#include <stdio.h>

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// For example: get_lines("./test.txt")
vector<string> get_lines(string path="data.txt")
{
  vector<string> result;
  ifstream infile(path);
  string line;
  while (getline(infile, line))
  {
    result.push_back(line);
  }
  return result;
}

bool is_num_digit(char c, int base)
{
  if (base <= 10) {
    if (c < '0') return false;
    return (c <= '0' + base - 1);
  }

  assert(base > 10 && base <= 16);
  if (c <= '9' && c >= '0') return true;
  return (c <= 'A' + base - 11 && c >= 'A');
}

int get_digit(char c, int base)
{
  assert(is_num_digit(c, base));

  if (base <= 10) {
    return c - '0';
  }

  assert(base > 10 && base <= 16);
  if (c <= '9' && c >= '0') return c - '0';
  return c - 'A' + 10;
}

vector<int> get_numbers(string line, int base=10)
{
  vector<int> numbers;

  int sum = 0;
  bool processing_number = false;
  for (int i = 0; i < line.size(); i++) {
    char c = line[i];
    if (!processing_number) {
      if (is_num_digit(c, base)) {
        processing_number = true;
        sum = get_digit(c, base);
      }
      continue;
    }

    if (is_num_digit(c, base)) {
      sum *= base;
      sum += get_digit(c, base);
      continue;
    }

    processing_number = false;
    numbers.push_back(sum);
  }

  if (processing_number) {
    numbers.push_back(sum);
  }

  return numbers;
}

struct PairHasher
{
  size_t operator()(const pair<int, int>& k) const
  {
    return (k.first << 16 | k.second);
  }
};
