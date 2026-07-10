#include <iostream>
#include "include/matrix.hpp"
// C++23
#include <print>

int main() {
    Matrix a(2, 3, {2, 3, 4, 5, 6, 7});
    Matrix b(3, 1, {1, 2, 3});
    Matrix c = a * b;
    std::cout << c;
    std::cout << c.transpose();
    std::println("{}", c.shape());
    return 0;
}