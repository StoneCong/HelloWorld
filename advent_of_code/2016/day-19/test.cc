#include "../../../include/txt_file.hpp"

void part_1()
{
  const int count = 3005290;
  vector<int> elves(count, 1);
  int cur = 0;
  int i = 0;
  for (;;) {
    if (elves[cur] == 0) {
      cur = (cur + 1) % count;
      continue;
    }
    // scan to the right
    for (i = cur + 1; ; i++) {
      if (elves[i % count]) break;
    }
    i = i % count;
    if (i == cur) {
      cout << "index = " << cur + 1 << endl;
      break;
    }
    cout << "passing " << elves[i] << " gifts from " << i << " to " << cur << endl;
    elves[cur] += elves[i];
    elves[i] = 0;
    cur = (cur + 1) % count;
  }
}

void part_2()
{
  // use list with a dict index into it to speed up this part.
  int count = 3005290;
  vector<pair<int, int>> elves;
  for (int i = 0; i < count; i++) {
    elves.push_back(make_pair(i + 1, 1));
  }
  int cur = 0;
  while (elves.size() > 1) {
    if (elves.size() % 1000 == 0) cout << elves.size() << endl;
    int target = (cur + (elves.size() / 2)) % elves.size();
    elves[cur].second += elves[target].second;
    elves.erase(elves.begin() + target);
    cur = (cur + 1) % elves.size();
  }
  cout << elves[0].first << ": gift count = " << elves[0].second << endl;
  // 154525: gift count = 3005290: too low
}

int main()
{
  part_2();
}
