#include "../../../include/txt_file.hpp"

string look_say(string s)
{
  string result;
  char c = s[0];
  int count = 1;
  for (int i = 1; i < s.size(); i++) {
    if (s[i] == c) {
      count++;
      continue;
    }
    result += to_string(count);
    result.append(1, c);
    c = s[i];
    count = 1;
  }
  result += to_string(count);
  result.append(1, c);
  return result;
}

int main()
{
  string s = "1113222113";
  for (int i = 0; i < 50; i++) {
    s = look_say(s);
  }
  cout << s.size() << endl;
}
