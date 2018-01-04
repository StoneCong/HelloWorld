#include "../../../include/txt_file.hpp"

int main()
{
  vector<string> data = get_lines();

  map<string, int> registers;
  int cur = 0;
  for (;;) {
    vector<string> terms = split_line(data[cur]);
    vector<int> numbers = get_signed_numbers(data[cur]);
    if (terms[0] == "cpy") {
      if (numbers.size() == 0) {
	registers[terms[2]] = registers[terms[1]];
      } else if (numbers.size() == 1) {
	registers[terms[2]] = numbers[0];
      }
      cur++;
      continue;
    }
    if (terms[0] == "dec") {
      if (numbers.size() == 0) {
	registers[terms[1]] -= 1;
      }
      cur++;
      continue;
    }
    if (terms[0] == "inc") {
      if (numbers.size() == 0) {
	registers[terms[1]] += 1;
      }
      cur++;
      continue;
    }
    if (terms[0] == "jnz") {
      if (numbers.size() == 2 && numbers[0]) {
        cur += numbers[1];
	continue;
      }
      if (numbers.size() == 1 && registers[terms[1]]) {
      }
      cur++;
      continue;
    }
  }
}
