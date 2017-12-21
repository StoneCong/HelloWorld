#include "../../../include/txt_file.hpp"

int main()
{
  vector<string> data = get_lines();
  for (auto e: data) {
    cout << e << endl;
  }
  return 0;
}
