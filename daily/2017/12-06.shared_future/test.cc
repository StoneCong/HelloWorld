#include "../../../include/txt_file.hpp"

int factorial(shared_future<int> f)
{
  int res = 1;
  int n = f.get();
  for (int i = n; i > 1; i--) {
    res *= i;
  }
  return res;
}

int main()
{
  promise<int> p;
  future<int> f = p.get_future();
  shared_future<int> sf = f.share();
  vector<future<int>> futures;
  for (int i = 0; i < 10; i++) {
    futures.push_back(async(launch::async, factorial, sf));
  }
  // now broadcast the promise to every async threads
  p.set_value(4);
  for (auto& e: futures) {
    cout << e.get() << endl;
  }
}
