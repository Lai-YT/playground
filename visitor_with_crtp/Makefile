.PHONY: clean

CC = g++
CXXFLAGS = -std=c++14
HEADERS = visitor.hpp visitable.hpp book.hpp comic.hpp novel.hpp
OBJS = visitor.o
DEPS := $(OBJS:%.o=%.d)

main: main.cpp $(HEADERS) $(OBJS)
	$(CC) -o $@ $< $(OBJS) $(CXXFLAGS)

%.o: %.cpp
	$(CC) -c -o $@ $< $(CXXFLAGS) -MMD

clean:
	rm -f main $(OBJS) $(DEPS)

-include: $(DEPS)
