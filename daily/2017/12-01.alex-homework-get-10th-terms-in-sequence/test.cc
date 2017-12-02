#include <assert.h>
#include <stdio.h>

#include <vector>
#include <string>

using namespace std;

pair<int, int> get_next_term(pair<int, int> first, pair<int, int> second)
{
  int top = first.first + second.first + 1;
  int bottom = first.second + second.second + 1;

  bool restart = false;
  for (;;) {
    restart = false;
    for (int i = 2; i <= min(top, bottom); i++) {
      if ((top % i == 0) && (bottom % i == 0)) {
        top /= i;
        bottom /= i;
        restart = true;
        break;
      }
    }
    if (!restart) {
      break;
    }
  }

  return make_pair(top, bottom);
}

int main()
{
  pair<int, int> first(make_pair(3, 2));
  pair<int, int> second(make_pair(10, 7));
  for (int i = 0; i < 40; i++) {
    pair<int, int> next = get_next_term(first, second);
    printf("%d / %d\n", next.first, next.second);
    first = second;
    second = next;
  }
  return 0;
}
