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

int part_1()
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

  cout << "Part 1 Result: " << count << "\n";
  return 0;
}

vector<string> get_xyx_set(const vector<string>& texts)
{
  vector<string> result;

  for (auto e: texts) {
    for (int i = 0; i < e.size() - 2; i++) {
      if (e[i] != e[i + 2]) continue;
      result.push_back(e.substr(i, 3));
    }
  }

  return result;
}

bool has_element(const vector<string>& texts, string pattern)
{
  for (auto e: texts) {
    if (e.find(pattern) != string::npos) return true;
  }
  return false;
}

int part_2()
{
  vector<string> data = get_lines();
  int count = 0;

  for (auto e: data) {
    vector<string> texts;
    vector<string> hyper_texts;
    get_parts(e, texts, hyper_texts);
    vector<string> xyx_set = get_xyx_set(hyper_texts);
    bool found = false;
    for (auto element : xyx_set) {
      string new_element;
      new_element.append(1, element[1]);
      new_element.append(1, element[0]);
      new_element.append(1, element[1]);
      if (has_element(texts, new_element)) {
        found = true;
        break;
      }
    }
    if (found) {
      count++;
    }
  }

  cout << "Part 2 Result: " << count << "\n";
  return 0;
}

int main()
{
  part_1();
  part_2();
  return 0;
}
