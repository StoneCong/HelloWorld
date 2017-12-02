#include "../../../include/txt_file.hpp"

void get_parts(string line, vector<string>& texts, vector<string>& hyper_texts)
{
  // segment the line into parts and push the right parts into right vectors

}

int main()
{
  vector<string> data = get_lines();

  for (auto e: data) {
    vector<string> texts;
    vector<string> hyper_texts;
    get_parts(e, texts, hyper_texts);
    cout << texts[0] << hyper_texts[0] << "\n";
  }

  return 0;
}
