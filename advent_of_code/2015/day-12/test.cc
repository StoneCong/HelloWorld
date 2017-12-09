#include "../../../include/txt_file.hpp"

int main()
{
  vector<string> data = get_lines();
  int result = 0;
  for (auto e: data) {
    vector<int> numbers = get_signed_numbers(e);
    for (auto n: numbers) {
      result += n;
    }
  }
  cout << result << endl;
  return 0;
}
