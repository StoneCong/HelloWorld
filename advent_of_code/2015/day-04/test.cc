#include "../../../include/txt_file.hpp"
#include "md5.h"

int main()
{
  vector<string> data = get_lines();
  string hash_result;
  string base = data[0];
  for (int i = 0; i < 99999999; i++) {
    string text = base + to_string(i);
    hash_result = md5(text.c_str());
    bool found = true;
    for (int j = 0; j < 6; j++) {
      if (hash_result[j] != '0') {
        found = false;
        break;
      }
    }
    if (!found) continue;
    cout << i << endl;
    break;
  }
  return 0;
}


/*
*/
