#include <iostream>
#include <mutex>
#include <thread>


/*
 * This is a mutex version of 1_plain.cpp.
 * The output is always in order.
 */

/* shared data */
int g_count = 0;
/* put mutex with the resouce it protects, so global in the case */
std::mutex g_mutex;

void Print(const int n, const char c) {
  /* critical section (exclusive access to std::cout signaled by locking mutex) */
  g_mutex.lock();

  for (size_t i = 0; i < n; i++) {
    std::cout << c;
    ++g_count;
  }
  std::cout << '\n';

  std::cout << "g_count = " << g_count << '\n';
  /* remember to unlock before leaving the critical section */
  g_mutex.unlock();
}


int main(int argc, char const *argv[]) {
  std::thread t1(Print, 10, 'A');
  std::thread t2(Print, 5, 'B');
  t1.join();
  t2.join();

  return 0;
}
