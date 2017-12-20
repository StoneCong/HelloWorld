#include "../../../include/txt_file.hpp"

/*
  http://thbecker.net/articles/rvalue_references/section_01.html
 */

class X
{
public:
  X(int data=0) : m_data(data) {}
  /*  X& operator=(const X & rhs)
  {
    m_data = rhs.m_data;
    return *this;
  }
  */
  X& operator=(X && rhs)
  {
    m_data = rhs.m_data;
    return *this;
  }
public:
  int m_data;
};

int main()
{
  X x(10);
  X y;
  cout << y.m_data << endl;
  y = x;
  cout << y.m_data << endl;
}
