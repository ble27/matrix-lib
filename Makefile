CXX      = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -I include

SRC      = src/matrix.cpp
TEST_SRC = tests/test_basic.cpp

test: $(SRC) $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(TEST_SRC) -o test_runner
	./test_runner

# -f flag = force, no error if file doesn't exist
clean:
	rm -f test_runner
	rm -f tests/test