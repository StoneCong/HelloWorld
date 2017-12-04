#include "../../../include/txt_file.hpp"

int main()
{
  vector<int> numbers;
  vector<string> words;
  vector<string> terms;
  vector<string> custom_words;
  vector<string> data = get_lines();
  for (auto e: data) {
    // 234 456 dasd 234 abc888
    numbers = get_numbers(e);
    words = get_words(e);
    terms = get_terms(e);
    custom_words = get_custom_words(e);
    cout << numbers.size() << " " << words.size() << " " << terms.size() << " "<< custom_words.size() << "\n";
    string first, second;
    split_line(e, "zzzz", first, second);
    cout << first << "\n" << second << "\n\n";
    vector<string> final = split_line(e, "a");
    for (auto e: final) {
      cout << e << "\n";
    }
    cout << "\n";
  }
  return 0;
}
