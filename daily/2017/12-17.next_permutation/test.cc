#include "../../../include/txt_file.hpp"

int main()
{
  string s = "ababc";
  sort(s.begin(), s.end());
  int count = 0;
  do {
    cout << s << '\n';
    count++;
  } while(next_permutation(s.begin(), s.end()));
  cout << count << endl;
}
