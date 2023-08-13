#ifndef BOOK_HPP
#define BOOK_HPP

#include "visitor.hpp"

class Book {
 public:
  virtual void Accept(Visitor&) = 0;
  virtual ~Book() = default;
};

#endif
