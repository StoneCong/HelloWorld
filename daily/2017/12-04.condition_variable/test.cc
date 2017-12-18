#include "../../../include/txt_file.hpp"

/*
  http://thispointer.com/c11-multithreading-part-7-condition-variables-explained/
 */

class Application
{
public:
  Application() : m_loaded(false) {}
  void LoadData()
  {
    cout << "LoadData: preparing data\n";
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << "LoadData: acquiring mutex in order to release data\n";
    lock_guard<mutex> guard(m_mutex);
    m_loaded = true;
    cout << "LoadData: notifying thread condition variable\n";
    m_cond.notify_one();
    cout << "LoadData: terminating\n";
  }
  bool isDataLoaded()
  {
    return m_loaded;
  }
  void MainTask()
  {
    cout << "MainTask: do some handshaking\n";
    // Acquire the lock
    cout << "MainTask: acquiring mutex\n";
    unique_lock<mutex> mlock(m_mutex);
    // Start waiting for the Condition Variable to get signaled
    // Wait() will internally release the lock and make the thread to block
    // As soon as condition variable get signaled, resume the thread and
    // again acquire the lock. Then check if condition is met or not
    // If condition is met then continue else again go in wait.
    cout << "MainTask: condition variable waiting\n";
    m_cond.wait(mlock, bind(&Application::isDataLoaded, this));
    cout << "MainTask: processing loaded data and then terminating\n";
  }
private:
  condition_variable m_cond;
  mutex m_mutex;
  bool m_loaded;
};

int main()
{
  Application app;
  thread thread1(&Application::MainTask, &app);
  thread thread2(&Application::LoadData, &app);
  thread2.join();
  thread1.join();
  return 0;
}

/*
  MainTask: do some handshaking
  LoadData: preparing data
  MainTask: acquiring mutex
  MainTask: condition variable waiting
  LoadData: acquiring mutex in order to release data
  LoadData: notifying thread condition variable
  LoadData: terminating
  MainTask: processing loaded data and then terminating
*/
