#include "../../../include/txt_file.hpp"

vector<string> get_graph(string input)
{
  return split_line(input, "/");
}

void print_graph(vector<string> g)
{
  cout << endl;
  for (auto e: g) {
    cout << e << endl;
  }
  cout << endl;
}

vector<string> rotate_left(vector<string> g)
{
  vector<string> result;
  for (int i = g.size() - 1; i >= 0; i--) {
    string row;
    for (int j = 0; j < g.size(); j++) {
      row.append(1, g[j][i]);
    }
    result.push_back(row);
  }
  return result;
}

vector<string> rotate_left(vector<string> g, int count)
{
  for (int i = 0; i < count; i++) {
    g = rotate_left(g);
  }
  return g;
}

vector<string> flip(vector<string> g)
{
  vector<string> result;
  for (auto& e: g) {
    reverse(e.begin(), e.end());
    result.push_back(e);
  }
  return result;
}

vector<string> grow(vector<string> graph, map<vector<string>, vector<string>>& dict)
{
  if (dict.find(graph) == dict.end()) {
    cout << "Cannot process this graph" << endl;
    print_graph(graph);
  }
  return dict[graph];
}

vector<string> scan_left_to_right(vector<string>& graph,
				  int row,
				  int step,
				  map<vector<string>, vector<string>>& dict)
{
  vector<string> lines(step + 1, string());
  for (int col = 0; col < graph.size(); col += step) {
    vector<string> temp;
    for (int i = 0; i < step; i++) {
      temp.push_back(graph[row + i].substr(col, step));
    }
    temp = grow(temp, dict);
    for (int i = 0; i < step + 1; i++) {
      lines[i] += temp[i];
    }
  }
  return lines;
}

vector<string> process_graph(vector<string>& graph, map<vector<string>, vector<string>>& dict)
{
  vector<string> result;

  if (graph.size() == 3) {
    return grow(graph, dict);
  }

  if (graph.size() % 2 == 0) {
    for (int row = 0; row < graph.size(); row += 2) {
      for (auto e: scan_left_to_right(graph, row, 2, dict)) {
        result.push_back(e);
      }
    }
    return result;
  }

  // split into 3x3 and them sum them up
  for (int row = 0; row < graph.size(); row += 3) {
    for (auto e: scan_left_to_right(graph, row, 3, dict)) {
      result.push_back(e);
    }
  }

  return result;
}

int main()
{
  vector<string> data = get_lines();
  vector<string> graph;
  graph.push_back(".#.");
  graph.push_back("..#");
  graph.push_back("###");

  print_graph(graph);
  
  map<vector<string>, vector<string>> dict;
  for (auto e: data) {

    vector<string> terms = split_line(e, " ");
    vector<string> from = get_graph(terms[0]);
    vector<string> to = get_graph(terms[2]);
    vector<string> flipped = flip(from);
    
    dict[from] = to;
    dict[flipped] = to;
    for (int i = 1; i < 4; i++) {
      dict[rotate_left(from, i)] = to;
      dict[rotate_left(flipped, i)] = to;
    }
  }
  
  for (int i = 0; i < 18; i++) {
    graph = process_graph(graph, dict);
    print_graph(graph);
  }

  int count = 0;
  for (auto e: graph) {
    for (auto c: e) {
      if (c == '#') count++;
    }
  }

  cout << count << endl;
  
  return 0;
}
