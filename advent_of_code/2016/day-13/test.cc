#include "../../../include/txt_file.hpp"

bool is_wall(pair<int, int> pos)
{
  int x = pos.first;
  int y = pos.second;
  if (x < 0 || y < 0) return true;
  int result = x * x + 3 * x + 2 * x * y + y + y * y;
  bitset<32> bit_set(result + 1364);
  return bit_set.count() & 1;
}

int main()
{
  int                   count = 0;
  queue<pair<int, int>> frontier;
  set<pair<int, int>>   processed;
  set<pair<int, int>>   reachable;

  frontier.push(make_pair(1, 1));

  while (frontier.size()) {
    queue<pair<int, int>> next_frontier;
    while (frontier.size()) {
      pair<int, int> cur = frontier.front();
      if (cur == make_pair(31, 39)) {
        cout << count << endl;
        // part 1 is done here: return 0;
      }
      frontier.pop();
      if (processed.find(cur) != processed.end()) continue;
      processed.insert(cur);
      if (is_wall(cur)) continue;
      reachable.insert(cur);
      next_frontier.push(make_pair(cur.first - 1, cur.second));
      next_frontier.push(make_pair(cur.first + 1, cur.second));
      next_frontier.push(make_pair(cur.first, cur.second - 1));
      next_frontier.push(make_pair(cur.first, cur.second + 1));
    }
    frontier = next_frontier;
    count++;
    if (count == 51) break;
  }
  cout << reachable.size() << endl;
  return 0;
}
