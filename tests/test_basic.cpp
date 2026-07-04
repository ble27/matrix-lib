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

void test_multiplication_default_constructor() {
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

void test_multiplication_factor() {
    Matrix A(2, 2), B(2, 2);
    A(0,0)=1; A(0,1)=2; A(1,0)=3; A(1,1)=4;
    B(0,0)=5; B(0,1)=6; B(1,0)=7; B(1,1)=8;
    A = A * 2;
    B *= 2;
    assert(approx_eq(A(0,0), 2.0));
    assert(approx_eq(A(0,1), 4.0));
    assert(approx_eq(A(1,0), 6.0));
    assert(approx_eq(A(1,1), 8.0));
    assert(approx_eq(B(0,0), 10.0));
    assert(approx_eq(B(0,1), 12.0));
    assert(approx_eq(B(1,0), 14.0));
    assert(approx_eq(B(1,1), 16.0));
    std::cout << "PASS test_multiply_factor\n";
}

void test_division_factor() {
    Matrix A(2, 2), B(2, 2);
    A(0,0)=2; A(0,1)=9; A(1,0)=7.5; A(1,1)=4;
    B(0,0)=10; B(0,1)=6; B(1,0)=9; B(1,1)=8;
    A /= 2;
    B = B / 2;

    assert(approx_eq(A(0,0), 1.0));
    assert(approx_eq(A(0,1), 4.5));
    assert(approx_eq(A(1,0), 3.75));
    assert(approx_eq(A(1,1), 2.0));
    assert(approx_eq(B(0,0), 5.0));
    assert(approx_eq(B(0,1), 3.0));
    assert(approx_eq(B(1,0), 4.5));
    assert(approx_eq(B(1,1), 4.0));
    std::cout << "PASS test_division_factor\n";
}
void test_addition_elementwise() {
    Matrix a(2, 2);
    Matrix b(2, 2);
    a(0, 0) = 1.0; a(0, 1) = 2.0; a(1, 0) = 3.0; a(1, 1) = 4.0;
    b(0, 0) = 1.0; b(0, 1) = 2.0; b(1, 0) = 3.0; b(1, 1) = 4.0;
    Matrix c = a + b;
    assert(approx_eq(c(0,0), 2.0));
    assert(approx_eq(c(0,1), 4.0));
    assert(approx_eq(c(1,0), 6.0));
    assert(approx_eq(c(1,1), 8.0));
    std::cout << "PASS test_addition_elementwise\n";
}

void test_subtraction_elementwise() {
    Matrix a(2, 2);
    Matrix b(2, 2);
    a(0, 0) = 1.0; a(0, 1) = 7.0; a(1, 0) = 6.0; a(1, 1) = 9.0;
    b(0, 0) = 2.0; b(0, 1) = 5.0; b(1, 0) = 3.0; b(1, 1) = 4.0;
    Matrix c = a - b;
    assert(approx_eq(c(0,0), -1.0));
    assert(approx_eq(c(0,1), 2.0));
    assert(approx_eq(c(1,0), 3.0));
    assert(approx_eq(c(1,1), 5.0));
    std::cout << "PASS test_subtraction_elementwise\n";
}

void test_equality() {
    Matrix a(2, 2);
    Matrix b(2, 2);
    a(0, 0) = 1.0; a(0, 1) = 7.0; a(1, 0) = 6.0; a(1, 1) = 9.0;
    b(0, 0) = 1.0; b(0, 1) = 7.0; b(1, 0) = 6.0; b(1, 1) = 9.0;
    assert(a(0,0) == b(0,0));
    assert(a(0,1) == b(0,1));
    assert(a(1,0) == b(1,0));
    assert(a(1,1) == b(1,1));
    std::cout << "PASS test_equality\n";
}

void test_non_equality() {
    Matrix a(2, 2);
    Matrix b(2, 2);
    a(0, 0) = 2.0; a(0, 1) = 7.0; a(1, 0) = 5.0; a(1, 1) = 9.0;
    b(0, 0) = 1.0; b(0, 1) = 7.0; b(1, 0) = 6.0; b(1, 1) = 9.0;
    assert(a(0,0) != b(0,0));
    assert(a(0,1) == b(0,1));
    assert(a(1,0) != b(1,0));
    assert(a(1,1) == b(1,1));
    std::cout << "PASS test_non_equality\n";
}

void test_sum_all() {
    Matrix a(2, 3, {1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0});
    assert(approx_eq(a.sum(), 21.0));
    std::cout << "PASS test_sum_all\n";
}

void test_sum_axis0() {
    // sum across columns for each row
    // row 0: 1+2+3 = 6
    // row 1: 4+5+6 = 15
    Matrix a(2, 3, {1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0});
    Matrix res = a.sum(0);
    assert(approx_eq(res(0, 0), 6.0));
    assert(approx_eq(res(1, 0), 15.0));
    std::cout << "PASS test_sum_axis0\n";
}

void test_sum_axis1() {
    // sum down each column across rows
    // col 0: 1+4 = 5
    // col 1: 2+5 = 7
    // col 2: 3+6 = 9
    Matrix a(2, 3, {1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0});
    Matrix res = a.sum(1);
    assert(approx_eq(res(0, 0), 5.0));
    assert(approx_eq(res(0, 1), 7.0));
    assert(approx_eq(res(0, 2), 9.0));
    std::cout << "PASS test_sum_axis1\n";
}

void test_mean_all() {
    // mean of all elements: 21 / 6 = 3.5
    Matrix a(2, 3, {1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0});
    assert(approx_eq(a.mean(), 3.5));
    std::cout << "PASS test_mean_all\n";
}

void test_mean_axis0() {
    // mean across columns for each row
    // row 0: (1+2+3) / 3 = 2.0
    // row 1: (4+5+6) / 3 = 5.0
    Matrix a(2, 3, {1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0});
    Matrix res = a.mean(0);
    assert(approx_eq(res(0, 0), 2.0));
    assert(approx_eq(res(1, 0), 5.0));
    std::cout << "PASS test_mean_axis0\n";
}

void test_mean_axis1() {
    // mean down each column across rows
    // col 0: (1+4) / 2 = 2.5
    // col 1: (2+5) / 2 = 3.5
    // col 2: (3+6) / 2 = 4.5
    Matrix a(2, 3, {1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0});
    Matrix res = a.mean(1);
    assert(approx_eq(res(0, 0), 2.5));
    assert(approx_eq(res(0, 1), 3.5));
    assert(approx_eq(res(0, 2), 4.5));
    std::cout << "PASS test_mean_axis1\n";
}

void test_max_all() {
    Matrix a(2, 3, {1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0});
    assert(approx_eq(a.max(), 6.0));
    std::cout << "PASS test_max_all\n";
}

void test_max_axis0() {
    // max across columns for each row
    // row 0: max(1,2,3) = 3
    // row 1: max(4,5,6) = 6
    Matrix a(2, 3, {1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0});
    Matrix res = a.max(0);
    assert(approx_eq(res(0, 0), 3.0));
    assert(approx_eq(res(1, 0), 6.0));
    std::cout << "PASS test_max_axis0\n";
}

void test_max_axis1() {
    // max down each column across rows
    // col 0: max(1,4) = 4
    // col 1: max(2,5) = 5
    // col 2: max(3,6) = 6
    Matrix a(2, 3, {1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0});
    Matrix res = a.max(1);
    assert(approx_eq(res(0, 0), 4.0));
    assert(approx_eq(res(0, 1), 5.0));
    assert(approx_eq(res(0, 2), 6.0));
    std::cout << "PASS test_max_axis1\n";
}

void test_min_all() {
    Matrix a(2, 3, {1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0});
    assert(approx_eq(a.min(), 1.0));
    std::cout << "PASS test_min_all\n";
}

void test_min_axis0() {
    // min across columns for each row
    // row 0: min(1,2,3) = 1
    // row 1: min(4,5,6) = 4
    Matrix a(2, 3, {1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0});
    Matrix res = a.min(0);
    assert(approx_eq(res(0, 0), 1.0));
    assert(approx_eq(res(1, 0), 4.0));
    std::cout << "PASS test_min_axis0\n";
}

void test_min_axis1() {
    // min down each column across rows
    // col 0: min(1,4) = 1
    // col 1: min(2,5) = 2
    // col 2: min(3,6) = 3
    Matrix a(2, 3, {1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0});
    Matrix res = a.min(1);
    assert(approx_eq(res(0, 0), 1.0));
    assert(approx_eq(res(0, 1), 2.0));
    assert(approx_eq(res(0, 2), 3.0));
    std::cout << "PASS test_min_axis1\n";
}

int main() {
    test_construction();
    test_element_access();
    test_multiplication_default_constructor();
    test_multiplication_factor();
    test_division_factor();
    test_addition_elementwise();
    test_subtraction_elementwise();
    test_equality();
    test_non_equality();
    test_construction();
    test_element_access();
    test_sum_all();
    test_sum_axis0();
    test_sum_axis1();
    test_mean_all();
    test_mean_axis0();
    test_mean_axis1();
    test_max_all();
    test_max_axis0();
    test_max_axis1();
    test_min_all();
    test_min_axis0();
    test_min_axis1();
    std::cout << "\nAll tests passed.\n";
    return 0;
}