#include "../../../include/txt_file.hpp"

void complex_numbers_test()
{
  // using namespace complex_literals;
  cout << fixed << setprecision(1);

  complex<double> z1 = 1i * 1i;                      // imaginary unit squared
  cout << "i * i = " << z1 << '\n';

  double PI = acos(-1);
  // complex<double> z3 = exp(1i * PI);              // Euler's formula
  // cout << "exp(i * pi) = " << z3 << '\n';

  complex<double> z4 = 1. + 2i, z5 = 1. - 2i;        // conjugates
  cout << "(1+2i)*(1-2i) = " << z4*z5 << '\n';
}

struct cell {
};

class FluxCapacitor {
public:
  static const size_t num_cells = 50;                // still OK
  FluxCapacitor(complex<double> c) : capacity(c) {}  // capacity c
  FluxCapacitor() {}                                 // capacity 100
private:
  int id;
  // static int nextId = 0;                          // Should be OK but not yet on c++ 14 compiler
  complex<double> capacity = 100;                    // New OK!
  cell FluxCells[num_cells];                         // Still OK
};

int main()
{
  complex_numbers_test();
  cout << "test the new c++ 11/14 in-class initializers." << endl;
  return 0;
}
