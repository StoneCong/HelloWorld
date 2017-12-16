#include "../../../include/txt_file.hpp"

void part_1()
{
  vector<string> data = get_lines();
  vector<string> terms = split_line(data[0], ",");
  string input = "abcdefghijklmnop";
  for (auto e: terms) {

    vector<int> numbers = get_numbers(e);

    if ('s' == e[0]) {
      assert(numbers.size() == 1);
      string first = input.substr(0, input.size() - numbers[0]);
      string second = input.substr(input.size() - numbers[0]);
      input = second + first;
      continue;
    }

    assert('x' == e[0] || 'p' == e[0]);

    if ('p' == e[0]) {
      assert(numbers.size() == 0);
      numbers.push_back((int)(input.find(e[1])));
      numbers.push_back((int)(input.find(e[3])));
    }

    assert(numbers.size() == 2);
    char temp = input[numbers[0]];
    input[numbers[0]] = input[numbers[1]];
    input[numbers[1]] = temp;
  }
  cout << input << endl;
}

void part_2()
{
  vector<string> data = get_lines();
  vector<string> terms = split_line(data[0], ",");
  string input = "abcdefghijklmnop";
  map<string, string> dict;
  int loop_count = 0;
  for (int i = 0; i < 1000000000; i++) {

    if (i % 100000 == 0) cout << i << endl;

    // TODO: there is a closed loop: need to identify the length of the loop
    //       and then mod the loop length to jump to the result directly
    if (dict.find(input) != dict.end()) {
      input = dict[input];
      continue;
    }

    string original = input;
    for (auto e: terms) {
      vector<int> numbers = get_numbers(e);
      if ('s' == e[0]) {
        assert(numbers.size() == 1);
        string first = input.substr(0, input.size() - numbers[0]);
        string second = input.substr(input.size() - numbers[0]);
        input = second + first;
        continue;
      }
      assert('x' == e[0] || 'p' == e[0]);
      if ('p' == e[0]) {
        assert(numbers.size() == 0);
        numbers.push_back((int)(input.find(e[1])));
        numbers.push_back((int)(input.find(e[3])));
      }
      assert(numbers.size() == 2);
      char temp = input[numbers[0]];
      input[numbers[0]] = input[numbers[1]];
      input[numbers[1]] = temp;
    }
    dict[original] = input;
    cout << "new hit: " << input << endl;
  }
  cout << input << endl;
}

int main()
{
  part_1();
  part_2();
  return 0;
}
