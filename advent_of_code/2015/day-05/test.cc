#include "../../../include/txt_file.hpp"

bool is_vowel(char c)
{
  string vowels = "aeiou";
  for (auto e: vowels) {
    if (e == c) return true;
  }
  return false;
}

bool is_nice(string input)
{
  int vowel_count = 0;

  for (auto e: input) {
    if (is_vowel(e)) vowel_count++;
  }
  if (vowel_count < 3) return false;

  bool found = false;
  for (int i = 0; i < input.size() - 1; i++) {
    if (input[i] == input[i+1]) {
      found = true;
    }
  }
  if (!found) return false;

  vector<string> invalids = {"ab", "cd", "pq", "xy"};
  for (auto e: invalids) {
    if (input.find(e) != string::npos) return false;
  }

  return true;
}

bool is_nice_2(string input)
{
  bool found = false;
  for (int i = 0; i < input.size() - 3; i++) {
    string pattern = input.substr(i, 2);
    string right = input.substr(i + 2);
    if (right.find(pattern) != string::npos) {
      found = true;
      break;
    }
  }

  if (!found) return false;

  for (int i = 0; i < input.size() - 2; i++) {
    if (input[i] == input[i + 2]) return true;
  }

  return false;
}

int main()
{
  vector<string> data = get_lines();
  int count = 0;
  for (auto e: data) {
    if (is_nice_2(e)) count++;
  }
  cout << count << endl;
  return 0;
}
