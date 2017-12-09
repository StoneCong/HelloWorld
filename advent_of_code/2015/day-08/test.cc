#include "../../../include/txt_file.hpp"

int get_memory_length(string line)
{
  int count = 0;
  int cur = 1;

  assert(line.size() >= 2);
  assert(line.front() == '\"');
  assert(line.back() == '\"');

  while (cur < line.size() - 1) {
    if (line[cur++] != '\\') {
      count++;
      continue;
    }
    if (line[cur++] != 'x') {
      count++;
      continue;
    }
    cur += 2;
    count++;
  }

  return count;
}

void part_1(const vector<string>& data)
{
  int string_length = 0;
  int memory_length = 0;

  for (auto e: data) {
    string_length += e.size();
    memory_length += get_memory_length(e);
  }

  cout << string_length - memory_length << endl;
}

int get_encode_length(string line)
{
  int result = 6;
  int cur = 1;
  while (cur < line.size() - 1) {
    if (line[cur] == '\\') {
      result += 2;
    } else if (line[cur] == '\"') {
      result += 2;
    } else {
      result++;
    }
    cur++;
  }
  return result;
}

void part_2(const vector<string>& data)
{
  int string_length = 0;
  int encode_length = 0;

  for (auto e: data) {
    string_length += e.size();
    encode_length += get_encode_length(e);
  }

  cout << encode_length - string_length << endl;
}

int main()
{
  vector<string> data = get_lines();

  part_1(data);
  part_2(data);

  return 0;
}
