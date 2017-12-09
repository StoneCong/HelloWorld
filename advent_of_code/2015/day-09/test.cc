#include "../../../include/txt_file.hpp"

void add_city(string city, vector<string>& cities)
{
  for (auto e: cities) {
    if (e == city) return;
  }
  cities.push_back(city);
}

int get_path_cost(vector<int>& permutation, const vector<string>& cities, const map<pair<string, string>, int>& dict)
{
  int cost = 0;
  for (int i = 0; i < permutation.size() - 1; i++) {
    pair<string, string> current_pair = make_pair(cities[permutation[i]], cities[permutation[i + 1]]);
    if (dict.find(current_pair) == dict.end()) {
      return INT_MAX;
    }
    cost += dict.find(current_pair)->second;
  }
  return cost;
}

int get_shortest_route(const vector<string>& cities, const map<pair<string, string>, int>& dict)
{
  // get all the permutations of cities and check which one is shortest
  vector<vector<int>> permutations = get_permutations(cities.size());
  int shortest_route = INT_MAX;
  for (auto p: permutations) {
    int cost = get_path_cost(p, cities, dict);
    shortest_route = min(shortest_route, cost);
  }
  return shortest_route;
}

int get_longest_route(const vector<string>& cities, const map<pair<string, string>, int>& dict)
{
  // get all the permutations of cities and check which one is shortest
  vector<vector<int>> permutations = get_permutations(cities.size());
  int longest_route = 0;
  for (auto p: permutations) {
    int cost = get_path_cost(p, cities, dict);
    if (cost == INT_MAX) continue;
    longest_route = max(longest_route, cost);
  }
  return longest_route;
}

int main(int arg, const char* argv[])
{
  vector<string> data = get_lines(arg == 1 ? "data.txt" : "real.txt");
  map<pair<string, string>, int> dict;
  vector<string> cities;
  for (auto e: data) {
    vector<int> numbers = get_numbers(e);
    vector<string> words = get_words(e);
    dict[make_pair(words[0], words[2])] = numbers[0];
    dict[make_pair(words[2], words[0])] = numbers[0];
    add_city(words[0], cities);
    add_city(words[2], cities);
  }
  cout << get_shortest_route(cities, dict) << endl;
  cout << get_longest_route(cities, dict) << endl;
  return 0;
}
