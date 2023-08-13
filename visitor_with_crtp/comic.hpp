#ifndef COMIC_HPP
#define COMIC_HPP

#include "book.hpp"
#include "visitable.hpp"

class Comic : public Visitable<Book, Comic> {};

#endif
