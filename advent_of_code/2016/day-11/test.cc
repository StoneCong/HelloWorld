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

bool is_valid_row(vector<int>& row)
{
  if (row.size() == 0) return true;
  sort(row.begin(), row.end());
  bool generator_found = false;
  for (auto e: row) {
    if (e == -1) continue;
    if (e % 2 == 0) {
      generator_found = true;
    }
  }
  if (!generator_found) return true;
  // every chip must has its generator
  for (auto e: row) {
    if (e == -1) continue;
    if (e % 2) {
      // find e - 1 (the generator) in the list
      bool found = false;
      for (auto element: row) {
        if (element == e - 1) {
          found = true;
          break;
        }
      }
      if (!found) return false;
    }
  }
  return true;
}

void get_valid_next_states(const vector<vector<int>>& current,
                           vector<vector<vector<int>>>& states)
{
  // choose to carry one item or two item to go either up or down
  // check if new state is valid: if valid, insert into states
  states.clear();
  // find the elevator row count
  int elevator_row = -1;
  int index = 0;
  for (auto e: current) {
    for (auto n: e) {
      if (n == -1) {
        assert(elevator_row == -1);
        elevator_row = index;
      }
    }
    index++;
  }
  assert(elevator_row != -1);

  // remove the elevator out from list of objects to move
  vector<int> row;
  for (auto e: current[elevator_row]) {
    if (e == -1) continue;
    row.push_back(e);
  }

  // carry item(s) up
  if (elevator_row < 3) {
    vector<vector<int>> new_state = current;
    // 1 item
    for (auto e: row) {
      vector<int> row_above = current[elevator_row + 1];
      row_above.push_back(e);
      row_above.push_back(-1);
      if (!is_valid_row(row_above)) continue;
      vector<int> new_row;
      for (auto element: row) {
        if (element == e) continue;
        new_row.push_back(element);
      }
      if (!is_valid_row(new_row)) continue;
      new_state[elevator_row] = new_row;
      new_state[elevator_row + 1] = row_above;
      states.push_back(new_state);
    }
    // carry 2 items up
    new_state = current;
    for (int i = 0; i < row.size() - 1; i++) {
      for (int j = i + 1; j < row.size(); j++) {
        vector<int> row_above = current[elevator_row + 1];
        row_above.push_back(row[i]);
        row_above.push_back(row[j]);
        row_above.push_back(-1);
        if (!is_valid_row(row_above)) continue;
        vector<int> new_row;
        for (auto element: row) {
          if (element == row[i] || element == row[j]) continue;
          new_row.push_back(element);
        }
        if (!is_valid_row(new_row)) continue;
        new_state[elevator_row] = new_row;
        new_state[elevator_row + 1] = row_above;
        states.push_back(new_state);
      }
    }
  }
  // carry item(s) down
  if (elevator_row > 0) {
    vector<vector<int>> new_state = current;
    // 1 item
    for (auto e: row) {
      vector<int> row_below = current[elevator_row - 1];
      row_below.push_back(e);
      row_below.push_back(-1);
      if (!is_valid_row(row_below)) continue;
      vector<int> new_row;
      for (auto element: row) {
        if (element == e) continue;
        new_row.push_back(element);
      }
      if (!is_valid_row(new_row)) continue;
      new_state[elevator_row] = new_row;
      new_state[elevator_row - 1] = row_below;
      states.push_back(new_state);
    }
    // carry 2 items down
    new_state = current;
    for (int i = 0; i < row.size() - 1; i++) {
      for (int j = i + 1; j < row.size(); j++) {
        vector<int> row_below = current[elevator_row - 1];
        row_below.push_back(row[i]);
        row_below.push_back(row[j]);
        row_below.push_back(-1);
        if (!is_valid_row(row_below)) continue;
        vector<int> new_row;
        for (auto element: row) {
          if (element == row[i] || element == row[j]) continue;
          new_row.push_back(element);
        }
        if (!is_valid_row(new_row)) continue;
        new_state[elevator_row] = new_row;
        new_state[elevator_row - 1] = row_below;
        states.push_back(new_state);
      }
    }
  }
}

void process_state(vector<vector<int>> current,
                   map<vector<vector<int>>, bool>& states,
                   queue<vector<vector<int>>>& next_frontier)
{
  vector<vector<vector<int>>> valid_next_states;
  get_valid_next_states(current, valid_next_states);
  for (auto e: valid_next_states) {
    if (states.find(e) != states.end()) continue;
    next_frontier.push(e);
    states[e] = true;
  }
}

int main()
{
  vector<vector<int>> data;
  // -1:                        elevator;
  // 0, 10, 20, 30, 40, 50, 60: generators;
  // 1, 11, 21, 31, 41, 51, 61: microchips
  data.push_back(vector<int>{-1, 0, 1, 10, 20, 50, 51, 60, 61});
  data.push_back(vector<int>{11, 21});
  data.push_back(vector<int>{30, 31, 40, 41});
  data.push_back(vector<int>{});

  // Use BFT to search for the shortest path to move everything up
  map<vector<vector<int>>, bool> states;
  queue<vector<vector<int>>> frontier;
  frontier.push(data);
  int steps = 0;
  while (frontier.size()) {
    cout << "Step " << steps << "\n";
    queue<vector<vector<int>>> next_frontier;
    while (frontier.size()) {
      vector<vector<int>> current = frontier.front();
      frontier.pop();
      // print_graph(current);
      states[current] = true;
      if (current[3].size() == 15) {
        cout << "Found: " << steps << "\n";
        return 0;
      }
      process_state(current, states, next_frontier);
    }
    frontier = next_frontier;
    steps++;
  }
  return 0;
}
