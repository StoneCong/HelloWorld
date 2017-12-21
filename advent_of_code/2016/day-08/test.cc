#include "../../../include/txt_file.hpp"

enum instruction {
  unknown = 0,
  rect = 1,
  rotate_column_x = 2,
  rotate_row_y = 3
};

/*
  rect 14x1
  rotate column x=39 by 3
  rotate row y=5 by 5
*/
instruction get_instruction(string line, pair<int, int>& param)
{
  vector<int> numbers = get_numbers(line);
  assert(numbers.size() == 2);
  param = make_pair(numbers[0], numbers[1]);
  if (line.find("rect") != string::npos) {
    return rect;
  } else if (line.find("rotate column x") != string::npos) {
    return rotate_column_x;
  } else if (line.find("rotate row y") != string::npos) {
    return rotate_row_y;
  }
  assert(false);
  return unknown;
}

void print_board(vector<vector<int>>& board)
{
  cout << "Board:\n";
  for (auto e: board) {
    for (auto p: e) {
      cout << " " << (p == 1 ? "*" : " ");
    }
    cout << "\n";
  }
}

void set_point(int row, int column, vector<vector<int>>& board)
{
  board[row][column] = 1;
}

void set_rect(pair<int, int> params, vector<vector<int>>& board)
{
  for (int r = 0; r < params.second; r++) {
    for (int c = 0; c < params.first; c++) {
      set_point(r, c, board);
    }
  }
}

void rotate_col_by_1(int col, vector<vector<int>>& board)
{
  int temp = board.back()[col];
  for (int i = board.size() - 1; i > 0; i--) {
    board[i][col] = board[i - 1][col];
  }
  board[0][col] = temp;
}

void set_rotate_col(pair<int, int> params, vector<vector<int>>& board)
{
  int col = params.first;
  int count = params.second;
  for (int i = 0; i < count; i++) {
    rotate_col_by_1(col, board);
  }
}

void rotate_row_by_1(int row, vector<vector<int>>& board)
{
  int temp = board[row].back();
  for (int i = board[row].size() - 1; i > 0; i--) {
    board[row][i] = board[row][i - 1];
  }
  board[row][0] = temp;
}

void set_rotate_row(pair<int, int> params, vector<vector<int>>& board)
{
  int row = params.first;
  int count = params.second;
  for (int i = 0; i < count; i++) {
    rotate_row_by_1(row, board);
  }
}

int get_pixel_count(vector<vector<int>>& board)
{
  int count = 0;
  for (auto l: board) {
    for (auto c: l) {
      if (c == 1) count++;
    }
  }
  return count;
}

int main()
{
  vector<string> data = get_lines();
  vector<int> line(50, 0);
  vector<vector<int>> board(6, line);
  print_board(board);
  for (auto e: data) {
    pair<int, int> params;
    instruction i = get_instruction(e, params);
    switch (i) {
    case rect:
      set_rect(params, board);
      break;
    case rotate_column_x:
      set_rotate_col(params, board);
      break;
    case rotate_row_y:
      set_rotate_row(params, board);
      break;
    case unknown:
      assert(false);
      break;
    };
  }
  print_board(board);
  cout << get_pixel_count(board) << "\n";
  return 0;
}
