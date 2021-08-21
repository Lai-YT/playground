CXXFLAGS := -std=c++11 -pthread

bin/notify_one: 1_notify_one.cpp
	g++ $< -o $@ $(CXXFLAGS)

bin/notify_all: 2_notify_all.cpp
	g++ $< -o $@ $(CXXFLAGS)

bin/wait_predict: 3_wait_predict.cpp
	g++ $< -o $@ $(CXXFLAGS)

bin/example: 4_example.cpp
	g++ $< -o $@ $(CXXFLAGS)
