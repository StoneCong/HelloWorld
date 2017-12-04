#include "../../../include/txt_file.hpp"

void get_marker(string input, int& current, string& s, int& count)
{
  assert(input[current] == '(');
  string segment;
  current++;
  for (;current < input.size(); current++) {
    if (input[current] == ')') {
      current++;
      break;
    }
    segment.append(1, input[current]);
  }
  vector<int> numbers = get_numbers(segment);
  assert(numbers.size() == 2);
  int length = numbers[0];
  count = numbers[1];
  s = input.substr(current, length);
  current += length;
}

string decompress(string input)
{
  string result;
  int current = 0;
  // (6x6)AFPLBX(2x3)ZE(53x13)(4x7)ZGQO(2x4)
  while (current < input.size()) {
    char c = input[current];
    if (c != '(') {
      result.append(1, c);
      current++;
      continue;
    }
    string s;
    int count;
    get_marker(input, current, s, count);
    for (int i = 0; i < count; i++) {
      result += s;
    }
  }
  return result;
}

int main()
{
  vector<string> data = get_lines();
  assert (data.size() == 1);
  string input = data[0];
  // cout << input << "\n";
  string result = decompress(input);
  cout << result.size() << ": "<< result << "\n";
  return 0;
}
