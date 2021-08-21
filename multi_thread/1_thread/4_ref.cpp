#include <functional>
#include <iostream>
#include <thread>


void Foo1(int& n) {
  std::cout << "in foo 1, n = " << n << '\n';
  n += 10;
}


void Foo2(int n) {
  std::cout << "in foo 2, n = " << n << '\n';
  n += 10;
}


/*
 * One can pass reference to a funtion that takes value,
 * but can't pass value to a function that takes reference.
 */
int main(int argc, char const *argv[]) {
  int n1 = 5;
  std::thread t1(Foo1, std::ref(n1));
  t1.join();
  std::cout << "in main, n1 = " << n1 << '\n';

  int n2 = 5;
  std::thread t2(Foo2, n2);
  t2.join();
  std::cout << "in main, n2 = " << n2 << '\n';

  return 0;
}
