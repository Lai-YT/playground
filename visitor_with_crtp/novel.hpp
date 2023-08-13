#ifndef NOVEL_HPP
#define NOVEL_HPP

#include "book.hpp"
#include "visitable.hpp"

class Novel : public Visitable<Book, Novel> {};

#endif
