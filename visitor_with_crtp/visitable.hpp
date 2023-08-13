#ifndef VISITABLE_HPP
#define VISITABLE_HPP

#include "book.hpp"
#include "visitor.hpp"

template<typename Base, class Derived>
class Visitable : public Base {
 public:
  void Accept(Visitor& visitor) override {
    visitor.Visit(static_cast<Derived&>(*this));
  }
};

#endif
