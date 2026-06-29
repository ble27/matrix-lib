CXX      = clang++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -I include

SRC      = src/matrix.cpp
TEST_SRC = tests/test_basic.cpp

test: $(SRC) $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(TEST_SRC) -o test_runner
	./test_runner

clean:
	rm -f test_runner