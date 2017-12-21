#include "../../../include/txt_file.hpp"

void execute_rules(map<int, tuple<int, int, int, int>>& rules,
                   map<int, vector<int>>& states,
                   map<int, vector<int>>& outputs)
{
  bool done = true;
  for (;;) {
    done = true;
    for (auto e: states) {
      int bot_id = e.first;
      if (e.second.size() != 2) continue;
      done = false;
      int lo = min(e.second[0], e.second[1]);
      int ma = max(e.second[0], e.second[1]);
      tuple<int, int, int, int> rule = rules[bot_id];
      if (get<0>(rule) != -1) {
        states[get<0>(rule)].push_back(lo);
      } else {
        assert(get<1>(rule) != -1);
        outputs[get<1>(rule)].push_back(lo);
      }
      if (get<2>(rule) != -1) {
        states[get<2>(rule)].push_back(ma);
      } else {
        assert(get<3>(rule) != -1);
        outputs[get<3>(rule)].push_back(ma);
      }
      states[bot_id].clear();
      if (17 == lo && ma == 61) {
        cout << "found result: " << bot_id << "\n";
      }
    }
    if (done) break;
  }
}

int main()
{
  vector<string> data = get_lines();
  int max_bot_id = 0;
  vector<pair<int, int>> assignments;
  map<int, tuple<int, int, int, int>> rules;
  map<int, vector<int>> states;
  vector<int> empty_vector;
  map<int, vector<int>> outputs;
  for (auto e: data) {
    vector<int> input = get_numbers(e);
    int input_size = input.size();
    if (input_size == 2) {
      assignments.push_back(make_pair(input[0], input[1]));
      continue;
    }
    assert(input_size == 3);
    vector<string> terms = get_terms(e);
    tuple<int, int, int, int> rule (make_tuple(-1, -1, -1, -1));
    if (terms[5] == "bot") {
      get<0>(rule) = input[1];
    } else {
      get<1>(rule) = input[1];
    }
    if (terms[10] == "bot") {
      get<2>(rule) = input[2];
    } else {
      get<3>(rule) = input[2];
    }
    rules[input[0]] = rule;
  }

  // execute the instructions for as long as possible. Once done, feed in a new assignments;
  for (auto e: assignments) {
    states[e.second].push_back(e.first);
    execute_rules(rules, states, outputs);
  }

  for (auto e: outputs) {
    cout << "output " << e.first << ":";
    for (auto n: e.second) {
      cout << " " << n;
    }
    cout << "\n";
  }
  return 0;
}
