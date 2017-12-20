#include "../../../include/txt_file.hpp"

int main()
{
  int x = 10, y = 20;
  cout << "x = " << x << " y = " << y << endl;
  swap(x, y);
  cout << "x = " << x << " y = " << y << endl;

  vector<int> foo(4, x), bar(6, y);
  print_vector(foo);
  print_vector(bar);
  swap(foo, bar);
  print_vector(foo);
  print_vector(bar);
}
