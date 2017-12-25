#include "../../../include/txt_file.hpp"

int main()
{
  const int disk_size = 35651584;
  string input = "00101000101111010";
  while (input.size() < disk_size) {
    string copy = input;
    reverse(copy.begin(), copy.end());
    for (auto& e: copy) {
      if (e == '1') {
	e = '0';
      } else {
	e = '1';
      }
    }
    input += ("0" + copy);
  }
  input = input.substr(0, disk_size);
  cout << input.size() << ":" << input << endl;
  string checksum = input;
  while (checksum.size() % 2 == 0) {
    string temp;
    for (int i = 0; i < checksum.size(); i+= 2) {
      if (checksum[i] == checksum[i + 1]) {
	temp.append(1, '1');
      } else {
	temp.append(1, '0');
      }
    }
    checksum = temp;
  }
  cout << checksum << endl;
  return 0;
}
