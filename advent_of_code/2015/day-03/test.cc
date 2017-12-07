#include "../../../include/txt_file.hpp"

void update_location(pair<int, int>& cur, char e, map<pair<int, int>, int>& locations)
{
  switch (e) {
  case '<':
    cur.first--;
    break;
  case '>':
    cur.first++;
    break;
  case '^':
    cur.second++;
    break;
  case 'v':
    cur.second--;
    break;
    assert(false);
  }
  if (locations.find(cur) == locations.end()) {
    locations[cur] = 1;
  } else {
    locations[cur]++;
  }
}

void part_1()
{
  vector<string> data = get_lines();
  map<pair<int, int>, int> locations;
  pair<int, int> cur = make_pair(0, 0);
  for (auto e: data[0]) {
    update_location(cur, e, locations);
  }
  cout << locations.size() << endl;
}

void part_2()
{
  vector<string> data = get_lines();
  map<pair<int, int>, int> locations;
  pair<int, int> curs[2];
  for (int i = 0; i < 2; i++) {
    curs[i] = make_pair(0, 0);
  }
  locations[curs[0]] = 2;
  for (int i = 0; i < data[0].size(); i += 2) {
    for (int j = 0; j < 2; j++) {
      char e = data[0][i + j];
      update_location(curs[j], e, locations);
    }
  }
  cout << locations.size() << endl;
}

int main()
{
  part_1();
  part_2();
  return 0;
}
