#ifndef MY_VECTOR_HPP_
#define MY_VECTOR_HPP_

#include <initializer_list>
#include <iostream>
#include <memory>

// inherit from std::vector
template<typename value_type, typename allocator_type = std::allocator<value_type>>
class MyVector : public std::vector<value_type, allocator_type> {
public:
  // alias
  using base_vector = std::vector<value_type, allocator_type>;

  // use the constructors of std::vector
  using base_vector::vector;

  // Intention:
  // To test whether the constructor or operator= is called,
  // I hide the original implementations in base_vector so can add a cout message.

  MyVector(std::initializer_list<value_type> il, const allocator_type& alloc = allocator_type())
    :base_vector(il, alloc) {
    // call base class constructor
    std::cout << "constructor" << '\n';
  }

  MyVector& operator= (std::initializer_list<value_type> il) {
    // call base class operator=
    base_vector::operator=(il);
    std::cout << "operator=" << '\n';
    return *this;
  }

};

#endif /* end of include guard: MY_VECTOR_HPP_ */
