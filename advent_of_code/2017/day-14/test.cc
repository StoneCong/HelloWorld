#include "../../../include/txt_file.hpp"

void reverse(vector<int>& numbers, int cur, int value)
{
  int size = numbers.size();
  cur = cur % size;
  value = value % size;
  vector<int> temp = numbers;
  temp.insert(temp.end(), numbers.begin(), numbers.end());
  reverse(temp.begin() + cur, temp.begin() + cur + value);
  numbers.clear();
  for (int i = size; i < size + cur; i++) {
    numbers.push_back(temp[i]);
  }
  for (int i = cur; i < size; i++) {
    numbers.push_back(temp[i]);
  }
}

int get_set_bits(int c)
{
  int count = 0;
  while(c) {
    if (c & 1) {
      count++;
    }
    c >>= 1;
  }
  return count;
}

int get_set_bits(string temp)
{
  int count = 0;
  for (auto e: temp) {
    int digit = get_digit(e, 16);
    count += get_set_bits(digit);
  }
  return count;
}

string get_knot_hash(string data)
{
  int skip = 0;
  int cur = 0;
  vector<int> numbers;
  vector<int> input;
  char buffer[64];

  for (int i = 0; i < 256; i++) {
    numbers.push_back(i);
  }

  for (auto e: data) {
    input.push_back(e);
  }

  input.push_back(17);
  input.push_back(31);
  input.push_back(73);
  input.push_back(47);
  input.push_back(23);

  for (int i = 0; i < 64; i++) {
    for (auto e: input) {
      reverse(numbers, cur, e);
      cur += (e + skip++);
    }
  }

  vector<int> dense;

  for (int outer = 0; outer < 256; outer += 16) {
    int value = 0;
    for (int inner = 0; inner < 16; inner++) {
      value ^= numbers[outer + inner];
    }
    dense.push_back(value);
  }

  for (int i = 0; i < dense.size(); i++) {
    sprintf(buffer + i*2, "%02x", dense[i]);
  }

  return buffer;
}

void part_1()
{
  string seed = "ljoxqyyw-";

  int hash_count = 0;
  for (int i = 0; i < 128; i++) {
    string temp = seed + to_string(i);
    string hash = get_knot_hash(temp);
    hash_count += get_set_bits(hash);
  }

  cout << hash_count << endl;

  return;
}

bool get_bit(int number, int offset)
{
  int mask = 1 << offset;
  return number & mask;
}

void part_2()
{
  string seed = "ljoxqyyw-";
  map<pair<int, int>, bool> dict;
  map<pair<int, int>, bool> visited;
  vector<vector<int>> data;

  for (int i = 0; i < 128; i++) {
    string temp = seed + to_string(i);
    string hash = get_knot_hash(temp);
    cout << hash << endl;
    vector<int> local;
    for (auto e: hash) {
      local.push_back(get_digit(e, 16));
    }
    data.push_back(local);
  }

  for (int row = 0; row < data.size(); row++) {
    vector<int> line = data[row];
    int col = 0;
    for (int cur = 0; cur < line.size(); cur++) {
      dict[make_pair(row, col + 0)] = get_bit(line[cur], 0);
      dict[make_pair(row, col + 1)] = get_bit(line[cur], 1);
      dict[make_pair(row, col + 2)] = get_bit(line[cur], 2);
      dict[make_pair(row, col + 3)] = get_bit(line[cur], 3);
      col += 4;
    }
    assert(col == 128);
  }

  int region_count = 0;
  for (int row = 0; row < 128; row++) {
    for (int col = 0; col < 128; col++) {
      if (!dict[make_pair(row, col)]) continue;
      if (visited[make_pair(row, col)]) continue;
      region_count++;
      queue<pair<int, int>> frontier;
      frontier.push(make_pair(row, col));
      while (frontier.size()) {
        pair<int, int> cur = frontier.front();
        frontier.pop();
        if (visited[cur]) continue;
        visited[cur] = true;
        if (!dict[cur]) continue;
        frontier.push(make_pair(row - 1, col));
        frontier.push(make_pair(row, col - 1));
        frontier.push(make_pair(row + 1, col));
        frontier.push(make_pair(row, col + 1));
      }
    }
  }

  assert(region_count == 1074);
  cout << region_count << endl;
  return;
}

int main()
{
  part_2();
  return 0;
}
