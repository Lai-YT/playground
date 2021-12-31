#include <iostream>
#include <thread>


class MyClass {
public:
  void Foo() const {
    std::cout << "foo" << '\n';
  }

  void Bar(const int n) const {
    std::cout << "bar " << n << '\n';
  }

  void Start() const {
    /* take reference of the member functions and pass this as the first argument */
    std::thread t1(&MyClass::Foo, this);
    std::thread t2(&MyClass::Bar, this, 10);

    t1.join();
    t2.join();
  }
};


int main(int argc, char const *argv[]) {
  MyClass cls;
  cls.Start();

  return 0;
}
