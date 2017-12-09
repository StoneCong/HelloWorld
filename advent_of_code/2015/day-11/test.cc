#include "../../../include/txt_file.hpp"

string get_next(string s)
{
  for (int i = s.size() - 1; i >= 0; i--) {
    if (s[i] != 'z') {
      s[i] += 1;
      return s;
    }
    s[i] = 'a';
  }
  return s;
}

bool is_valid(string s)
{
  bool found = false;
  for (int i = 0; i < s.size() - 2; i++) {
    if (s[i] == 'y' || s[i] == 'z') continue;
    if (s[i] + 1 != s[i + 1]) continue;
    if (s[i] + 2 != s[i + 2]) continue;
    found = true;
  }
  if (!found) return false;

  for (auto e: s) {
    if (e == 'i' || e == 'o' || e == 'l') return false;
  }

  int  found_count = 0;
  char first_found = 0;
  for (int i = 0; i < s.size() -1; i++) {
    if (s[i] != s[i+1]) continue;
    if (found_count == 0) {
      first_found = s[i];
      found_count = 1;
    } else if (found_count == 1) {
      if (s[i] == first_found) continue;
      return true;
    }
  }
  return false;
}

int main()
{
  string s = "vzbxkghb";

  for (int i = 0; i < 2; i++) {
    for (;;) {
      s = get_next(s);
      if (is_valid(s)) {
        break;
      }
    }
    cout << s << endl;
  }

  return 0;
}
