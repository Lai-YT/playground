#include <cstddef>   // size_t
#include <iomanip>   // setw
#include <iostream>  // cout

#include "vec.hpp"

int main() {
  constexpr std::size_t N = 3;
  float sa[N] = {1, 2, 3};
  auto a = Vec{sa, N};
  float sb[N] = {2, 3, 4};
  auto b = Vec{sb, N};
  float sc[N] = {3, 4, 5};
  auto c = Vec{sc, N};

  // With expression template, no temporaries are created during each addition.
  auto x = a + b + c;
  std::cout << "| x| = |a| + |b| + |c|" << '\n';
  std::cout << "----------------------" << '\n';
  for (std::size_t i = 0; i < N; ++i) {
    std::cout << '|' << std::setw(2) << x[i] << '|' << " = " << '|' << a[i]
              << '|' << " + " << '|' << b[i] << '|' << " + " << '|' << c[i]
              << '|' << '\n';
  }
}
