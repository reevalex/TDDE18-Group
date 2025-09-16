CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wpedantic -Wold-style-cast

catch: catch_amalgamated.cpp
	$(CXX) -std=c++17 -c catch_amalgamated.cpp

test: catch_amalgamated.o test_time.cc time.cc time.h
	$(CXX) $(CXXFLAGS) catch_amalgamated.o test_time.cc time.cc -o test
	./test

clean:
	rm -f test_time *.o *.gch

.PHONY: test clean catch