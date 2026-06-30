/**
 * tests/test_basic.cpp
 * author: Bao Le
 */

#include "../include/matrix.hpp"
#include <cassert>
#include <cmath>

bool approx_eq(double a, double b, double tol = 1e-9) {
    return std::abs(a - b) < tol;
}

void test_construction() {
    Matrix test(2, 3);
    assert(test.rows() == 2);
    assert(test.cols() == 3);
    for (size_t r = 0; r < test.rows(); r++) {
        for (size_t c = 0; c < test.cols(); c++) {
            assert(approx_eq(test(r, c), 0.0));
        }
    }
    std::cout << "PASS test_construction\n";
}

void test_element_access() {
    Matrix m(2, 2);
    m(0, 0) = 1.0;
    m(0, 1) = 2.0;
    m(1, 0) = 3.0;
    m(1, 1) = 4.0;

    assert(approx_eq(m(0, 0), 1.0));
    assert(approx_eq(m(1, 1), 4.0));
    std::cout << "PASS test_element_access\n";
}

void test_multiply_default_constructor() {
    // A = [[1, 2], [3, 4]]
    // B = [[5, 6], [7, 8]]
    // A*B = [[1*5+2*7, 1*6+2*8], [3*5+4*7, 3*6+4*8]]
    //     = [[19, 22], [43, 50]]
    Matrix A(2, 2), B(2, 2);
    A(0,0)=1; A(0,1)=2; A(1,0)=3; A(1,1)=4;
    B(0,0)=5; B(0,1)=6; B(1,0)=7; B(1,1)=8;

    Matrix C = A * B;
    assert(approx_eq(C(0,0), 19.0));
    assert(approx_eq(C(0,1), 22.0));
    assert(approx_eq(C(1,0), 43.0));
    assert(approx_eq(C(1,1), 50.0));
    std::cout << "PASS test_multiply_default_constructor\n";
}

// void test_multiply() {
//     // A = [[1, 2], [3, 4]]
//     // B = [[5, 6], [7, 8]]
//     // A*B = [[1*5+2*7, 1*6+2*8], [3*5+4*7, 3*6+4*8]]
//     //     = [[19, 22], [43, 50]]
//     Matrix A(2, 2, std::vector<double>{1,2,3,4}), B(2, 2, std::vector<double>{5,6,7,8});

//     Matrix C = A * B;
//     assert(approx_eq(C(0,0), 19.0));
//     assert(approx_eq(C(0,1), 22.0));
//     assert(approx_eq(C(1,0), 43.0));
//     assert(approx_eq(C(1,1), 50.0));
//     std::cout << "PASS test_multiply\n";
// }

int main() {
    test_construction();
    test_element_access();
    test_multiply_default_constructor();
    // test_multiply();
    std::cout << "\nAll tests passed.\n";
    return 0;
}