#include "../../../include/txt_file.hpp"

int get_steps(map<string, int>& dict)
{
  int n_count = dict["n"] - dict["s"];
  int nw_count = dict["nw"] - dict["se"];
  int sw_count = dict["sw"] - dict["ne"];

  int min_common = min(min(abs(n_count),  abs(sw_count)),
                       min(abs(sw_count), abs(nw_count)));

  if (min_common == 0) return abs(n_count) + abs(sw_count) + abs(nw_count);

  if ((n_count > 0 && sw_count > 0 && nw_count > 0) ||
      (n_count < 0 && sw_count < 0 && nw_count < 0)) {
    return (abs(n_count) + abs(sw_count) + abs(nw_count)) - min_common;
  }

  if ((n_count > 0 && sw_count > 0 && nw_count < 0) ||
      (n_count < 0 && sw_count < 0 && nw_count > 0)) {
    return (abs(n_count) + abs(sw_count) + abs(nw_count)) - 3 * min_common;
  }

  return (abs(n_count) + abs(sw_count) + abs(nw_count)) - min_common;
}

int main()
{
  vector<string> data = get_lines();
  map<string, int> dict;
  vector<string> terms = get_terms(data[0]);
  int max_steps = 0;
  for (auto e: terms) {
    dict[e]++;
    max_steps = max(max_steps, get_steps(dict));
  }
  cout << "steps: " << get_steps(dict) << endl;
  cout << "max:   " << max_steps << endl;
  return 0;
}
