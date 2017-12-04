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

void get_marker_raw(const string& input, long long current, string& s)
{
  assert(input[current] == '(');
  s.clear();
  for ( ; current < input.size(); current++) {
    if (input[current] == ')') {
      s.append(1, input[current]);
      current++;
      break;
    }
    s.append(1, input[current]);
  }
  vector<int> numbers = get_numbers(s);
  assert(numbers.size() == 2);
  int length = numbers[0];
  s += input.substr(current, length);
}

void construct_initial_data(const string& input, map<long long, string>& data, long long& file_size)
{
  file_size = input.size();
  long long current = 0;
  while (current < input.size()) {
    if (input[current] != '(') {
      current++;
      continue;
    }
    string s;
    get_marker_raw(input, current, s);
    data[current] = s;
    current += s.size();
  }
}

void get_digest(string& segment, map<long long, string>& digest)
{
  long long file_size = 0;
  construct_initial_data(segment, digest, file_size);
}

void expand_data(map<long long, string>& data, long long& file_size)
{
  map<long long, string> result;
  long long new_file_size = file_size;

  //  track the markers and eof using a dict instead of saving the raw data
  // (6x6)AFPLBX(2x3)ZE(53x13)(4x7)ZGQO(2x4)
  // TBD: construct the initial dict to track all the markers and then feed it
  //      to a loop until all the markers are resolved
  for (auto e: data) {
    // cout << e.first << ": " << e.second << "\n";
    vector<int> numbers = get_numbers(e.second);
    long long delta = new_file_size - file_size;
    new_file_size -= e.second.size();
    new_file_size += numbers[1] * numbers[0];
    if (numbers.size() == 2) {
      // no recursive markers, this marker is done
      continue;
    }
    // there are recursive markers, add these markers back into the map
    long long new_offset = e.first + delta;
    // expand the string first
    string segment = decompress(e.second);
    map<long long, string> digest;
    get_digest(segment, digest);
    for (auto e: digest) {
      result[new_offset + e.first] = e.second;
    }
  }

  data = result;
  file_size = new_file_size;
}

long long get_length(string input)
{
  long long length = 0;
  map<long long, string> data;
  long long file_size = 0;
  construct_initial_data(input, data, file_size);

  while (data.size() != 0) {
    expand_data(data, file_size);
    cout << "data.size() = " << data.size() << "\n";
  }

  return file_size;
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
