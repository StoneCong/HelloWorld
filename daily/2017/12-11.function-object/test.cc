#include "../../../include/txt_file.hpp"

struct IsPos {
  bool operator()(int n) { return n > 0; }
};

inline void print_vector(vector<int>& v)
{
  cout << "v(" << v.size() << "):";
  for (auto e: v) {
    cout << " " << e;
  }
  cout << endl;
}

inline void print_vector(vector<string>& v)
{
  cout << "v(" << v.size() << "):";
  for (auto e: v) {
    cout << " \"" << e << "\"";
  }
  cout << endl;
}

int main()
{
  vector<string> strings {"hello", "world"};
  vector<int> numbers {-5, -19, 3, 10, 15, 20, 100};
  print_vector(strings);
  print_vector(numbers);
  auto firstPos = find_if(begin(numbers), end(numbers), IsPos());
  if (firstPos != end(numbers)) {
    cout << "First positive value in v is: " << *firstPos << endl;
  }
}
