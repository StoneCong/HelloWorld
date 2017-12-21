/*
  https://adventofcode.com/2016/day/6
 */

#include "../../../include/txt_file.hpp"

char get_most_frequent_char(vector<string>& data, int position)
{
  unordered_map<char, int> dict;
  for (auto e: data) {
    char c = e[position];
    if (dict.find(c) == dict.end()) {
      dict[c] = 1;
    } else {
      dict[c]++;
    }
  }
  pair<char, int> result = make_pair('a', 0);
  for (auto e: dict) {
    if (e.second <= result.second) continue;
    result = e;
  }
  return result.first;
}

char get_least_frequent_char(vector<string>& data, int position)
{
  unordered_map<char, int> dict;
  for (auto e: data) {
    char c = e[position];
    if (dict.find(c) == dict.end()) {
      dict[c] = 1;
    } else {
      dict[c]++;
    }
  }
  pair<char, int> result = make_pair('a', 99999);
  for (auto e: dict) {
    if (e.second >= result.second) continue;
    result = e;
  }
  return result.first;
}

int main()
{
  vector<string> data = get_lines();

  for (auto e: data) {
    cout << e << "\n";
  }

  string code;
  for (int i = 0; i < data[0].size(); i++) {
    code += get_most_frequent_char(data, i);
  }

  cout << "The message is: " << code << "\n";

  code.clear();

  for (int i = 0; i < data[0].size(); i++) {
    code += get_least_frequent_char(data, i);
  }

  cout << "The message is: " << code << "\n";


  return 0;
}
