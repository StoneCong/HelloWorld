#include "../../../include/txt_file.hpp"

void process_garbage(string line, int& cur, int& total_count)
{
  assert(line[cur] == '<');
  cur++;
  for (;;) {
    if (cur >= line.size()) break;
    char c = line[cur];
    if (c == '!') {
      cur += 2;
      continue;
    }
    if (c == '>') {
      cur++;
      break;
    }
    total_count++;
    cur++;
  }
}

int main()
{
  vector<string> data = get_lines();
  stack<char> s;
  int cur = 0;
  int score = 0;
  int total_count = 0;
  for (;;) {
    if (cur >= data[0].size()) break;
    char e = data[0][cur];
    switch (e) {
    case '{':
      s.push(e);
      cur++;
      break;
    case '}':
      score += s.size();
      s.pop();
      cur++;
      break;
    case '<':
      process_garbage(data[0], cur, total_count);
      break;
    default:
      cur++;
      break;
    }
  }
  cout << "total score: " << score << endl;
  cout << "total count: " << total_count << endl;
  return 0;
}
