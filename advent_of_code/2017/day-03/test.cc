#include "../../../include/txt_file.hpp"

enum direction {
  left = 1,
  right,
  up,
  down
};

direction get_direction(pair<int, int> previous, pair<int, int> current)
{
  if (previous.second == current.second) {
    return previous.first < current.first ? direction::right : direction::left;
  }
  return previous.second < current.second ? direction::up : direction::down;
}

int get_sum(pair<int, int> cur, const unordered_map<pair<int, int>, int, PairHasher>& map)
{
  int sum = 0;
  if (map.find(make_pair(cur.first, cur.second + 1)) != map.end()) sum += map.at(make_pair(cur.first, cur.second + 1));
  if (map.find(make_pair(cur.first - 1, cur.second)) != map.end()) sum += map.at(make_pair(cur.first - 1, cur.second));
  if (map.find(make_pair(cur.first, cur.second - 1)) != map.end()) sum += map.at(make_pair(cur.first, cur.second - 1));
  if (map.find(make_pair(cur.first + 1, cur.second)) != map.end()) sum += map.at(make_pair(cur.first + 1, cur.second));

  if (map.find(make_pair(cur.first - 1, cur.second + 1)) != map.end()) sum += map.at(make_pair(cur.first - 1, cur.second + 1));
  if (map.find(make_pair(cur.first - 1, cur.second - 1)) != map.end()) sum += map.at(make_pair(cur.first - 1, cur.second - 1));
  if (map.find(make_pair(cur.first + 1, cur.second - 1)) != map.end()) sum += map.at(make_pair(cur.first + 1, cur.second - 1));
  if (map.find(make_pair(cur.first + 1, cur.second + 1)) != map.end()) sum += map.at(make_pair(cur.first + 1, cur.second + 1));

  if (sum > 368078) {
    cout << "sum found: " << sum << "\n";
  }

  return sum;
}

void get_next(const pair<int, int>& previous,
              const pair<int, int>& current,
              pair<int, int>& next,
              unordered_map<pair<int, int>, int, PairHasher>& map)
{
  // get direction
  direction d = get_direction(previous, current);
  switch (d) {
  case direction::left:
    // if there is number underneath current, go left
    if (map.find(make_pair(current.first, current.second - 1)) != map.end()) {
      next = make_pair(current.first - 1, current.second);
      map[next] = get_sum(next, map);
    } else {
      // go downward
      next = make_pair(current.first, current.second - 1);
      map[next] = get_sum(next, map);
    }
    return;
  case direction::down:
    // if there is number to our right, continue
    if (map.find(make_pair(current.first + 1, current.second)) != map.end()) {
      next = make_pair(current.first, current.second - 1);
      map[next] = get_sum(next, map);
    } else {
      // go right
      next = make_pair(current.first + 1, current.second);
      map[next] = get_sum(next, map);
    }
    return;
  case direction::right:
    // if there is number above us, continue
    if (map.find(make_pair(current.first, current.second + 1)) != map.end()) {
      next = make_pair(current.first + 1, current.second);
      map[next] = get_sum(next, map);
    } else {
      // go up
      next = make_pair(current.first, current.second + 1);
      map[next] = get_sum(next, map);
    }
    return;
  case direction::up:
    // if there is number to our left, continue
    if (map.find(make_pair(current.first - 1, current.second)) != map.end()) {
      next = make_pair(current.first, current.second + 1);
      map[next] = get_sum(next, map);
    } else {
      // go left
      next = make_pair(current.first - 1, current.second);
      map[next] = get_sum(next, map);
    }
    return;
  };
  assert(false);
}

void get_location(int number, pair<int, int>& location)
{
  unordered_map<pair<int, int>, int, PairHasher> map;
  map[make_pair(0, 0)] = 1;
  map[make_pair(1, 0)] = 1;
  map[make_pair(1, 1)] = 2;
  map[make_pair(0, 1)] = 4;
  if (number < 5) {
    // to simplify, not supporting this
    assert(false);
    return;
  }

  pair<int, int> previous = make_pair(1, 1);
  pair<int, int> current = make_pair(0, 1);
  pair<int, int> next;

  for (int i = 5; i <= number; i++) {
    get_next(previous, current, next, map);
    previous = current;
    current = next;
  }

  location = current;
}

int main()
{
  pair<int, int> location;
  get_location(5, location);
  assert(location.first == -1 && location.second == 1);
  get_location(25, location);
  assert(location.first == 2 && location.second == -2);
  get_location(368078, location);
  cout << location.first << ", " << location.second << "\n";
  return 0;
}
