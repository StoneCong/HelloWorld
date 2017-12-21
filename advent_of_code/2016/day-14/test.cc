#include "../../../include/txt_file.hpp"

#include "md5.h"

string get_code_part_1(string base)
{
  string hash_result;
  string code;
  int key_count = 0;
  for (int i = 0; i < 99999999; i++) {
    if (i % 1000 == 0) cout << i << endl;
    string text = base + to_string(i);
    hash_result = md5(text.c_str());
    bool found = false;
    char c = 0;
    for (int j = 0; j < hash_result.size() - 2; j++) {
      if (hash_result[j] == hash_result[j + 1] &&
	  hash_result[j] == hash_result[j + 2]) {
        found = true;
	c = hash_result[i];
        break;
      }
    }
    if (!found) continue;
    found = false;    
    for (int j = 1; j <= 1000; j++) {
      string text = base + to_string(i + j);
      hash_result = md5(text.c_str());
      for (int j = 0; j < hash_result.size() - 4; j++) {
        if (c == hash_result[j + 0] &&
  	    hash_result[j] == hash_result[j + 1] &&
  	    hash_result[j] == hash_result[j + 2] &&
  	    hash_result[j] == hash_result[j + 3] &&
  	    hash_result[j] == hash_result[j + 4]) {
          found = true;
          break;
        }
      }
    }
    if (!found) continue;
    key_count++;
    if (key_count == 64) {
      cout << i << endl;
      break;
    }
  }
  return code;
}

int main()
{
  get_code_part_1("yjdafjpo");
  return 0;
}
