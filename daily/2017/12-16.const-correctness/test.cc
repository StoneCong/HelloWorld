#include "../../../include/txt_file.hpp"

class test_class
{
public:

  test_class(int input) : m_data(input) {}

  /*
  int increment() const
  {
    return ++m_data;
  }

  test.cc:11:12: error: cannot assign to non-static data member within const member function 'increment'
      return ++m_data;
             ^ ~~~~~~
  test.cc:9:7: note: member function 'test_class::increment' is declared const here
    int increment() const
    ~~~~^~~~~~~~~~~~~~~~~
  1 error generated.
  */

  int test_func()
  {
    /*
      https://en.wikipedia.org/wiki/Const_(computer_programming)
     */
    int * ptr0 = nullptr;             // use nullptr instead of NULL
    int **ptr1;                       // a pointer to a pointer to ints
    int const **ptr2;                 // a pointer to a pointer to constant int value
                                      // (not a pointer to a constant pointer to ints)
    int *const *ptr3;                 // a pointer to a const pointer to int values
                                      // (not a constant pointer to a pointer to ints)
    int **const ptr4 = nullptr;       // a constant pointer to pointers to ints
                                      // (ptr, the identifier, being const makes no sense)
    int const **const ptr5 = nullptr; // a constant pointer to pointers to constant int values
    return 0;
  }

private:

  int m_data;
};

int main()
{
  return 0;
}
