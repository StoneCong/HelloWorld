#include "../../../include/txt_file.hpp"

int fib(int n)
{
  int previous, current, next;
  if (n == 0) return 0;
  if (n == 1) return 1;
  previous = 0;
  current = 1;
  for (int i = 2; i <= n; i++) {
    next = previous + current;
    previous = current;
    current = next;
  }
  printf("fib(%d) = %d\n", n, current);
  return current;
}

int main()
{
  vector<thread> threads;
  for (int i = 2; i < 40; i++) {
    threads.push_back(thread(fib, i));
  }
  for (auto& t: threads) {
    t.join();
  }
  return 0;
}
