#include "../../../include/txt_file.hpp"

int main()
{
  map<string, pair<tuple<int, int, string>, tuple<int, int, string>>> instructions;
  instructions["A"] = make_pair(make_tuple(1,  1, "B"), make_tuple(0, -1, "B"));
  instructions["B"] = make_pair(make_tuple(1, -1, "C"), make_tuple(0,  1, "E"));
  instructions["C"] = make_pair(make_tuple(1,  1, "E"), make_tuple(0, -1, "D"));
  instructions["D"] = make_pair(make_tuple(1, -1, "A"), make_tuple(1, -1, "A"));
  instructions["E"] = make_pair(make_tuple(0,  1, "A"), make_tuple(0,  1, "F"));
  instructions["F"] = make_pair(make_tuple(1,  1, "E"), make_tuple(1,  1, "A"));

  map<int, int> values;
  string current_state = "A";
  int current_pos = 0;
  for (int i = 0; i < 12861455; i++) {
	int value = values[current_pos];
	if (value == 0) {
	  values[current_pos] = get<0>(instructions[current_state].first);
	  current_pos += get<1>(instructions[current_state].first);
	  current_state = get<2>(instructions[current_state].first);
	} else {
	  values[current_pos] = get<0>(instructions[current_state].second);
	  current_pos += get<1>(instructions[current_state].second);
	  current_state = get<2>(instructions[current_state].second);
	}
  }
  int count = 0;
  for (auto e: values) {
	if (e.second == 1) {
	  count++;
	}
  }
  cout << count << endl;
}
