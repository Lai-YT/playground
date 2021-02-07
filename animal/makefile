.PHONY: dirs clean stat

CFLAGS = -std=c++11 -fno-elide-constructors -Wfatal-errors
CC = g++
TEST = test/ut_main.cpp test/ut_animal.h
OBJ = obj/ut_main.o obj/animal.o obj/dog.o obj/bird.o
LIBS = -lgtest -lpthread

all: dirs ut_all

ut_all: $(OBJ) $(TEST)
	$(CC) $(CFLAGS) -o bin/ut_all $(OBJ) $(LIBS)

obj/ut_main.o:
	$(CC) $(CFLAGS) -c test/ut_main.cpp -o obj/ut_main.o

obj/%.o: src/%.cpp src/%.h
	$(CC) $(CFLAGS) -c $< -o $@

dirs:
	mkdir -p bin obj

clean:
	rm -rf bin obj

stat:
	wc src/* test/*
