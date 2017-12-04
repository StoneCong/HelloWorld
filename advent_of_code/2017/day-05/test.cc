#include "../../../include/txt_file.hpp"

int main()
{
  vector<int> numbers;
  vector<string> words;
  vector<string> terms;
  vector<string> data = get_lines();
  for (auto e: data) {
    // 234 456 dasd 234 abc888
    numbers = get_numbers(e);
    words = get_words(e);
    terms = get_terms(e);
    cout << numbers.size() << " " << words.size() << " " << terms.size() << "\n";
  }
  return 0;
}
