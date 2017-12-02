#include "../../../include/txt_file.hpp"
#include "md5.h"

string get_code_part_1(string base)
{
  string hash_result;
  string code;

  for (int i = 0; i < 99999999; i++) {
    string text = base + to_string(i);
    hash_result = md5(text.c_str());
    bool found = true;
    for (int j = 0; j < 5; j++) {
      if (hash_result[j] != '0') {
        found = false;
        break;
      }
    }
    if (!found) continue;
    printf("Result (%s) = %s\n", text.c_str(), hash_result.c_str());
    code += hash_result[5];
    if (code.size() == 8) break;
  }
  return code;
}

string get_code_part_2(string base)
{
  string hash_result;
  string code(8, 'x');
  for (int i = 0; i < 99999999; i++) {
    string text = base + to_string(i);
    hash_result = md5(text.c_str());
    bool found = true;
    for (int j = 0; j < 5; j++) {
      if (hash_result[j] != '0') {
        found = false;
        break;
      }
    }
    if (!found) continue;
    int position = hash_result[5] - '0';
    if (position < 0 || position > 7) {
      continue;
    }
    if (code[position] != 'x') continue;
    code[position] = hash_result[6];
    printf("Code: %s\n", code.c_str());
    found = false;
    for (auto e: code) {
      if (e == 'x') {
        found = true;
      }
    }
    if (!found) break;
  }
  return code;
}

int main()
{
  // http://www.zedwood.com/article/cpp-md5-function
  // g++ test.cc md5.cpp -o test.out && ./test.out
  string base = "ffykfhsq";
  string code;

  code = get_code_part_1(base);
  printf("part 1: code = %s\n", code.c_str());

  code = get_code_part_2(base);
  printf("part 2: code = %s\n", code.c_str());

  return 0;
}
