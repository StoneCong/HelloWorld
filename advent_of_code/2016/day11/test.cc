#include "../../../include/txt_file.hpp"

void print_graph(vector<vector<int>>& data)
{
  cout << "Graph:\n";
  for (int row = data.size() - 1; row >= 0; row--) {
    for (auto i: data[row]) {
      cout << " " << setfill('0') << setw(2) << i;
    }
    cout << "\n";
  }
}

void get_valid_next_states(const vector<vector<int>>& current,
                           vector<vector<vector<int>>>& states)
{
  // find the elevator row count
  // choose to carry one item or two item
  // choose which item(s) to carry
  // check if the new state is valid
  // if valid, insert into states
}

void process_state(vector<vector<int>> current,
                   map<vector<vector<int>>, bool>& states,
                   queue<vector<vector<int>>>& next_frontier)
{
  vector<vector<vector<int>>> valid_next_states;
  get_valid_next_states(current, valid_next_states);
  for (auto e: valid_next_states) {
    if (states[e]) continue;
    next_frontier.push(e);
  }
}

int main()
{
  vector<vector<int>> data;
  // -1:                elevator;
  // 0, 10, 20, 30, 40: generators;
  // 1, 11, 21, 31, 41: microchips
  data.push_back(vector<int>{-1, 0, 1, 10, 20});
  data.push_back(vector<int>{11, 21});
  data.push_back(vector<int>{30, 31, 40, 41});
  data.push_back(vector<int>{});

  map<vector<vector<int>>, bool> states;
  queue<vector<vector<int>>> frontier;
  frontier.push(data);
  int steps = 0;
  while (frontier.size()) {
    steps++;
    cout << "Step " << steps << "\n";
    queue<vector<vector<int>>> next_frontier;
    while (frontier.size()) {
      vector<vector<int>> current = frontier.front();
      frontier.pop();
      print_graph(current);
      states[current] = true;
      process_state(current, states, next_frontier);
    }
    steps++;
    frontier = next_frontier;
  }

  return 0;
}
