#include "../../../include/txt_file.hpp"

bool is_valid(string e)
{
  vector<string> words = get_words(e);
  map<string, int> dict;
  for (auto e: words) {
    if (dict.find(e) != dict.end()) return false;
    dict[e] = 1;
  }
  return true;
}

void part_1()
{
  vector<string> data = get_lines();
  int count = 0;
  for (auto e: data) {
    if (is_valid(e)) count++;
  }
  cout << count << "\n";
}

bool is_valid_2(string e)
{
  vector<string> words = get_words(e);
  map<string, int> dict;
  for (auto e: words) {
    sort(e.begin(), e.end());
    if (dict.find(e) != dict.end()) return false;
    dict[e] = 1;
  }
  return true;
}

void part_2()
{
  vector<string> data = get_lines();
  int count = 0;
  for (auto e: data) {
    if (is_valid_2(e)) count++;
  }
  cout << count << "\n";
}

int main()
{
  part_1();
  part_2();
  return 0;
}
