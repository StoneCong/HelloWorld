#include "../../../include/txt_file.hpp"

void get_parts(string line, vector<string>& texts, vector<string>& hyper_texts)
{
  // segment the line into parts and push the right parts into right vectors
  int start = 0;
  int end = 0;
  bool processing = false;
  texts.clear();
  hyper_texts.clear();
  for (int i = 0; i < line.size(); i++) {
    char c = line[i];
    if (!processing) {
      if (isalpha(c)) {
        start = i;
        end = i;
        processing = true;
      }
      continue;
    }

    if (isalpha(c)) {
      end = i;
      continue;
    }

    processing = false;

    string segment = line.substr(start, end - start + 1);
    // cout << "segment: " << segment << "\n";

    if (c == '[') {
      texts.push_back(segment);
      continue;
    }

    hyper_texts.push_back(segment);
  }

  if (processing) {
    string segment = line.substr(start, end - start + 1);
    // cout << "last segment: " << segment << "\n";
    if (line.back() == ']') {
      hyper_texts.push_back(segment);
    } else {
      texts.push_back(segment);
    }
  }
}

bool has_pattern(string word)
{
  for (int i = 0; i < word.size() - 3; i++) {
    if (word[i] == word[i+1]) continue;
    if (word[i] != word[i + 3]) continue;
    if (word[i + 1] != word[i + 2]) continue;
    return true;
  }

  return false;
}

bool has_pattern(vector<string>& texts)
{
  for (auto e: texts) {
    if (has_pattern(e)) return true;
  }
  return false;
}

int main()
{
  vector<string> data = get_lines();
  int count = 0;

  for (auto e: data) {
    vector<string> texts;
    vector<string> hyper_texts;
    get_parts(e, texts, hyper_texts);
    if (has_pattern(hyper_texts)) {
      continue;
    }
    if (has_pattern(texts)) {
      count++;
      // cout << "found:" << texts[0] << "\n";
    }
  }

  cout << "Result: " << count << "\n";

  return 0;
}
