#include "../../../include/txt_file.hpp"

int get_register(string term)
{
  int register_num = term[0] - 'a';
  assert(register_num >=0 && register_num < 4);
  return register_num;
 }

int main()
{
  vector<string> data = get_lines();
  vector<int> registers(4, 0);
  registers[2] = 1;
  int cur = 0;
  for (;;) {
    if (cur >= data.size()) break;
    if (cur < 0) break;
    string instr = data[cur];
    vector<string> terms = split_line(instr, " ");
    vector<int> numbers = get_signed_numbers(instr);
    if (terms[0] == "cpy") {
      assert(terms.size() == 3);
      assert(numbers.size() <= 1);
      if (numbers.size()) {
        registers[get_register(terms[2])] = numbers[0];
      } else {
        registers[get_register(terms[2])] = registers[get_register(terms[1])];
      }
      cur++;
      continue;
    }
    if (terms[0] == "inc") {
      assert(terms.size() == 2);
      assert(numbers.size() == 0);
      registers[get_register(terms[1])] += 1;
      cur++;
      continue;
    }
    if (terms[0] == "dec") {
      assert(terms.size() == 2);
      assert(numbers.size() == 0);
      registers[get_register(terms[1])] -= 1;
      cur++;
      continue;
    }
    assert(terms[0] == "jnz");
    assert(terms.size() == 3);
    assert(numbers.size() == 1 || numbers.size() == 2);
    if (numbers.size() == 1 && registers[get_register(terms[1])] == 0) {
      cur++;
      continue;
    }
    if (numbers.size() == 2 && numbers[0] == 0) {
      cur++;
      continue;
    }
    cur += (numbers.size() == 1 ? numbers[0] : numbers[1]);
  }
  cout << registers[0] << endl;
  return 0;
}
