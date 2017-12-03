#include "../../../include/txt_file.hpp"

int main()
{
  vector<string> data = get_lines();
  cout << data.size() << "\n";
  for (auto e: data) {
    cout << e << "\n";
  }
  return 0;
}
