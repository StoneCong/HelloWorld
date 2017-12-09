
#include <assert.h>
#include <stdio.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

using namespace std;

vector<string> get_lines(string path="data.txt")
{
  vector<string> result;
  ifstream infile(path);
  string line;
  while (getline(infile, line)) {
    result.push_back(line);
    cout << line << endl;
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

typedef int (*my_filter)(int);

vector<string> get_terms_internal(string line, my_filter filter_func)
{
  vector<string> words;
  bool processing = false;
  string word;
  for (int i = 0; i < line.size(); i++) {
    char c = line[i];
    if (!processing) {
      if (filter_func(c)) {
        processing = true;
        word.clear();
        word.append(1, c);
      }
      continue;
    }
    if (filter_func(c)) {
      word.append(1, c);
      continue;
    }
    processing = false;
    words.push_back(word);
  }
  if (processing) {
    words.push_back(word);
  }
  return words;
}

inline vector<string> get_words(string line)
{
  return get_terms_internal(line, isalpha);
}

inline vector<string> get_terms(string line)
{
  return get_terms_internal(line, isalnum);
}

int custom_filter(int c)
{
  string extra_valid_chars = "_";
  if (isalnum(c)) return true;
  for (auto e: extra_valid_chars) {
    if (e == c) return true;
  }
  return false;
}

inline vector<string> get_custom_words(string line)
{
  return get_terms_internal(line, custom_filter);
}

void split_line(string line, string delim, string& first, string& second)
{
  size_t pos = line.find(delim);
  if (pos == string::npos) {
    first = line;
    second.clear();
    return;
  }
  first = line.substr(0, pos);
  second = line.substr(pos + delim.size());
}

vector<string> split_line(string line, string delim)
{
  vector<string> result;
  for (;;) {
    size_t pos = line.find(delim);
    if (pos == string::npos) {
      result.push_back(line);
      break;
    }
    result.push_back(line.substr(0, pos));
    line = line.substr(pos + delim.size());
  }
  return result;
}

int signed_number_filter(int c)
{
  string extra_valid_chars = "-";
  if (isdigit(c)) return true;
  for (auto e: extra_valid_chars) {
    if (e == c) return true;
  }
  return false;
}

vector<int> get_signed_numbers(string line)
{
  vector<int> numbers;
  for (auto e: get_terms_internal(line, signed_number_filter)) {
    numbers.push_back(stoi(e));
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
