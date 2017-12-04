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

bool contain_marker(string input)
{
  for (auto e: input) {
    if (e == '(') return true;
  }
  return false;
}

void part_1()
{
  vector<string> data = get_lines();
  assert (data.size() == 1);
  cout << decompress(data[0]).size() << "\n";
}

void construct_initial_data(const string& input, unordered_map<pair<int, int>, string, PairHasher>& data, int& file_size)
{
  string result;
  int current = 0;
  /*
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
  */
}

long long get_length(string input)
{
  long long length = 0;
  unordered_map<pair<int, int>, string, PairHasher> data;
  //  track the markers and eof using a dict instead of saving the raw data
  // (6x6)AFPLBX(2x3)ZE(53x13)(4x7)ZGQO(2x4)
  // TBD: construct the initial dict to track all the markers and then feed it
  //      to a loop until all the markers are resolved
  int file_size = 0;
  construct_initial_data(input, data, file_size);
  return length;
}

void part_2()
{
  vector<string> data = get_lines();
  assert (data.size() == 1);
  cout << "part 2 result: " << get_length(data[0]) << "\n";
  // if (!contain_marker(new_result)) break;
}

int main()
{
  // part_1();
  part_2();
  return 0;
}
