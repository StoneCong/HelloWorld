#include "../../../include/txt_file.hpp"

/*
  More info: https://solarianprogrammer.com/2012/10/17/cpp-11-async-tutorial/
*/

void print_seperator()
{
  cout << "==================================================" << endl;
}

void called_from_async() {
  cout << "Message from async call!\n";
}

void simple()
{
  print_seperator();
  // Called_from_async launched in a separate thread if possible
  future<void> result(async(called_from_async));
  cout << "Message from main!\n";
  // Ensure that called_from_async is launched synchronously
  // If it wasn't already launched
  result.get();
}

void lambda()
{
  print_seperator();
  // called_from_async launched in a separate thread if possible.
  // Note return type is int
  future<int> result(async([](int m, int n) {return m + n;} , 2, 4));
  cout << "Message from main!\n";
  //retrive and print the value stored in the future
  cout << result.get() << endl;
}

int twice(int m)
{
  return m * 2;
}

void multiple()
{
  print_seperator();
  vector<future<int>> futures;
  for (int i = 0; i < 10; i++) {
    futures.push_back(async(twice, i));
  }
  for (auto& e: futures) {
    cout << e.get() << endl;
  }
}

void multiple_lambda()
{
  print_seperator();
  vector<future<int>> futures;
  for (int i = 0; i < 10; i++) {
    futures.push_back(async([](int m){return m*2;}, i));
  }
  for (auto& e: futures) {
    cout << e.get() << endl;
  }
}

int main() {
  simple();
  lambda();
  multiple();
  multiple_lambda();
}
