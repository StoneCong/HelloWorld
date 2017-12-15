#include "../../../include/txt_file.hpp"

int get_next(int a, int factor)
{
  long long result = a;
  result *= factor;
  result %= 2147483647;
  return (int)result;
}

void part_1()
{
  int a = 618;
  int b = 814;

  int count = 0;
  for (int i = 0; i < 40 * 1000 * 1000; i++) {
    a = get_next(a, 16807);
    b = get_next(b, 48271);
    if ((a % 65536) == (b % 65536)) count++;
  }

  cout << count << endl;
}

void part_2()
{
  int a = 618;
  int b = 814;

  int count = 0;
  queue<int> r_a;
  queue<int> r_b;
  int pair_count = 0;
  while (pair_count < 5 * 1000 * 1000) {
    a = get_next(a, 16807);
    b = get_next(b, 48271);
    if (a % 4 == 0) r_a.push(a);
    if (b % 8 == 0) r_b.push(b);
    if (r_a.size() == 0) continue;
    if (r_b.size() == 0) continue;
    pair_count++;
    if ((r_a.front() % 65536) == (r_b.front() % 65536)) count++;
    r_a.pop();
    r_b.pop();
  }

  cout << count << endl;
}

int main()
{
  part_2();
  return 0;
}
