#include "../../../include/txt_file.hpp"

string swap_position(string input, int first, int second)
{
  char temp = input[first];
  input[first] = input[second];
  input[second] = temp;
  return input;
}

string swap_letter(string input, char first, char second)
{
  size_t pos1 = input.find(first);
  size_t pos2 = input.find(second);
  return swap_position(input, pos1, pos2);
}

string rotate_string(string input, int count)
{
  if (count == 0) return input;
  
  if (count < 0) {
    // rotate left
    string left = input.substr(0, abs(count));
    string right = input.substr(abs(count));
    return right + left;
  }
  
  // rotate right
  count = count % input.size();
  string left = input.substr(0, input.size() - count);
  string right = input.substr(input.size() - count);
  return right + left;
}

string get_hash(string input, const vector<string>& data)
{
  for (auto& e: data) {
    vector<string> terms = split_line(e, " ");
    vector<int> numbers = get_numbers(e);
    if (terms[0] == "swap") {
      if (terms[1] == "position") {
	input = swap_position(input, numbers[0], numbers[1]);
      } else {
        assert(terms[1] == "letter");
        input = swap_letter(input, terms[2][0], terms[5][0]);
      }
      continue;
    }
    if (terms[0] == "rotate") {
      if (terms[1] == "left") {
	input = rotate_string(input, -1 * numbers[0]);
      } else if (terms[1] == "right") {
	input = rotate_string(input, numbers[0]);
      } else {
	assert (terms[1] == "based");
        size_t pos = input.find(terms[6]);
	if (pos >= 4) {
	  input = rotate_string(input, 2 + ((int)pos));
	} else {
	  input = rotate_string(input, 1 + ((int)pos));
	}
      }
      continue;
    }
    if (terms[0] == "reverse") {
      reverse(input.begin() + numbers[0], input.begin() + numbers[1] + 1);
      continue;
    }
    assert(terms[0] == "move");
    char temp = input[numbers[0]];
    input.erase(input.begin() + numbers[0]);
    input.insert(input.begin() + numbers[1], temp);
  }
  return input;
}

int main()
{
  map<string, string> dict;
  string input = "abcdefgh";
  vector<string> data = get_lines();
  sort(input.begin(), input.end());
  do {
    dict[input] = get_hash(input, data);
  } while (next_permutation(input.begin(), input.end()));

  for (auto& e: dict) {
    if (e.second == "fbgdceah") {
      cout << "Found: " << e.first << endl;
      break;
    }
  }
  return 0;
}
