#include <memory>

#include "book.hpp"
#include "comic.hpp"
#include "novel.hpp"
#include "visitor.hpp"

int main() {
  std::unique_ptr<Book> comic = std::make_unique<Comic>();
  std::unique_ptr<Book> novel = std::make_unique<Novel>();

  auto visitor = Visitor{};

  comic->Accept(visitor);
  novel->Accept(visitor);

  return 0;
}
