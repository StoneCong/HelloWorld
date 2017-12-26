#include "../../../include/txt_file.hpp"

int main()
{
  vector<string> data = get_lines();
  vector<pair<long long, long long>> ranges;
  for (auto e: data) {
    vector<int> nums = get_numbers(e);
    ranges.push_back(make_pair((long long)(unsigned int)nums[0],
			       (long long)(unsigned int)nums[1]));
  }
  sort(ranges.begin(), ranges.end());
  vector<pair<long long, long long>> allowed_ranges;
  long long low = ranges[0].first;
  long long high = ranges[0].second;
  for (auto e: ranges) {
    if (e.first > high + 1) {
      allowed_ranges.push_back(make_pair(high + 1, e.first - 1));
      low = e.first;
      high = e.second;
      continue;
    }
    high = max(e.second, high);
  }
  allowed_ranges.push_back(make_pair(high + 1, (long long)(unsigned int)-1));

  int count = 0;
  for (auto e: allowed_ranges) {
    count += e.second - e.first + 1;
  }
  cout << count << endl;
  return 0;
}
