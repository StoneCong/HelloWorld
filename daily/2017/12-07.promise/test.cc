#include "../../../include/txt_file.hpp"

int factorial(future<int>& f)
{
  int res = 1;
  int num = f.get();
  for (int i = 2; i <= num; i++) {
    res *= i;
  }
  cout << num << "! = " << res << endl;
  return res;
}

int main()
{
  int x;
  promise<int> p;
  future<int> f1 = p.get_future();
  future<int> f2 = async(launch::async, factorial, ref(f1));
  // do something else
  this_thread::sleep_for(chrono::milliseconds(1000));
  p.set_value(4);
  x = f2.get();
  cout << "Get from child: " << x << endl;
}
