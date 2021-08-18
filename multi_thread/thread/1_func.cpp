/* g++ -std=c++14 1_func.cpp -o bin/func -pthread */

#include <chrono>
#include <iostream>
#include <thread>


void Foo() {
  std::cout << "foo" << '\n';
}


void Bar(const int n) {
  std::cout << "bar " << n << '\n';
}


int main(int argc, char const *argv[]) {
  std::thread t1(Foo);  /* new thread and execute foo */
  std::thread t2(Bar, 0);  /* new thread and execute bar */
  /* synchronize threads */
  std::cout << "main, foo and bar now execute concurrently..." << '\n';

  std::cout << "sleep 1s" << '\n';
  /* requires c++14, std::chrono::seconds(1) in c++11 */
  using namespace std::chrono_literals;
  std::this_thread::sleep_for(1s);

  std::cout << "join t1" << '\n';
  t1.join();  /* main waits until t1 finished */
  std::cout << "join t2" << '\n';
  t2.join();  /* main waits until t2 finished */

  /*
   * One can use t.detach() to tell main not to wait for t.
   */

  std::cout << "foo and bar completed." << '\n';

  return 0;
}
