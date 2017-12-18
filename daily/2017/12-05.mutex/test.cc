#include "../../../include/txt_file.hpp"

mutex g_mutex;
int   g_count = 0;

void work(int num)
{
  this_thread::sleep_for(chrono::milliseconds(get_random_number(100, 1000)));
  g_mutex.lock();
  cout << "Thread " << num << ": "<< g_count++ << " Hello, world!" << endl;
  g_mutex.unlock();
}

int main()
{
  vector<thread> threads;

  for (int i = 0; i < 10; i++) {
    threads.push_back(thread(work, i));
  }

  for (auto& e: threads) {
    e.join();
  }
}
