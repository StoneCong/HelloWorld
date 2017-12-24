#include "../../../include/txt_file.hpp"

int get_free_connector(vector<pair<int, int>> current_path)
{
  int current_connector = 0;
  for (auto e: current_path) {
    current_connector = (e.first == current_connector) ? e.second : e.first;
  }
  return current_connector;  
}

void print_path(vector<pair<int, int>> path) {
  for (auto e: path) {
    cout << " (" << e.first << ", " << e.second << ")";
  }
  cout << endl;
}

vector<pair<int, int>> get_neighbors(vector<pair<int, int>> cur_path,
				     vector<pair<int, int>>& links)
{
  vector<pair<int, int>> result;
  int free_connector = get_free_connector(cur_path);
  for (auto e: links) {
    if (find(cur_path.begin(), cur_path.end(), e) != cur_path.end()) continue;
    if (e.first == free_connector || e.second == free_connector) {
      result.push_back(e);
    }
  }
  return result;
}

int get_path_value(vector<pair<int, int>> path)
{
  int result = 0;
  for (auto e: path) {
    result += e.first;
    result += e.second;
  }
  return result;
}

void DFT_Graph(vector<pair<int, int>> cur_path,
	       vector<pair<int, int>>& links,
	       map<int, int>& hop_max_dict)
{
  for (auto e: get_neighbors(cur_path, links)) {
    cur_path.push_back(e);
    hop_max_dict[cur_path.size()] = max(hop_max_dict[cur_path.size()], get_path_value(cur_path));
    DFT_Graph(cur_path, links, hop_max_dict);
    cur_path.pop_back();
  }
}

int main()
{
  vector<string> data = get_lines();
  vector<pair<int, int>> links;
  for (auto& e: data) {
    vector<int> numbers = get_numbers(e);
    links.push_back(make_pair(min(numbers[0], numbers[1]), max(numbers[0], numbers[1])));
  }
  vector<pair<int, int>> current_path;
  map<int, int> hop_max_dict;
  hop_max_dict[0] = 0;
  current_path.push_back(make_pair(0, 0));
  DFT_Graph(current_path, links, hop_max_dict);
  for (auto e: hop_max_dict) {
    cout << e.first << " = " << e.second << endl;
  }
}
