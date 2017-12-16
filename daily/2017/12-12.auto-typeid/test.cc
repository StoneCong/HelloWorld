#include "../../../include/txt_file.hpp"

int main()
{
  auto a(10);
  cout << "a has type: " << typeid(a).name() << endl;

  auto b {10};
  cout << "b has type: " << typeid(b).name() << endl;

  /*
    In C++, and in C99 and C11, it is a special rule of the language that
    if the control flow reaches the end of the main function, then the
    function impliclty returns 0.
   */
}
