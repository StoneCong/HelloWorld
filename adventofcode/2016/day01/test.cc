#include <stdio.h>
#include <assert.h>
#include <vector>
#include <string>

using namespace std;

enum direction {
  north = 1,
  west = 2,
  south = 4,
  east = 8
};

string get_direction_string(direction input)
{
  switch (input) {
  case north:
    return "north";
  case west:
    return "west";
  case south:
    return "south";
  case east:
    return "east";
  }
  assert(false);
}

class Engine
{
public:

  Engine(string input): _data(input) {}

  int get_steps(int& cur)
  {
    assert(cur < _data.size());
    int result = 0;
    for (; cur < _data.size(); cur++) {
      char digit = _data[cur];
      if (digit < '0' || digit > '9') {
        return result;
      }
      result *= 10;
      result += digit - '0';
    }
    return result;
  }

  void adjust_direction(direction& cur_direction, bool turn_left)
  {
    if (turn_left) {
      switch (cur_direction) {
      case north:
        cur_direction = west;
        break;
      case south:
        cur_direction = east;
        break;
      case west:
        cur_direction = south;
        break;
      case east:
        cur_direction = north;
        break;
      }
      return;
    }
    switch (cur_direction) {
    case north:
      cur_direction = east;
      break;
    case south:
      cur_direction = west;
      break;
    case west:
      cur_direction = north;
      break;
    case east:
      cur_direction = south;
      break;
    }
  }

  pair<int, int> adjust_steps(direction cur_direction, int steps)
  {
    switch (cur_direction) {
    case north:
      return make_pair(0, steps);
    case south:
      return make_pair(0, -1 * steps);
    case west:
      return make_pair(-1 * steps, 0);
    case east:
      return make_pair(steps, 0);
    }
    assert(false);
  }

  // int:  number of steps to go. If 0, terminate
  // int:  number of steps to go. If 0, terminate
  pair<int, int> get_instruction(int& cur_offset, direction& cur_direction)
  {
    if (cur_offset >= _data.size()) {
      return make_pair(0, 0);
    }

    assert(_data[cur_offset] == 'L' || _data[cur_offset] == 'R');
    bool turn_left = (_data[cur_offset] == 'L');

    cur_offset++;
    assert(cur_offset < _data.size());

    int steps = get_steps(cur_offset);

    cur_offset += 2;

    adjust_direction(cur_direction, turn_left);
    // printf("I am here: %s, %d\n", get_direction_string(cur_direction).c_str(), steps);

    return adjust_steps(cur_direction, steps);
  }

  // x and y coordinations after solving the puzzle
  pair<int, int> solve_puzzle()
  {
    direction cur_direction(north);
    int       cur_offset = 0;
    pair<int, int> cur_position = make_pair(0, 0);
    for (;;) {
      pair<int, int> instruction = get_instruction(cur_offset, cur_direction);
      if (instruction.first == 0 && instruction.second == 0) break;
      cur_position.first +=  instruction.first;
      cur_position.second += instruction.second;
      // printf("<%d, %d>\n", cur_position.first, cur_position.second);
    }

    return cur_position;
  }

public:

  string _data;
};

int main()
{
  // raw data
  string data = "R4, R1, L2, R1, L1, L1, R1, L5, R1, R5, L2, R3, L3, L4, R4, R4, R3, L5, L1, R5, R3, L4, R1, R5, L1, R3, L2, R3, R1, L4, L1, R1, L1, L5, R1, L2, R2, L3, L5, R1, R5, L1, R188, L3, R2, R52, R5, L3, R79, L1, R5, R186, R2, R1, L3, L5, L2, R2, R4, R5, R5, L5, L4, R5, R3, L4, R4, L4, L4, R5, L4, L3, L1, L4, R1, R2, L5, R3, L4, R3, L3, L5, R1, R1, L3, R2, R1, R2, R2, L4, R5, R1, R3, R2, L2, L2, L1, R2, L1, L3, R5, R1, R4, R5, R2, R2, R4, R4, R1, L3, R4, L2, R2, R1, R3, L5, R5, R2, R5, L1, R2, R4, L1, R5, L3, L3, R1, L4, R2, L2, R1, L1, R4, R3, L2, L3, R3, L2, R1, L4, R5, L1, R5, L2, L1, L5, L2, L5, L2, L4, L2, R3";

  Engine engine(data);
  pair<int, int> result = engine.solve_puzzle();

  printf("Data: %s\n", data.c_str());
  printf("Result = <%d, %d>\n", result.first, result.second);
}
