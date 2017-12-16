#include "../../../include/txt_file.hpp"

vector<int> test()
{
  vector<int> v = {10, 20, 30};
  v.insert(end(v), {40, 50, 60});
  return v;
}

int main()
{
  for (auto e: test())
    cout << " " << e;

  cout << endl;
  return 0;
}
