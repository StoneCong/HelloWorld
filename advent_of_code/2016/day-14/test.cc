#include "../../../include/txt_file.hpp"

#include "md5.h"

string get_hash(string text, map<string, string>& dict)
{
  if (dict.find(text) != dict.end()) {
    return dict[text];
  }
  
  string hash_result = md5(text.c_str());
  for (int k = 0; k < 2016; k++) {
    hash_result = md5(hash_result.c_str());
  }
  dict[text] = hash_result;
  return hash_result;
}

string get_code(string base)
{
  string hash_result;
  string code;
  int key_count = 0;
  map<string, string> dict;
  for (int i = 0; i < 99999999; i++) {
    if (i % 1000 == 0) cout << i << endl;
    string text = base + to_string(i);
    hash_result = get_hash(text, dict);
    bool found = false;
    char c = 0;
    for (int j = 0; j < hash_result.size() - 2; j++) {
      if (hash_result[j] == hash_result[j + 1] &&
	  hash_result[j] == hash_result[j + 2]) {
        found = true;
	c = hash_result[j];
        break;
      }
    }
    if (!found) continue;
    found = false;    
    for (int j = 1; j <= 1000; j++) {
      string text = base + to_string(i + j);
      hash_result = get_hash(text, dict);
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
  get_code("yjdafjpo");
  return 0;
}
