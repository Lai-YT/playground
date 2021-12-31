#include <iostream>
#include <mutex>
#include <thread>


/*
 * This is a modified version of 2_mutex.cpp.
 * Using lock_guards to take advantage of RAII.
 * mutex is automatically unlocked during the destruction of lock_guard,
 * so avoids deadlock.
 */

/* shared data */
int g_count = 0;
/* put mutex with the resouce it protects, so global in the case */
std::mutex g_mutex;

void Print(const int n, const char c) {
  /* critical section (exclusive access to std::cout signaled by locking mutex) */
  std::lock_guard<std::mutex> lock(g_mutex);

  for (size_t i = 0; i < n; i++) {
    std::cout << c;
    ++g_count;
  }
  std::cout << '\n';

  std::cout << "g_count = " << g_count << '\n';
}  /* unlock automatically */


int main(int argc, char const *argv[]) {
  std::thread t1(Print, 10, 'A');
  std::thread t2(Print, 5, 'B');
  t1.join();
  t2.join();

  return 0;
}
