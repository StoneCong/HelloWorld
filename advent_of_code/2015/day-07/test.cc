#include "../../../include/txt_file.hpp"

bool process_line(string line, map<string, int>& dict)
{
  vector<string> terms = split_line(line, " ");
  vector<int> numbers = get_numbers(line);

  // 123 -> x
  if (terms.size() == 3) {
    if (numbers.size()) {
      dict[terms[2]] = numbers[0];
      return true;
    }
    if (dict.find(terms[0]) == dict.end()) return false;
    dict[terms[2]] = dict[terms[0]];
    return true;
  }

  // NOT x -> h
  if (terms[0] == "NOT") {
    if (numbers.size()) {
      dict[terms[3]] = ~numbers[0];
      return true;
    }
    if (dict.find(terms[1]) == dict.end()) return false;
    dict[terms[3]] = ~dict[terms[1]];
    return true;
  }

  // x [operator] Y -> d
  if (numbers.size() == 0) {
    if (dict.find(terms[0]) == dict.end()) return false;
    if (dict.find(terms[2]) == dict.end()) return false;
    numbers.push_back(dict[terms[0]]);
    numbers.push_back(dict[terms[2]]);
  } else if (numbers.size() == 1) {
    if (isdigit(terms[0][0])) {
      if (dict.find(terms[2]) == dict.end()) return false;
      numbers.push_back(dict[terms[2]]);
    } else {
      if (dict.find(terms[0]) == dict.end()) return false;
      numbers.push_back(numbers[0]);
      numbers[0] = dict[terms[0]];
    }
  }

  assert(numbers.size() == 2);
  cout << numbers[0] << " " << numbers[1] << endl;

  // x AND Y -> d
  if (terms[1] == "AND") {
    dict[terms[4]] = numbers[0] & numbers[1];
    return true;
  }

  // x OR Y -> d
  if (terms[1] == "OR") {
    dict[terms[4]] = numbers[0] | numbers[1];
    return true;
  }

  // x LSHIFT 2 -> f
  if (terms[1] == "LSHIFT") {
    dict[terms[4]] = numbers[0] << numbers[1];
    return true;
  }

  // y RSHIFT 2 -> g
  if (terms[1] == "RSHIFT") {
    dict[terms[4]] = numbers[0] >> numbers[1];
    return true;
  }

  cout << line << endl;
  assert(false);
  return false;
}

int main()
{
  vector<string> data = get_lines();
  map<string, int> dict;
  while (data.size()) {
    vector<string> left_over;
    for (int i = 0; i < data.size(); i++) {
      if (!process_line(data[i], dict)) {
        left_over.push_back(data[i]);
      }
    }
    data = left_over;
  }
  cout << "wire a == " << dict["a"] << endl;
  return 0;
}
