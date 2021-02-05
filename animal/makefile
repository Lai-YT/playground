.PHONY: dirs clean stat

all: dirs ut_all

CFLAGS = -std=c++11 -fno-elide-constructors -Wfatal-errors
CC = g++
SRC_HEADERS = src/animal.h src/dog.h src/bird.h
TEST_HEADERS = test/ut_animal.h

main: $(SRC_HEADERS)
	$(CC) $(CFLAGS) src/main.cpp -o bin/ut_all

ut_all: test/ut_main.cpp $(TEST_HEADERS) $(SRC_HEADERS)
	$(CC) $(CFLAGS) test/ut_main.cpp -o bin/ut_all -lgtest -lpthread

dirs:
	mkdir -p bin

clean:
	rm -rf bin

stat:
	wc src/* test/*
