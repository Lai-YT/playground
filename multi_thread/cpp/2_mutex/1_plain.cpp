#include <iostream>
#include <thread>


/*
 * This is a no mutex version.
 * One can see that the output is out of order.
 */

/* shared data */
int g_count = 0;

void Print(const int n, const char c) {
  for (size_t i = 0; i < n; i++) {
    std::cout << c;
    ++g_count;
  }
  std::cout << '\n';

  std::cout << "g_count = " << g_count << '\n';
}


int main(int argc, char const *argv[]) {
  std::thread t1(Print, 10, 'A');
  std::thread t2(Print, 5, 'B');
  t1.join();
  t2.join();

  return 0;
}
