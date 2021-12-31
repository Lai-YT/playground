#include <iostream>
#include <thread>


void Foo(const int n) {
  std::cout << "foo " << n << '\n';
}


int main(int argc, char const *argv[]) {
  /*
   * Default is a thread object that does nothing,
   * though it's still better to initialize at the same time.
   */
  std::thread threads[3];
  /* initialization */
  for (int i = 0; i < 3; ++i) {
    threads[i] = std::thread(Foo, i);
  }
  /* make sure you join all of the threads */
  for (int i = 0; i < 3; ++i) {
    threads[i].join();
  }

  std::cout << "main exits." << '\n';

  return 0;
}
