#include "../../../include/txt_file.hpp"

bool aligned_well(vector<pair<int, int>> positions)
{
  for (int i = 0; i < positions.size(); i++) {
    for (auto& e: positions) {
      e.second = (e.second + 1) % e.first;
    }
    if (positions[i].second != 0) return false;
  }
  return true;
}

int main()
{
  /*
  Disc #1 has 13 positions; at time=0, it is at position 10.
  Disc #2 has 17 positions; at time=0, it is at position 15.
  Disc #3 has 19 positions; at time=0, it is at position 17.
  Disc #4 has 7 positions; at time=0, it is at position 1.
  Disc #5 has 5 positions; at time=0, it is at position 0.
  Disc #6 has 3 positions; at time=0, it is at position 1.
   */

  vector<pair<int, int>> positions;
  positions.push_back(make_pair(13, 10));
  positions.push_back(make_pair(17, 15));
  positions.push_back(make_pair(19, 17));
  positions.push_back(make_pair( 7,  1));
  positions.push_back(make_pair( 5,  0));
  positions.push_back(make_pair( 3,  1));
  positions.push_back(make_pair(11,  0));  // part II input

  for (int wait_num = 0; ; wait_num++) {
    if (wait_num % 1000 == 0) cout << wait_num << endl;
    if (aligned_well(positions)) {
      cout << "result: " << wait_num << endl;
      break;
    }
    for (auto& e: positions) {
      e.second = (e.second + 1) % e.first;
    }
  }

  return 0;
}
