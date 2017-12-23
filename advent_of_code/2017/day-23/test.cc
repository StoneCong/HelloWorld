#include "../../../include/txt_file.hpp"

int main()
{
  vector<string> data = get_lines();
  map<string, int> registers;

  int cur = 0;
  int count = 0;
  for(;;) {
    if (cur < 0 || cur >= data.size()) break;
    string instr = data[cur];
    vector<string> terms = split_line(instr, " ");
    vector<int> numbers = get_signed_numbers(instr);
    if (terms[0] == "jnz") {
      if (numbers.size() == 1) {
        int num = registers[terms[1]];
        if (num == 0) {
    	  cur++;
        } else {
	  cur += numbers[0];
        }
      } else {
	if (numbers[0] == 0) {
	  cur++;
	} else {
	  cur += numbers[1];
	}
      }
      continue;
    }
    if (numbers.size() == 0) {
      numbers.push_back(registers[terms[2]]);
    }
    if (terms[0] == "set") {
      registers[terms[1]] = numbers[0];
      cur++;
      continue;
    }
    if (terms[0] == "sub") {
      registers[terms[1]] -= numbers[0];
      cur++;
      continue;
    }
    if (terms[0] == "mul") {
      registers[terms[1]] *= numbers[0];
      cur++;
      count++;
      continue;
    }
  }
  cout << count << endl;
  return 0;
}
