#include "../../../include/txt_file.hpp"

void update_number(string line,
                   map<string, int>& dict,
                   int& max_ever)
{
  // words, for example, is: "b inc 5 if a > 1"
  vector<string> words = split_line(line, " ");
  int v1 = 0, v2 = 0, v3, v4;
  string r1 = words[0];
  string r2 = words[4];

  if (dict.find(r1) != dict.end()) {
    v1 = dict[r1];
  }
  if (dict.find(r2) != dict.end()) {
    v2 = dict[r2];
  }

  v3 = stoi(words[2]);
  v4 = stoi(words[6]);

  if (line.find(">=") != string::npos) {
    if (v2 < v4) return;
  } else if (line.find("<=") != string::npos) {
    if (v2 > v4) return;
  } else if (line.find("==") != string::npos) {
    if (v2 != v4) return;
  } else if (line.find("!=") != string::npos) {
    if (v2 == v4) return;
  } else if (line.find("<") != string::npos) {
    if (v2 >= v4) return;
  } else if (line.find(">") != string::npos) {
    if (v2 <= v4) return;
  } else {
    cout << line << endl;
    assert(false);
  }
  assert(words[1] == "inc" || words[1] == "dec");
  v1 = (words[1] == "inc") ? v1 + v3 : v1 - v3;
  dict[r1] = v1;
  max_ever = max(max_ever, v1);
}

int main()
{
  vector<string> data = get_lines();
  map<string, int> dict;

  int max_ever = INT_MIN;
  for (auto e: data) {
    update_number(e, dict, max_ever);
  }

  int max = INT_MIN;
  for (auto e: dict) {
    if (e.second > max) {
      max = e.second;
    }
  }
  cout << "max result: " << max      <<  endl;
  cout << "max ever:   " << max_ever <<  endl;

  return 0;
}
