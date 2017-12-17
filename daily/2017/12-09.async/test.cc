#include "../../../include/txt_file.hpp"

/*
  More info: https://solarianprogrammer.com/2012/10/17/cpp-11-async-tutorial/
*/


void called_from_async() {
  cout << "Message from async call!\n";
}

int main() {
  //called_from_async launched in a separate thread if possible
  future<void> result(async(called_from_async));
  cout << "Message from main!\n";
  //ensure that called_from_async is launched synchronously
  //if it wasn't already launched
  result.get();
}
