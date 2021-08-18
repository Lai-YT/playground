CXXFLAGS := -std=c++11 -pthread

bin/plain: 1_plain.cpp
	g++ $< -o $@ $(CXXFLAGS)

bin/mutex: 2_mutex.cpp
	g++ $< -o $@ $(CXXFLAGS)

bin/guard: 3_guard.cpp
	g++ $< -o $@ $(CXXFLAGS)
