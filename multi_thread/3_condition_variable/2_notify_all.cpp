#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>


void PrintId(const int id, bool& ready,
             std::mutex& mutex, std::condition_variable& cond_var) {
  std::unique_lock<std::mutex> lock(mutex);

  cond_var.wait(lock, [&ready]() -> bool {
    return ready;
  });
  /*
  * The above statement is equivalent to:
  *   while (!ready) { cond_var.wait(lock); }
  * The second optional parameter of wait is a predicate function,
  * keeps waiting while the function returns false.
  */

  std::cout << "thread " << id << '\n';
}


void Go(bool& ready, std::mutex& mutex, std::condition_variable& cond_var) {
  std::unique_lock<std::mutex> lock(mutex);
  ready = true;
  cond_var.notify_all();
}


int main(int argc, char const *argv[]) {
  std::mutex mutex;
  std::condition_variable cond_var;
  bool ready = false;

  std::thread threads[5];
  for (int i = 0; i < 5; ++i) {
    threads[i] = std::thread(PrintId, i, std::ref(ready),
                             std::ref(mutex), std::ref(cond_var));
  }

  std::cout << "5 threads ready to race..." << '\n';
  Go(ready, mutex, cond_var);
  for (auto& thread : threads) {
    thread.join();
  }

  return 0;
}
