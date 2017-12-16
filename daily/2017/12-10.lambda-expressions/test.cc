#include "../../../include/txt_file.hpp"

int main()
{
  vector<int> v {-5, -19, 3, 10, 15, 20, 100};
  auto firstPos = find_if(begin(v), end(v), [](int n) {return n > 0;});
  if (firstPos != end(v)) {
    cout << "First positive value in v is: " << *firstPos << endl;
  }
}
