#include "../../../include/txt_file.hpp"
#include "md5.h"

int main()
{
  // http://www.zedwood.com/article/cpp-md5-function
  // g++ test.cc md5.cpp -o test.out && ./test.out
  string result = md5("abc3231929");
  printf("Result = %s\n", result.c_str());
  result = md5("abc5017308");
  printf("Result = %s\n", result.c_str());

  string code;
  string base = "ffykfhsq";
  for (int i = 0; i < 99999999; i++) {
    string text = base + to_string(i);
    result = md5(text.c_str());
    bool found = true;
    for (int j = 0; j < 5; j++) {
      if (result[j] != '0') {
        found = false;
        break;
      }
    }
    if (!found) continue;
    printf("Result (%s) = %s\n", text.c_str(), result.c_str());
    code += result[5];
    if (code.size() == 8) break;
  }

  printf("code = %s\n", code.c_str());

  return 0;
}
