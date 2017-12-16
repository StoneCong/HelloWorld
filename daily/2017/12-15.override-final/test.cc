#include "../../../include/txt_file.hpp"

class Base {
public:
  virtual void f(int);       // Nothing more needed
  virtual int g() const;     // cannot change member variables
  virtual void h(int) final; // Only virtual functions can be marked as final
};

class Derived : public Base {
public:
  void f(int) override;      // Base::f must be virtual

  /*
  int g() override;          // error as shown below

  test.cc:13:11: error: non-virtual member function marked 'override' hides virtual member function
    int g() override;          // error
          ^
  test.cc:6:15: note: hidden overloaded virtual function 'Base::g' declared here: different qualifiers (const vs none)
    virtual int g() const;     // cannot change member variables
              ^
  1 error generated.
  */

  /*
    void h(int);

    cong@MacBook:~/src/advent_of_code/daily/2017/12-15.override-final$ g++ test.cc
    test.cc:26:8: error: declaration of 'h' overrides a 'final' function
    void h(int);
    ^
    test.cc:7:16: note: overridden virtual function is here
    virtual void h(int) final; // Only virtual functions can be marked as final
    ^
    test.cc:26:8: warning: 'h' overrides a member function but is not marked 'override' [-Winconsistent-missing-override]
    void h(int);
    ^
    test.cc:7:16: note: overridden virtual function is here
    virtual void h(int) final; // Only virtual functions can be marked as final
    ^
    1 warning and 1 error generated.
   */

};

class Further_Derived final : public Base {
};

/*
class New_Derived : public Further_Derived {
};

test.cc:50:28: error: base 'Further_Derived' is marked 'final'
class New_Derived : public Further_Derived {
                           ^
test.cc:47:7: note: 'Further_Derived' declared here
class Further_Derived final : public Base {
      ^               ~~~~~
1 error generated.
*/

int main()
{
  cout << "test override and final in c++ 11" << endl;
  return 0;
}
