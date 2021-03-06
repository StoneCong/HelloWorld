#include "../../../include/txt_file.hpp"

string get_chars(string line)
{
  string result;
  for (auto e: line) {
    if (isdigit(e)) break;
    if (isalpha(e)) result += e;
  }
  return result;
}

bool myfunction(pair<int, char>& lhs, pair<int, char>& rhs)
{
  if (lhs.first > rhs.first) return true;
  if (lhs.first < rhs.first) return false;
  if (lhs.second < rhs.second) return true;
  return false;
}

int get_checksum(string line)
{
  vector<int> numbers = get_numbers(line);
  return numbers[0];
}

string get_target(string line)
{
  int start = 0;
  int end = 0;
  for (int i = 0; i < line.size(); i++) {
    if (line[i] == '[') {
      start = i + 1;
    } else if (line[i] == ']') {
      end = i - 1;
      break;
    }
  }

  return line.substr(start, end - start + 1);
}

int get_line_result(string line)
{
  string chars = get_chars(line);
  // printf("%s\n", chars.c_str());
  unordered_map<char, int> dict;
  for (auto e: chars) {
    if (dict.find(e) == dict.end()) {
      dict[e] = 1;
    } else {
      dict[e]++;
    }
  }

  // sort the dict by count first
  vector<pair<int, char>> freqs;
  for (auto e: dict) {
    freqs.push_back(make_pair(e.second, e.first));
  }

  sort(freqs.begin(), freqs.end(), myfunction);
  string top_five_string;
  for (auto e: freqs) {
    top_five_string += e.second;
    if (top_five_string.size() == 5) break;
  }

  // printf("%s\n", top_five_string.c_str());
  string target = get_target(line);
  // printf("%s\n", target.c_str());

  if (top_five_string == target) {
    return get_checksum(line);
  }

  return 0;
}

char get_clear_char(char c, int shift_count)
{
  int result = c - 'a';
  result += shift_count;
  result %= 26;
  return result + 'a';
}

string get_message(string line, int shift_count)
{
  string result;

  for (auto e: line) {
    if (isalpha(e)) {
      result += get_clear_char(e, shift_count);
      continue;
    }
    if (e == '-') {
      result += ' ';
      continue;
    }
    if (isdigit(e)) break;
  }

  return result;
}

void get_clear_texts(const vector<string>& data,
                     vector<pair<string, int>>& clear_texts)
{
  for (auto e: data) {
    int sector = get_checksum(e);
    string message = get_message(e, sector);
    clear_texts.push_back(make_pair(message, sector));
  }
  return;
}

int main()
{
  vector<string> data = get_lines();

  /*
    aaaaa-bbb-z-y-x-123[abxyz]
    a-b-c-d-e-f-g-h-987[abcde]
    not-a-real-room-404[oarel]
    totally-real-room-200[decoy]
   */

  int sum = 0;

  for (auto e: data) {
    sum += get_line_result(e);
  }

  printf("Result = %d\n", sum);

  // part II: decipher the message
  vector<pair<string, int>> clear_texts;
  get_clear_texts(data, clear_texts);

  for (auto e: clear_texts) {
    printf("%s: %d\n", e.first.c_str(), e.second);
  }
}
