CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wpedantic -Wold-style-cast -g

catch: catch_amalgamated.cpp
	$(CXX) -std=c++17 -c catch_amalgamated.cpp

test: catch_amalgamated.o test_list.cpp list.cpp list.h
	$(CXX) $(CXXFLAGS) catch_amalgamated.o test_list.cpp list.cpp
	./a.out --success

valgrind: test
	valgrind --tool=memcheck --leak-check=yes ./a.out

clean:
	rm -f a.out *.o *.gch *.out

.PHONY: test clean catch valgrind