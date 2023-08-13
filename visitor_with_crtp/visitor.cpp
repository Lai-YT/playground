#include "visitor.hpp"

#include <iostream>

#include "comic.hpp"
#include "novel.hpp"

void Visitor::Visit(Comic& comic) {
  std::cout << "This is a comic.\n";
}

void Visitor::Visit(Novel& novel) {
  std::cout << "This is a novel.\n";
}
