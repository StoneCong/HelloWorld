#include "../../../include/txt_file.hpp"

void simple()
{
  vector<int> v {-5, -19, 3, 10, 15, 20, 100};
  auto firstPos = find_if(begin(v), end(v), [](int n) {return n > 0;});
  if (firstPos != end(v)) {
    cout << "First positive value in v is: " << *firstPos << endl;
  }
}

void with_locals()
{
  vector<double> v {1.2, 4.7, 5, 9, 9.4};
  double target = 4.9;
  double epsilon = .3;

  auto end_matches = partition(begin(v), end(v), [target, epsilon](double val){return fabs(target-val) < epsilon;});
  cout << "Values within epsilon: " << for_each(begin(v), end_matches, [](double d){cout << d << ' ';});
  cout << endl;
}

void func_within_func()
{
  double target = 4.9;
  double epsilon = .3;
  auto withinEpsilon = [=](double val) {return fabs(target - val) < epsilon; };
  cout << (withinEpsilon(5.1) ? "Yes!" : "No!") << endl;
}

int main()
{
  simple();
  with_locals();
  func_within_func();
}
