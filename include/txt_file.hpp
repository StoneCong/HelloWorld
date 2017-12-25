#include <assert.h>
#include <math.h>
#include <stdio.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <complex>
#include <fstream>
#include <future>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <typeinfo>
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

bool is_num_digit(char cur, int base)
{
  cur = toupper(cur);
  if (base <= 10) {
    if (cur < '0') return false;
    return (cur <= '0' + base - 1);
  }
  assert(base > 10 && base <= 16);
  if (cur <= '9' && cur >= '0') return true;
  return (cur <= 'A' + base - 11 && cur >= 'A');
}

int get_digit(char cur, int base)
{
  cur = toupper(cur);
  assert(is_num_digit(cur, base));
  if (base <= 10) {
    return cur - '0';
  }
  assert(base > 10 && base <= 16);
  if (cur <= '9' && cur >= '0') return cur - '0';
  return cur - 'A' + 10;
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

vector<vector<int>> get_permutations(int size)
{
  vector<vector<int>> permutations;
  vector<int> permutation;
  for (int i = 0; i < size; i++) {
    permutation.push_back(i);
  }
  permutations.push_back(permutation);
  for (;;) {
    bool done = true;
    // Find greatest index 'i' within string such that v[i] < v[i+1]
    // If cannot find any such index, this is the last permutation.
    for (int i = size - 2; i >= 0; i--) {
      if (permutation[i] < permutation[i+1]) {
        // Find greatest index 'p' where v[i] < v[p]
        for (int j = size - 1; j > i; j--) {
          if (permutation[j] > permutation[i]) {
            // swap i and j
            int temp = permutation[i];
            permutation[i] = permutation[j];
            permutation[j] = temp;
            // reverse the content from i + 1 to end
            reverse(permutation.begin() + i + 1, permutation.end());
            permutations.push_back(permutation);
            done = false;
            break;
          }
        }
        break;
      }
    }
    if (done) break;
  }
  return permutations;
}

// function object for hashing
struct PairHasher
{
  size_t operator()(const pair<int, int>& k) const
  {
    return (k.first << 16 | k.second);
  }
};

template<typename T>
inline void print_vector(vector<T>& v)
{
  cout << "v(" << v.size() << "):";
  for (auto e: v) {
    cout << " " << e;
  }
  cout << endl;
}

inline void print_vector(vector<int>& v)
{
  print_vector<int>(v);
}

inline void print_vector(vector<long long>& v)
{
  print_vector<long long>(v);
}

inline void print_vector(vector<string>& v)
{
  cout << "v(" << v.size() << "):";
  for (auto e: v) {
    cout << " \"" << e << "\"";
  }
  cout << endl;
}

inline void print_vector(vector<pair<int, int>>& v)
{
  cout << "v(" << v.size() << "):";
  for (auto e: v) {
    cout << " (" << e.first << ","<< e.second << ")";
  }
  cout << endl;
}

inline int get_random_number(int low, int high)
{
  // [low, high)
  random_device rd;
  mt19937 mt(rd());
  uniform_real_distribution<double> dist(low * 1.0, high * 1.0);
  return dist(mt);
}

enum direction {
  N = 0,
  E = 1,
  S = 2,
  W = 3
};

direction turn_right(direction cur_dir)
{
  return (direction)((cur_dir + 1) % 4);
}

direction turn_left(direction cur_dir)
{
  return (direction)((cur_dir + 3) % 4);
}

// cur_pos.first:  row
// cur_pos.second: column
pair<int, int> next_location(pair<int, int> cur_pos, direction d)
{
  switch (d) {
  case N:
    return make_pair(cur_pos.first - 1, cur_pos.second);
  case S:
    return make_pair(cur_pos.first + 1, cur_pos.second);
  case W:
    return make_pair(cur_pos.first, cur_pos.second - 1);
  case E:
    return make_pair(cur_pos.first, cur_pos.second + 1);
  }
  cout << d << endl;
  assert(false);
  return make_pair(0, 0);
}
