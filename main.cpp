#include <iostream>
#include "include/matrix.hpp"
// C++23
#include <print>
#include <iostream>
#include <cassert>
#include <cmath>
#include "include/matrix.hpp"

int main() {
    Matrix a(4, 4, {1,0,2,-1,3,0,0,5,2,1,4,-3,1,0,5,0});
    std::cout << a.determinant();
    return 0;
}