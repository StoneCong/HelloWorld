#include "../../../include/txt_file.hpp"

string find_parent(string cur, map<string, pair<int, vector<string>>>& dict)
{
  string result;
  for (auto e: dict) {
    for (auto t: e.second.second) {
      if (cur == t) return e.first;
    }
  }
  return result;
}

int get_weight(string cur, map<string, pair<int, vector<string>>>& dict)
{
  if (dict[cur].second.size() == 0) {
    return dict[cur].first;
  }
  int sum = dict[cur].first;
  for (auto e: dict[cur].second) {
    sum += get_weight(e, dict);
  }
  return sum;
}

bool get_compare_results(vector<int> numbers, int& right, int& wrong)
{
  int min_value = numbers[0];
  int max_value = numbers[0];

  for (auto e: numbers) {
    min_value = min(min_value, e);
    max_value = max(max_value, e);
  }
  if (min_value == max_value) return true;

  int min_count = 0;
  int min_index = 0;
  int max_count = 0;
  int max_index = 0;

  for (int i = 0; i < numbers.size(); i++) {
    if (numbers[i] == min_value) {
      min_count++;
      min_index = i;
      continue;
    }
    if (numbers[i] == max_value) {
      max_count++;
      max_index = i;
      continue;
    }
  }

  if (numbers.size() >= 3) {
    if (min_count == 1) {
      wrong = min_index;
      right = max_index;
      return false;
    }
    if (max_count == 1) {
      wrong = max_index;
      right = min_index;
      return false;
    }
  }
  // do we need to handle 2 element cases? Luckily for these inputs we don't
  assert(false);
  return false;
}

int main()
{
  vector<string> data = get_lines();
  string current;
  string root;

  cout << "=======================================" << endl;

  map<string, pair<int, vector<string>>> dict;

  for (auto e: data) {
    vector<string> terms = get_terms(e);
    vector<string> children;
    vector<int> numbers = get_numbers(e);
    for (int i = 2; i < terms.size(); i++) {
      children.push_back(terms[i]);
    }
    dict[terms[0]] = make_pair(numbers[0], children);
    current = terms[0];
  }

  // Find root node
  for (;;) {
    string parent = find_parent(current, dict);
    if (parent.size() == 0) {
      root = current;
      cout << "root node: " << root << endl;
      break;
    }
    current = parent;
  }

  // find the inbalanced node
  current = root;
  for (;;) {
    vector<string> children = dict[current].second;
    if (children.size() == 0) break;
    vector<int> weights;
    for (auto e: children) {
      weights.push_back(get_weight(e, dict));
    }
    int right, wrong;
    if (get_compare_results(weights, right, wrong)) {
      cout << "wrong node: " << current << " node weight:" << dict[current].first << " total weight:" << get_weight(current, dict) << endl;
      string parent = find_parent(current, dict);
      for (auto e: dict[parent].second) {
        cout << "sibling node: " << e << " node weight:" << dict[e].first << " total weight:" << get_weight(e, dict) << endl;
      }
      break;
    }
    current = children[wrong];
  }
  return 0;
}
