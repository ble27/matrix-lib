/**
 * tests/test_basic.cpp
 * author: Bao Le
 */

#include "../include/matrix.hpp"
#include <iostream>
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

void test_scalar_addition() {
    Matrix a(2, 2);
    Matrix b(2, 2);
    a(0, 0) = 1.0; a(0, 1) = 7.0; a(1, 0) = 6.0; a(1, 1) = 9.0;
    b(0, 0) = 2.0; b(0, 1) = 5.0; b(1, 0) = 11.0; b(1, 1) = 4.0;
    a = a + 2;
    b += 3;
    assert(approx_eq(a(0,0), 3.0));
    assert(approx_eq(a(0,1), 9.0));
    assert(approx_eq(a(1,0), 8.0));
    assert(approx_eq(a(1,1), 11.0));
    assert(approx_eq(b(0,0), 5.0));
    assert(approx_eq(b(0,1), 8.0));
    assert(approx_eq(b(1,0), 14.0));
    assert(approx_eq(b(1,1), 7.0));
    std::cout << "PASS test_scalar_addition\n";
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

void test_scalar_subtraction() {
    Matrix a(2, 2);
    Matrix b(2, 2);
    a(0, 0) = 1.0; a(0, 1) = 7.0; a(1, 0) = 6.0; a(1, 1) = 9.0;
    b(0, 0) = 2.0; b(0, 1) = 5.0; b(1, 0) = 11.0; b(1, 1) = 4.0;
    a = a - 2;
    b -= 3;
    assert(approx_eq(a(0,0), -1.0));
    assert(approx_eq(a(0,1), 5.0));
    assert(approx_eq(a(1,0), 4.0));
    assert(approx_eq(a(1,1), 7.0));
    assert(approx_eq(b(0,0), -1.0));
    assert(approx_eq(b(0,1), 2.0));
    assert(approx_eq(b(1,0), 8.0));
    assert(approx_eq(b(1,1), 1.0));
    std::cout << "PASS test_scalar_subtraction\n";
}

void test_dot_product() {
    Matrix a(2, 2);
    Matrix b(2, 2);
    a(0, 0) = 1.0; a(0, 1) = 7.0; a(1, 0) = 6.0; a(1, 1) = 9.0;
    b(0, 0) = 2.0; b(0, 1) = 5.0; b(1, 0) = 11.0; b(1, 1) = 4.0;
    double dot_total = a.dot(b);
    assert(dot_total == 2 + 35 + 66 + 36);
    std::cout << "PASS test_dot_product\n";
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

void test_transpose() {
    // original (2x3):        transposed (3x2):
    //  1  2  3                1  4
    //  4  5  6                2  5
    //                         3  6
    Matrix a(2, 3, {1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0});
    Matrix t = a.transpose();

    // check dimensions flipped
    assert(t.rows() == 3);
    assert(t.cols() == 2);

    // check values
    assert(approx_eq(t(0, 0), 1.0));
    assert(approx_eq(t(0, 1), 4.0));
    std::cout << "PASS test_transpose\n";
}

void test_slice() {
    Matrix a(3, 4, {1.0,  2.0,  3.0,  4.0,
                    5.0,  6.0,  7.0,  8.0,
                    9.0, 10.0, 11.0, 12.0});

    // slice rows 1-2, cols 1-2 → should give [[6,7],[10,11]]
    Matrix s = a.slice(1, 2, 1, 2);
    assert(s.rows() == 2);
    assert(s.cols() == 2);
    assert(approx_eq(s(0, 0),  6.0));
    assert(approx_eq(s(0, 1),  7.0));
    assert(approx_eq(s(1, 0), 10.0));
    assert(approx_eq(s(1, 1), 11.0));
    std::cout << "PASS test_slice\n";
}

void test_zeros() {
    Matrix zr = Matrix::zeros(2,3);
    assert(zr.rows() == 2);
    assert(zr.cols() == 3);
    assert(approx_eq(zr(0, 0),  0.0));
    assert(approx_eq(zr(0, 1),  0.0));
    assert(approx_eq(zr(0, 2),  0.0));
    assert(approx_eq(zr(1, 0),  0.0));
    assert(approx_eq(zr(1, 1),  0.0));
    assert(approx_eq(zr(1, 2),  0.0));
    std::cout << "PASS test_zeroes\n";
}

void test_ones() {
    Matrix o = Matrix::ones(2,3);
    assert(o.rows() == 2);
    assert(o.cols() == 3);
    assert(approx_eq(o(0, 0),  1.0));
    assert(approx_eq(o(0, 1),  1.0));
    assert(approx_eq(o(0, 2),  1.0));
    assert(approx_eq(o(1, 0),  1.0));
    assert(approx_eq(o(1, 1),  1.0));
    assert(approx_eq(o(1, 2),  1.0));
    std::cout << "PASS test_ones\n";
}

void test_identity() {
    Matrix i = Matrix::identity(3);
    assert(approx_eq(i(0, 0),  1.0));
    assert(approx_eq(i(0, 1),  0.0));
    assert(approx_eq(i(0, 2),  0.0));
    assert(approx_eq(i(1, 0),  0.0));
    assert(approx_eq(i(1, 1),  1.0));
    assert(approx_eq(i(1, 2),  0.0));
    assert(approx_eq(i(2, 0),  0.0));
    assert(approx_eq(i(2, 1),  0.0));
    assert(approx_eq(i(2, 2),  1.0));
    std::cout << "PASS test_identity\n";
}

void test_fill() {
    Matrix i(2, 3);
    i.fill(1);
    assert(approx_eq(i(0, 0), 1.0));
    assert(approx_eq(i(0, 1), 1.0));
    assert(approx_eq(i(0, 2), 1.0));
    assert(approx_eq(i(1, 0), 1.0));
    assert(approx_eq(i(1, 1), 1.0));
    assert(approx_eq(i(1, 2), 1.0));
    std::cout << "PASS test_fill\n";
}

void test_clip() {
    Matrix a(2, 3, {1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0});
    Matrix b = a.clip(2, 4);
    assert(approx_eq(b(0, 0), 2.0));
    assert(approx_eq(b(0, 1), 2.0));
    assert(approx_eq(b(0, 2), 3.0));
    assert(approx_eq(b(1, 0), 4.0));
    assert(approx_eq(b(1, 1), 4.0));
    assert(approx_eq(b(1, 2), 4.0));
    std::cout << "PASS test_clip\n";
}

void test_reshape() {
    Matrix a(2, 3, {1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0});
    Matrix b = a.reshape(1, 6);
    assert(approx_eq(b(0, 0), 1.0));
    assert(approx_eq(b(0, 1), 2.0));
    assert(approx_eq(b(0, 2), 3.0));
    assert(approx_eq(b(0, 3), 4.0));
    assert(approx_eq(b(0, 4), 5.0));
    assert(approx_eq(b(0, 5), 6.0));
    std::cout << "PASS test_reshape\n";
}

void test_flatten() {
    Matrix a(2, 3, {1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0});
    Matrix b = a.flatten();
    assert(approx_eq(b(0, 0), 1.0));
    assert(approx_eq(b(0, 1), 2.0));
    assert(approx_eq(b(0, 2), 3.0));
    assert(approx_eq(b(0, 3), 4.0));
    assert(approx_eq(b(0, 4), 5.0));
    assert(approx_eq(b(0, 5), 6.0));
    std::cout << "PASS test_flatten\n";
}

void test_hstack() {
    // A (2x2):    B (2x3):    expected (2x5):
    // 1  2        5  6  7     1  2  5  6  7
    // 3  4        8  9  10    3  4  8  9  10
    Matrix A(2, 2, {1.0, 2.0,
                    3.0, 4.0});
    Matrix B(2, 3, {5.0,  6.0,  7.0,
                    8.0,  9.0, 10.0});

    Matrix res = Matrix::hstack(A, B);

    // check dimensions
    assert(res.rows() == 2);
    assert(res.cols() == 5);

    // check values — left side from A
    assert(approx_eq(res(0, 0), 1.0));
    assert(approx_eq(res(0, 1), 2.0));
    assert(approx_eq(res(1, 0), 3.0));
    assert(approx_eq(res(1, 1), 4.0));

    // check values — right side from B
    assert(approx_eq(res(0, 2),  5.0));
    assert(approx_eq(res(0, 3),  6.0));
    assert(approx_eq(res(0, 4),  7.0));
    assert(approx_eq(res(1, 2),  8.0));
    assert(approx_eq(res(1, 3),  9.0));
    assert(approx_eq(res(1, 4), 10.0));

    std::cout << "PASS test_hstack\n";
}

void test_hstack_throws_on_row_mismatch() {
    // different number of rows — should throw
    Matrix A(2, 2, {1.0, 2.0, 3.0, 4.0});
    Matrix B(3, 2, {1.0, 2.0, 3.0, 4.0, 5.0, 6.0});

    bool threw = false;
    try {
        Matrix res = Matrix::hstack(A, B);
    } catch (const std::runtime_error&) {
        threw = true;
    }
    assert(threw);
    std::cout << "PASS test_hstack_throws_on_row_mismatch\n";
}

void test_vstack() {
    // A (2x3):    B (3x3):    expected (5x3):
    // 1  2  3     7  8  9     1  2  3
    // 4  5  6     10 11 12    4  5  6
    //             13 14 15    7  8  9
    //                         10 11 12
    //                         13 14 15
    Matrix A(2, 3, {1.0,  2.0,  3.0,
                    4.0,  5.0,  6.0});
    Matrix B(3, 3, {7.0,  8.0,  9.0,
                    10.0, 11.0, 12.0,
                    13.0, 14.0, 15.0});

    Matrix res = Matrix::vstack(A, B);

    // check dimensions
    assert(res.rows() == 5);
    assert(res.cols() == 3);

    // check values — top from A
    assert(approx_eq(res(0, 0), 1.0));
    assert(approx_eq(res(0, 1), 2.0));
    assert(approx_eq(res(0, 2), 3.0));
    assert(approx_eq(res(1, 0), 4.0));
    assert(approx_eq(res(1, 1), 5.0));
    assert(approx_eq(res(1, 2), 6.0));

    // check values — bottom from B
    assert(approx_eq(res(2, 0),  7.0));
    assert(approx_eq(res(2, 1),  8.0));
    assert(approx_eq(res(2, 2),  9.0));
    assert(approx_eq(res(3, 0), 10.0));
    assert(approx_eq(res(3, 1), 11.0));
    assert(approx_eq(res(3, 2), 12.0));
    assert(approx_eq(res(4, 0), 13.0));
    assert(approx_eq(res(4, 1), 14.0));
    assert(approx_eq(res(4, 2), 15.0));

    std::cout << "PASS test_vstack\n";
}

void test_vstack_throws_on_col_mismatch() {
    // different number of cols — should throw
    Matrix A(2, 3, {1.0, 2.0, 3.0, 4.0, 5.0, 6.0});
    Matrix B(2, 2, {1.0, 2.0, 3.0, 4.0});

    bool threw = false;
    try {
        Matrix res = Matrix::vstack(A, B);
    } catch (const std::runtime_error&) {
        threw = true;
    }
    assert(threw);
    std::cout << "PASS test_vstack_throws_on_col_mismatch\n";
}

void test_argmax_flat() {
    // data_ = [3, 1, 4, 1, 5, 2]
    // max = 5 at flat index 4
    Matrix a(2, 3, {3.0, 1.0, 4.0,
                    1.0, 5.0, 2.0});
    assert(a.argmax() == 4);
    std::cout << "PASS test_argmax_flat\n";
}

void test_argmax_flat_first_element() {
    // max is at index 0 — tests that initialization to idx=0 is correct
    Matrix a(2, 3, {9.0, 1.0, 4.0,
                    1.0, 5.0, 2.0});
    assert(a.argmax() == 0);
    std::cout << "PASS test_argmax_flat_first_element\n";
}

void test_argmax_flat_last_element() {
    // max is at last index — tests the loop runs to the end
    Matrix a(2, 3, {1.0, 2.0, 3.0,
                    4.0, 5.0, 9.0});
    assert(a.argmax() == 5);
    std::cout << "PASS test_argmax_flat_last_element\n";
}

void test_argmin_flat() {
    // data_ = [3, 1, 4, 1, 5, 2]
    // min = 1 at flat index 1 (first occurrence)
    Matrix a(2, 3, {3.0, 1.0, 4.0,
                    1.0, 5.0, 2.0});
    assert(a.argmin() == 1);
    std::cout << "PASS test_argmin_flat\n";
}

void test_argmin_flat_first_element() {
    // min is at index 0
    Matrix a(2, 3, {0.0, 1.0, 4.0,
                    1.0, 5.0, 2.0});
    assert(a.argmin() == 0);
    std::cout << "PASS test_argmin_flat_first_element\n";
}

void test_argmin_flat_last_element() {
    // min is at last index
    Matrix a(2, 3, {9.0, 8.0, 7.0,
                    6.0, 5.0, 1.0});
    assert(a.argmin() == 5);
    std::cout << "PASS test_argmin_flat_last_element\n";
}

void test_argmax_axis0() {
    // axis=0 → per row, which col has the max
    // row 0: max(3,1,4) → col 2
    // row 1: max(1,5,2) → col 1
    Matrix a(2, 3, {3.0, 1.0, 4.0,
                    1.0, 5.0, 2.0});
    Matrix res = a.argmax(0);

    assert(res.rows() == 2);
    assert(res.cols() == 1);
    assert(approx_eq(res(0, 0), 2.0));  // col 2
    assert(approx_eq(res(1, 0), 1.0));  // col 1
    std::cout << "PASS test_argmax_axis0\n";
}

void test_argmax_axis0_first_col() {
    // max is always in col 0 — tests initialization to best_col=0 is correct
    Matrix a(2, 3, {9.0, 1.0, 2.0,
                    8.0, 3.0, 4.0});
    Matrix res = a.argmax(0);

    assert(approx_eq(res(0, 0), 0.0));
    assert(approx_eq(res(1, 0), 0.0));
    std::cout << "PASS test_argmax_axis0_first_col\n";
}

void test_argmax_axis1() {
    // axis=1 → per col, which row has the max
    // col 0: max(3,1) → row 0
    // col 1: max(1,5) → row 1
    // col 2: max(4,2) → row 0
    Matrix a(2, 3, {3.0, 1.0, 4.0,
                    1.0, 5.0, 2.0});
    Matrix res = a.argmax(1);

    assert(res.rows() == 1);
    assert(res.cols() == 3);
    assert(approx_eq(res(0, 0), 0.0));  // row 0
    assert(approx_eq(res(0, 1), 1.0));  // row 1
    assert(approx_eq(res(0, 2), 0.0));  // row 0
    std::cout << "PASS test_argmax_axis1\n";
}

void test_argmin_axis0() {
    // axis=0 → per row, which col has the min
    // row 0: min(3,1,4) → col 1
    // row 1: min(1,5,2) → col 0
    Matrix a(2, 3, {3.0, 1.0, 4.0,
                    1.0, 5.0, 2.0});
    Matrix res = a.argmin(0);

    assert(res.rows() == 2);
    assert(res.cols() == 1);
    assert(approx_eq(res(0, 0), 1.0));  // col 1
    assert(approx_eq(res(1, 0), 0.0));  // col 0
    std::cout << "PASS test_argmin_axis0\n";
}

void test_argmin_axis1() {
    // axis=1 → per col, which row has the min
    // col 0: min(3,1) → row 1
    // col 1: min(1,5) → row 0
    // col 2: min(4,2) → row 1
    Matrix a(2, 3, {3.0, 1.0, 4.0,
                    1.0, 5.0, 2.0});
    Matrix res = a.argmin(1);

    assert(res.rows() == 1);
    assert(res.cols() == 3);
    assert(approx_eq(res(0, 0), 1.0));  // row 1
    assert(approx_eq(res(0, 1), 0.0));  // row 0
    assert(approx_eq(res(0, 2), 1.0));  // row 1
    std::cout << "PASS test_argmin_axis1\n";
}

void test_lu_decompose() {
    Matrix A(2, 2, {4.0, 3.0,
                    6.0, 3.0});

    LUResult lu = A.lu_decompose();

    assert(!lu.singular);
    assert(lu.n == 2);
    assert(lu.perm.size() == 2);
    
    // Pivoting verification
    assert(lu.sign == -1);          // One swap occurred
    assert(lu.perm[0] == 1);        // Row 0 is now old Row 1
    assert(lu.perm[1] == 0);        // Row 1 is now old Row 0

    // After swapping, the matrix processed was:
    // [[6.0, 3.0],
    //  [4.0, 3.0]]
    // L factor = 4.0 / 6.0 = 2.0 / 3.0
    // U(1,1)   = 3.0 - (2.0/3.0)*3.0 = 1.0

    // Diagonal elements of U
    assert(approx_eq(lu.data[0 * 2 + 0], 6.0));          // U(0,0) is now 6.0
    assert(approx_eq(lu.data[1 * 2 + 1], 1.0));          // U(1,1) is now 1.0

    // Below diagonal belongs to L
    assert(approx_eq(lu.data[1 * 2 + 0], 2.0 / 3.0));    // L(1,0) factor

    // Above diagonal belongs to U
    assert(approx_eq(lu.data[0 * 2 + 1], 3.0));          // U(0,1)

    std::cout << "PASS test_lu_decompose\n";
}

void test_lu_singular() {
    // row 1 = 2 * row 0 — singular
    Matrix A(2, 2, {1.0, 2.0,
                    2.0, 4.0});
    LUResult lu = A.lu_decompose();
    assert(lu.singular);
    std::cout << "PASS test_lu_singular\n";
}

void test_lu_non_square_throws() {
    Matrix A(2, 3, {1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0});
    bool threw = false;
    try {
        LUResult lu = A.lu_decompose();
    } catch (const std::runtime_error&) {
        threw = true;
    }
    assert(threw);
    std::cout << "PASS test_lu_non_square_throws\n";
}

void test_determinant_2x2() {
    // det([[3, 8], [4, 6]]) = 3*6 - 8*4 = 18 - 32 = -14
    Matrix A(2, 2, {3.0, 8.0,
                    4.0, 6.0});
    assert(approx_eq(A.determinant(), -14.0));
    std::cout << "PASS test_determinant_2x2\n";
}

void test_determinant_identity() {
    // det of identity is always 1
    Matrix I = Matrix::identity(3);
    assert(approx_eq(I.determinant(), 1.0));
    std::cout << "PASS test_determinant_identity\n";
}

void test_determinant_singular() {
    // singular matrix — det should be 0
    Matrix A(2, 2, {1.0, 2.0,
                    2.0, 4.0});
    assert(approx_eq(A.determinant(), 0.0));
    std::cout << "PASS test_determinant_singular\n";
}

void test_inverse_2x2() {
    // det = 4*6 - 7*2 = 24 - 14 = 10
    // A_inv = (1/10) * [[ 6, -7],
    //                   [-2,  4]]
    //       = [[0.6, -0.7],
    //          [-0.2, 0.4]]
    Matrix A(2, 2, {4.0, 7.0,
                    2.0, 6.0});

    Matrix A_inv = A.inverse();

    // check dimensions
    assert(A_inv.rows() == 2);
    assert(A_inv.cols() == 2);

    // check known values from closed form
    assert(approx_eq(A_inv(0, 0),  0.6));
    assert(approx_eq(A_inv(0, 1), -0.7));
    assert(approx_eq(A_inv(1, 0), -0.2));
    assert(approx_eq(A_inv(1, 1),  0.4));

    // verify A * A_inv = identity
    Matrix result = A * A_inv;
    assert(approx_eq(result(0, 0), 1.0));
    assert(approx_eq(result(0, 1), 0.0));
    assert(approx_eq(result(1, 0), 0.0));
    assert(approx_eq(result(1, 1), 1.0));

    std::cout << "PASS test_inverse_2x2\n";
}

void test_inverse_3x3() {
    // same matrix from our LU walkthrough — det = 4
    // don't compute inverse by hand, use A * A_inv = I property
    Matrix A(3, 3, {2.0, 1.0, 1.0,
                    4.0, 3.0, 3.0,
                    8.0, 7.0, 9.0});

    Matrix A_inv = A.inverse();

    // check dimensions
    assert(A_inv.rows() == 3);
    assert(A_inv.cols() == 3);

    // A * A_inv should be identity
    Matrix I      = Matrix::identity(3);
    Matrix result = A * A_inv;
    for (size_t r = 0; r < 3; r++)
        for (size_t c = 0; c < 3; c++)
            assert(approx_eq(result(r, c), I(r, c)));

    // A_inv * A should also be identity
    Matrix result2 = A_inv * A;
    for (size_t r = 0; r < 3; r++)
        for (size_t c = 0; c < 3; c++)
            assert(approx_eq(result2(r, c), I(r, c)));

    std::cout << "PASS test_inverse_3x3\n";
}

void test_solve_2x2() {
    // 2x0 + x1  = 5
    // 5x0 + 3x1 = 13
    // solution: x0 = 2, x1 = 1
    Matrix A(2, 2, {2.0, 1.0,
                    5.0, 3.0});
    Matrix b(2, 1, {5.0,
                    13.0});

    Matrix x = A.solve(b);

    assert(x.rows() == 2);
    assert(x.cols() == 1);
    assert(approx_eq(x(0, 0), 2.0));
    assert(approx_eq(x(1, 0), 1.0));

    // verify by plugging back in: A*x should equal b
    Matrix Ax = A * x;
    assert(approx_eq(Ax(0, 0),  5.0));
    assert(approx_eq(Ax(1, 0), 13.0));

    std::cout << "PASS test_solve_2x2\n";
}

void test_solve_3x3() {
    // use our walkthrough matrix — det = 4 so not singular
    // A*x = b where b = [4, 8, 12]
    // verify by checking A*x = b rather than known x values
    Matrix A(3, 3, {2.0, 1.0, 1.0,
                    4.0, 3.0, 3.0,
                    8.0, 7.0, 9.0});
    Matrix b(3, 1, {4.0,
                    8.0,
                    12.0});

    Matrix x = A.solve(b);

    assert(x.rows() == 3);
    assert(x.cols() == 1);

    // plug back in — A*x should equal b
    Matrix Ax = A * x;
    assert(approx_eq(Ax(0, 0),  4.0));
    assert(approx_eq(Ax(1, 0),  8.0));
    assert(approx_eq(Ax(2, 0), 12.0));

    std::cout << "PASS test_solve_3x3\n";
}

void test_solve_identity() {
    // I*x = b should give x = b
    Matrix I = Matrix::identity(3);
    Matrix b(3, 1, {3.0,
                    7.0,
                    2.0});

    Matrix x = I.solve(b);

    assert(approx_eq(x(0, 0), 3.0));
    assert(approx_eq(x(1, 0), 7.0));
    assert(approx_eq(x(2, 0), 2.0));

    std::cout << "PASS test_solve_identity\n";
}

void test_solve_singular_throws() {
    // singular matrix — no unique solution, should throw
    Matrix A(2, 2, {1.0, 2.0,
                    2.0, 4.0});
    Matrix b(2, 1, {1.0,
                    2.0});

    bool threw = false;
    try {
        Matrix x = A.solve(b);
    } catch (const std::runtime_error&) {
        threw = true;
    }
    assert(threw);
    std::cout << "PASS test_solve_singular_throws\n";
}

void test_solve_wrong_b_throws() {
    // b has wrong number of rows
    Matrix A(3, 3, {1.0, 0.0, 0.0,
                    0.0, 1.0, 0.0,
                    0.0, 0.0, 1.0});
    Matrix b(2, 1, {1.0, 2.0});  // wrong size

    bool threw = false;
    try {
        Matrix x = A.solve(b);
    } catch (const std::runtime_error&) {
        threw = true;
    }
    assert(threw);
    std::cout << "PASS test_solve_wrong_b_throws\n";
}

void test_random_dimensions() {
    // check shape and that values are within range
    Matrix r = Matrix::random(3, 4, 0.0, 1.0);
    assert(r.rows() == 3);
    assert(r.cols() == 4);

    // every element should be within [low, high]
    for (size_t i = 0; i < r.rows(); i++)
        for (size_t j = 0; j < r.cols(); j++) {
            assert(r(i, j) >= 0.0);
            assert(r(i, j) <= 1.0);
        }
    std::cout << "PASS test_random_dimensions\n";
}

void test_random_custom_range() {
    // values should be within [-1, 1]
    Matrix r = Matrix::random(10, 10, -1.0, 1.0);
    for (size_t i = 0; i < r.rows(); i++)
        for (size_t j = 0; j < r.cols(); j++) {
            assert(r(i, j) >= -1.0);
            assert(r(i, j) <=  1.0);
        }
    std::cout << "PASS test_random_custom_range\n";
}

void test_random_not_all_same() {
    // two random matrices of same size should not be identical
    // probability of collision is astronomically small
    Matrix a = Matrix::random(4, 4, 0.0, 1.0);
    Matrix b = Matrix::random(4, 4, 0.0, 1.0);
    assert(a != b);
    std::cout << "PASS test_random_not_all_same\n";
}

//==============================

void test_outer_product() {
    // col = [[2],   row = [[3, 4, 5]]
    //        [3]]
    //
    // outer = [[2*3, 2*4, 2*5],   = [[6,  8,  10],
    //          [3*3, 3*4, 3*5]]      [9, 12,  15]]
    Matrix col(2, 1, {2.0, 3.0});
    Matrix row(1, 3, {3.0, 4.0, 5.0});

    Matrix res = Matrix::outer_product(col, row);

    assert(res.rows() == 2);
    assert(res.cols() == 3);

    assert(approx_eq(res(0, 0),  6.0));
    assert(approx_eq(res(0, 1),  8.0));
    assert(approx_eq(res(0, 2), 10.0));
    assert(approx_eq(res(1, 0),  9.0));
    assert(approx_eq(res(1, 1), 12.0));
    assert(approx_eq(res(1, 2), 15.0));

    std::cout << "PASS test_outer_product\n";
}

void test_outer_product_wrong_shape_throws() {
    // col must be n x 1, row must be 1 x m
    Matrix a(2, 2, {1.0, 2.0, 3.0, 4.0});  // not a column vector
    Matrix b(1, 2, {1.0, 2.0});

    bool threw = false;
    try {
        Matrix res = Matrix::outer_product(a, b);
    } catch (const std::runtime_error&) {
        threw = true;
    }
    assert(threw);
    std::cout << "PASS test_outer_product_wrong_shape_throws\n";
}

void test_outer_product_vs_matmul() {
    // outer product of col * row should equal col matrix-multiplied by row
    Matrix col(3, 1, {1.0, 2.0, 3.0});
    Matrix row(1, 3, {4.0, 5.0, 6.0});

    Matrix outer  = Matrix::outer_product(col, row);
    Matrix matmul = col * row;

    assert(outer == matmul);
    std::cout << "PASS test_outer_product_vs_matmul\n";
}

//==============================

void test_row_accessor() {
    // extract row 1 from a 3x3
    Matrix A(3, 3, {1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0,
                    7.0, 8.0, 9.0});

    Matrix r = A.row(1);

    assert(r.rows() == 1);
    assert(r.cols() == 3);
    assert(approx_eq(r(0, 0), 4.0));
    assert(approx_eq(r(0, 1), 5.0));
    assert(approx_eq(r(0, 2), 6.0));

    std::cout << "PASS test_row_accessor\n";
}

void test_row_accessor_first_row() {
    Matrix A(3, 3, {1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0,
                    7.0, 8.0, 9.0});

    Matrix r = A.row(0);
    assert(approx_eq(r(0, 0), 1.0));
    assert(approx_eq(r(0, 1), 2.0));
    assert(approx_eq(r(0, 2), 3.0));
    std::cout << "PASS test_row_accessor_first_row\n";
}

void test_row_accessor_out_of_range_throws() {
    Matrix A(2, 2, {1.0, 2.0, 3.0, 4.0});
    bool threw = false;
    try {
        Matrix r = A.row(5);
    } catch (const std::runtime_error&) {
        threw = true;
    }
    assert(threw);
    std::cout << "PASS test_row_accessor_out_of_range_throws\n";
}

void test_col_accessor() {
    // extract col 2 from a 3x3
    Matrix A(3, 3, {1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0,
                    7.0, 8.0, 9.0});

    Matrix c = A.col(2);

    assert(c.rows() == 3);
    assert(c.cols() == 1);
    assert(approx_eq(c(0, 0), 3.0));
    assert(approx_eq(c(1, 0), 6.0));
    assert(approx_eq(c(2, 0), 9.0));

    std::cout << "PASS test_col_accessor\n";
}

void test_col_accessor_first_col() {
    Matrix A(3, 3, {1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0,
                    7.0, 8.0, 9.0});

    Matrix c = A.col(0);
    assert(approx_eq(c(0, 0), 1.0));
    assert(approx_eq(c(1, 0), 4.0));
    assert(approx_eq(c(2, 0), 7.0));
    std::cout << "PASS test_col_accessor_first_col\n";
}

void test_col_accessor_out_of_range_throws() {
    Matrix A(2, 2, {1.0, 2.0, 3.0, 4.0});
    bool threw = false;
    try {
        Matrix c = A.col(5);
    } catch (const std::runtime_error&) {
        threw = true;
    }
    assert(threw);
    std::cout << "PASS test_col_accessor_out_of_range_throws\n";
}

//==============================

void test_trace_square() {
    // trace = sum of diagonal = 1 + 5 + 9 = 15
    Matrix A(3, 3, {1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0,
                    7.0, 8.0, 9.0});
    assert(approx_eq(A.trace(), 15.0));
    std::cout << "PASS test_trace_square\n";
}

void test_trace_identity() {
    // trace of n x n identity = n
    Matrix I = Matrix::identity(4);
    assert(approx_eq(I.trace(), 4.0));
    std::cout << "PASS test_trace_identity\n";
}

void test_trace_non_square_throws() {
    Matrix A(2, 3, {1.0, 2.0, 3.0, 4.0, 5.0, 6.0});
    bool threw = false;
    try {
        double t = A.trace();
    } catch (const std::runtime_error&) {
        threw = true;
    }
    assert(threw);
    std::cout << "PASS test_trace_non_square_throws\n";
}

void test_broadcast_add_axis0() {
    // add row vector to every row
    // A = [[1, 2, 3],     bias = [[10, 20, 30]]
    //      [4, 5, 6],
    //      [7, 8, 9]]
    //
    // result = [[11, 22, 33],
    //           [14, 25, 36],
    //           [17, 28, 39]]
    Matrix A(3, 3, {1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0,
                    7.0, 8.0, 9.0});
    Matrix bias(1, 3, {10.0, 20.0, 30.0});

    Matrix res = A.broadcast_add(bias, 0);

    assert(res.rows() == 3);
    assert(res.cols() == 3);

    // row 0
    assert(approx_eq(res(0, 0), 11.0));
    assert(approx_eq(res(0, 1), 22.0));
    assert(approx_eq(res(0, 2), 33.0));
    // row 1
    assert(approx_eq(res(1, 0), 14.0));
    assert(approx_eq(res(1, 1), 25.0));
    assert(approx_eq(res(1, 2), 36.0));
    // row 2
    assert(approx_eq(res(2, 0), 17.0));
    assert(approx_eq(res(2, 1), 28.0));
    assert(approx_eq(res(2, 2), 39.0));

    std::cout << "PASS test_broadcast_add_axis0\n";
}

void test_broadcast_add_axis1() {
    // add column vector to every column
    // A = [[1, 2, 3],     bias = [[10],
    //      [4, 5, 6],              [20],
    //      [7, 8, 9]]              [30]]
    //
    // result = [[11, 12, 13],
    //           [24, 25, 26],
    //           [37, 38, 39]]
    Matrix A(3, 3, {1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0,
                    7.0, 8.0, 9.0});
    Matrix bias(3, 1, {10.0, 20.0, 30.0});

    Matrix res = A.broadcast_add(bias, 1);

    assert(res.rows() == 3);
    assert(res.cols() == 3);

    // row 0
    assert(approx_eq(res(0, 0), 11.0));
    assert(approx_eq(res(0, 1), 12.0));
    assert(approx_eq(res(0, 2), 13.0));
    // row 1
    assert(approx_eq(res(1, 0), 24.0));
    assert(approx_eq(res(1, 1), 25.0));
    assert(approx_eq(res(1, 2), 26.0));
    // row 2
    assert(approx_eq(res(2, 0), 37.0));
    assert(approx_eq(res(2, 1), 38.0));
    assert(approx_eq(res(2, 2), 39.0));

    std::cout << "PASS test_broadcast_add_axis1\n";
}

void test_broadcast_add_does_not_modify_original() {
    // broadcast_add is const — original should be unchanged
    Matrix A(2, 3, {1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0});
    Matrix bias(1, 3, {10.0, 10.0, 10.0});

    Matrix res = A.broadcast_add(bias, 0);

    // A should be exactly as before
    assert(approx_eq(A(0, 0), 1.0));
    assert(approx_eq(A(0, 1), 2.0));
    assert(approx_eq(A(1, 0), 4.0));
    assert(approx_eq(A(1, 2), 6.0));

    std::cout << "PASS test_broadcast_add_does_not_modify_original\n";
}

void test_broadcast_add_non_square() {
    // works on non-square matrices too
    // A (2x3) + row bias (1x3)
    Matrix A(2, 3, {1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0});
    Matrix bias(1, 3, {1.0, 2.0, 3.0});

    Matrix res = A.broadcast_add(bias, 0);

    assert(res.rows() == 2);
    assert(res.cols() == 3);
    assert(approx_eq(res(0, 0), 2.0));
    assert(approx_eq(res(0, 1), 4.0));
    assert(approx_eq(res(0, 2), 6.0));
    assert(approx_eq(res(1, 0), 5.0));
    assert(approx_eq(res(1, 1), 7.0));
    assert(approx_eq(res(1, 2), 9.0));

    std::cout << "PASS test_broadcast_add_non_square\n";
}

void test_broadcast_add_axis0_wrong_cols_throws() {
    // bias has wrong number of cols — should throw
    Matrix A(3, 3, {1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0,
                    7.0, 8.0, 9.0});
    Matrix bias(1, 2, {10.0, 20.0});  // 2 cols, A has 3

    bool threw = false;
    try {
        Matrix res = A.broadcast_add(bias, 0);
    } catch (const std::runtime_error&) {
        threw = true;
    }
    assert(threw);
    std::cout << "PASS test_broadcast_add_axis0_wrong_cols_throws\n";
}

void test_broadcast_add_axis1_wrong_rows_throws() {
    // bias has wrong number of rows — should throw
    Matrix A(3, 3, {1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0,
                    7.0, 8.0, 9.0});
    Matrix bias(2, 1, {10.0, 20.0});  // 2 rows, A has 3

    bool threw = false;
    try {
        Matrix res = A.broadcast_add(bias, 1);
    } catch (const std::runtime_error&) {
        threw = true;
    }
    assert(threw);
    std::cout << "PASS test_broadcast_add_axis1_wrong_rows_throws\n";
}

void test_softmax_sums_to_one() {
    // output must always sum to 1.0 regardless of input
    Matrix a(1, 4, {1.0, 2.0, 3.0, 4.0});
    Matrix res = a.softmax();
    assert(approx_eq(res.sum(), 1.0));
    std::cout << "PASS test_softmax_sums_to_one\n";
}

void test_softmax_known_values() {
    // [1, 2, 3] — computed by hand above
    Matrix a(1, 3, {1.0, 2.0, 3.0});
    Matrix res = a.softmax();

    assert(res.rows() == 1);
    assert(res.cols() == 3);
    assert(approx_eq(res(0, 0), 0.090, 1e-3));
    assert(approx_eq(res(0, 1), 0.245, 1e-3));
    assert(approx_eq(res(0, 2), 0.665, 1e-3));
    std::cout << "PASS test_softmax_known_values\n";
}

void test_softmax_all_same_input() {
    // equal inputs → equal outputs → each = 1/n
    // [2, 2, 2, 2] → [0.25, 0.25, 0.25, 0.25]
    Matrix a(1, 4, {2.0, 2.0, 2.0, 2.0});
    Matrix res = a.softmax();

    for (size_t c = 0; c < 4; c++)
        assert(approx_eq(res(0, c), 0.25));
    assert(approx_eq(res.sum(), 1.0));
    std::cout << "PASS test_softmax_all_same_input\n";
}

void test_softmax_all_values_positive() {
    // softmax output is always in (0, 1)
    Matrix a(1, 5, {-2.0, -1.0, 0.0, 1.0, 2.0});
    Matrix res = a.softmax();

    for (size_t c = 0; c < 5; c++) {
        assert(res(0, c) > 0.0);
        assert(res(0, c) < 1.0);
    }
    assert(approx_eq(res.sum(), 1.0));
    std::cout << "PASS test_softmax_all_values_positive\n";
}

void test_softmax_large_values() {
    // large inputs can cause overflow if not implemented with numeric stability
    // e.g. e^1000 = inf — stable softmax subtracts max first
    Matrix a(1, 3, {1000.0, 1001.0, 1002.0});
    Matrix res = a.softmax();

    // should not produce nan or inf
    for (size_t c = 0; c < 3; c++) {
        assert(!std::isnan(res(0, c)));
        assert(!std::isinf(res(0, c)));
        assert(res(0, c) > 0.0);
    }
    assert(approx_eq(res.sum(), 1.0));
    std::cout << "PASS test_softmax_large_values\n";
}

void test_softmax_does_not_modify_original() {
    Matrix a(1, 3, {1.0, 2.0, 3.0});
    Matrix res = a.softmax();

    assert(approx_eq(a(0, 0), 1.0));
    assert(approx_eq(a(0, 1), 2.0));
    assert(approx_eq(a(0, 2), 3.0));
    std::cout << "PASS test_softmax_does_not_modify_original\n";
}

void test_softmax_axis0() {
    // axis=0 — softmax across each row independently
    // row 0: softmax([1, 2]) 
    // row 1: softmax([3, 4])
    // each row should sum to 1.0
    Matrix a(2, 2, {1.0, 2.0,
                    3.0, 4.0});
    Matrix res = a.softmax(0);

    assert(res.rows() == 2);
    assert(res.cols() == 2);

    // each row sums to 1
    assert(approx_eq(res(0, 0) + res(0, 1), 1.0));
    assert(approx_eq(res(1, 0) + res(1, 1), 1.0));

    // larger input → larger softmax output within same row
    assert(res(0, 1) > res(0, 0));  // 2 > 1
    assert(res(1, 1) > res(1, 0));  // 4 > 3

    std::cout << "PASS test_softmax_axis0\n";
}

void test_softmax_axis1() {
    // axis=1 — softmax down each column independently
    // col 0: softmax([1, 3])
    // col 1: softmax([2, 4])
    // each column should sum to 1.0
    Matrix a(2, 2, {1.0, 2.0,
                    3.0, 4.0});
    Matrix res = a.softmax(1);

    assert(res.rows() == 2);
    assert(res.cols() == 2);

    // each col sums to 1
    assert(approx_eq(res(0, 0) + res(1, 0), 1.0));
    assert(approx_eq(res(0, 1) + res(1, 1), 1.0));

    // larger input → larger softmax output within same col
    assert(res(1, 0) > res(0, 0));  // 3 > 1
    assert(res(1, 1) > res(0, 1));  // 4 > 2

    std::cout << "PASS test_softmax_axis1\n";
}
//==============================
// relu tests
//==============================

// void test_relu() {
//     // negative values → 0, positive values → unchanged
//     Matrix a(2, 3, {-3.0, -1.0,  0.0,
//                      1.0,  2.0,  5.0});
//     Matrix res = a.relu();

//     assert(approx_eq(res(0, 0), 0.0));
//     assert(approx_eq(res(0, 1), 0.0));
//     assert(approx_eq(res(0, 2), 0.0));
//     assert(approx_eq(res(1, 0), 1.0));
//     assert(approx_eq(res(1, 1), 2.0));
//     assert(approx_eq(res(1, 2), 5.0));
//     std::cout << "PASS test_relu\n";
// }

// void test_relu_does_not_modify_original() {
//     Matrix a(2, 2, {-1.0, 2.0,
//                     -3.0, 4.0});
//     Matrix res = a.relu();
//     assert(approx_eq(a(0, 0), -1.0));
//     assert(approx_eq(a(1, 0), -3.0));
//     std::cout << "PASS test_relu_does_not_modify_original\n";
// }

// void test_relu_derivative() {
//     // derivative: 1 where x > 0, 0 elsewhere
//     Matrix a(2, 3, {-3.0, -1.0,  0.0,
//                      1.0,  2.0,  5.0});
//     Matrix res = a.relu_derivative();

//     assert(approx_eq(res(0, 0), 0.0));
//     assert(approx_eq(res(0, 1), 0.0));
//     assert(approx_eq(res(0, 2), 0.0));  // 0 → derivative is 0
//     assert(approx_eq(res(1, 0), 1.0));
//     assert(approx_eq(res(1, 1), 1.0));
//     assert(approx_eq(res(1, 2), 1.0));
//     std::cout << "PASS test_relu_derivative\n";
// }

// //==============================
// // sigmoid tests
// //==============================

// void test_sigmoid_known_values() {
//     // sigmoid(0) = 0.5 exactly
//     // sigmoid(large positive) → 1
//     // sigmoid(large negative) → 0
//     Matrix a(1, 3, {0.0, 10.0, -10.0});
//     Matrix res = a.sigmoid();

//     assert(approx_eq(res(0, 0), 0.5));
//     assert(approx_eq(res(0, 1), 1.0, 1e-4));   // very close to 1
//     assert(approx_eq(res(0, 2), 0.0, 1e-4));   // very close to 0
//     std::cout << "PASS test_sigmoid_known_values\n";
// }

// void test_sigmoid_output_range() {
//     // all outputs must be strictly between 0 and 1
//     Matrix a(2, 3, {-5.0, -1.0,  0.0,
//                      1.0,  5.0, 10.0});
//     Matrix res = a.sigmoid();

//     for (size_t r = 0; r < 2; r++)
//         for (size_t c = 0; c < 3; c++) {
//             assert(res(r, c) > 0.0);
//             assert(res(r, c) < 1.0);
//         }
//     std::cout << "PASS test_sigmoid_output_range\n";
// }

// void test_sigmoid_derivative() {
//     // sigmoid_derivative(x) = sigmoid(x) * (1 - sigmoid(x))
//     // at x=0: sigmoid(0) = 0.5, derivative = 0.5 * 0.5 = 0.25
//     Matrix a(1, 1, {0.0});
//     Matrix res = a.sigmoid_derivative();
//     assert(approx_eq(res(0, 0), 0.25));
//     std::cout << "PASS test_sigmoid_derivative\n";
// }

// void test_sigmoid_does_not_modify_original() {
//     Matrix a(2, 2, {1.0, 2.0,
//                     3.0, 4.0});
//     Matrix res = a.sigmoid();
//     assert(approx_eq(a(0, 0), 1.0));
//     assert(approx_eq(a(1, 1), 4.0));
//     std::cout << "PASS test_sigmoid_does_not_modify_original\n";
// }

//==============================
// set_row / set_col tests
//==============================

void test_set_row() {
    Matrix A(3, 3, {1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0,
                    7.0, 8.0, 9.0});
    Matrix new_row(1, 3, {10.0, 20.0, 30.0});

    A.set_row(1, new_row);

    assert(approx_eq(A(1, 0), 10.0));
    assert(approx_eq(A(1, 1), 20.0));
    assert(approx_eq(A(1, 2), 30.0));

    // other rows unchanged
    assert(approx_eq(A(0, 0), 1.0));
    assert(approx_eq(A(2, 2), 9.0));
    std::cout << "PASS test_set_row\n";
}

void test_set_row_out_of_range_throws() {
    Matrix A(2, 2, {1.0, 2.0, 3.0, 4.0});
    Matrix new_row(1, 2, {5.0, 6.0});
    bool threw = false;
    try {
        A.set_row(5, new_row);
    } catch (const std::runtime_error&) {
        threw = true;
    }
    assert(threw);
    std::cout << "PASS test_set_row_out_of_range_throws\n";
}

void test_set_row_wrong_size_throws() {
    Matrix A(2, 3, {1.0, 2.0, 3.0, 4.0, 5.0, 6.0});
    Matrix new_row(1, 2, {5.0, 6.0});  // wrong cols
    bool threw = false;
    try {
        A.set_row(0, new_row);
    } catch (const std::runtime_error&) {
        threw = true;
    }
    assert(threw);
    std::cout << "PASS test_set_row_wrong_size_throws\n";
}

void test_set_col() {
    Matrix A(3, 3, {1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0,
                    7.0, 8.0, 9.0});
    Matrix new_col(3, 1, {10.0, 20.0, 30.0});

    A.set_col(1, new_col);

    assert(approx_eq(A(0, 1), 10.0));
    assert(approx_eq(A(1, 1), 20.0));
    assert(approx_eq(A(2, 1), 30.0));

    // other cols unchanged
    assert(approx_eq(A(0, 0), 1.0));
    assert(approx_eq(A(0, 2), 3.0));
    std::cout << "PASS test_set_col\n";
}

void test_set_col_out_of_range_throws() {
    Matrix A(2, 2, {1.0, 2.0, 3.0, 4.0});
    Matrix new_col(2, 1, {5.0, 6.0});
    bool threw = false;
    try {
        A.set_col(5, new_col);
    } catch (const std::runtime_error&) {
        threw = true;
    }
    assert(threw);
    std::cout << "PASS test_set_col_out_of_range_throws\n";
}

//==============================
// diag tests
//==============================

void test_diag_extract() {
    // extract diagonal from square matrix
    Matrix A(3, 3, {1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0,
                    7.0, 8.0, 9.0});
    Matrix d = A.diag();

    assert(d.rows() == 3);
    assert(d.cols() == 1);
    assert(approx_eq(d(0, 0), 1.0));
    assert(approx_eq(d(1, 0), 5.0));
    assert(approx_eq(d(2, 0), 9.0));
    std::cout << "PASS test_diag_extract\n";
}

void test_diag_construct() {
    // construct diagonal matrix from column vector
    Matrix v(3, 1, {2.0, 5.0, 8.0});
    Matrix D = Matrix::diag(v);

    assert(D.rows() == 3);
    assert(D.cols() == 3);

    // diagonal should match v
    assert(approx_eq(D(0, 0), 2.0));
    assert(approx_eq(D(1, 1), 5.0));
    assert(approx_eq(D(2, 2), 8.0));

    // off-diagonal should be zero
    assert(approx_eq(D(0, 1), 0.0));
    assert(approx_eq(D(1, 0), 0.0));
    assert(approx_eq(D(0, 2), 0.0));
    std::cout << "PASS test_diag_construct\n";
}

void test_diag_non_square_throws() {
    Matrix A(2, 3, {1.0, 2.0, 3.0, 4.0, 5.0, 6.0});
    bool threw = false;
    try {
        Matrix d = A.diag();
    } catch (const std::runtime_error&) {
        threw = true;
    }
    assert(threw);
    std::cout << "PASS test_diag_non_square_throws\n";
}

//==============================
// approx_equal tests
//==============================

void test_approx_equal_identical() {
    Matrix a(2, 2, {1.0, 2.0, 3.0, 4.0});
    Matrix b(2, 2, {1.0, 2.0, 3.0, 4.0});
    assert(a.approx_equal(b));
    std::cout << "PASS test_approx_equal_identical\n";
}

void test_approx_equal_within_tolerance() {
    Matrix a(1, 3, {1.0,     2.0,     3.0    });
    Matrix b(1, 3, {1.0+1e-10, 2.0-1e-10, 3.0+1e-10});
    assert(a.approx_equal(b));
    std::cout << "PASS test_approx_equal_within_tolerance\n";
}

void test_approx_equal_outside_tolerance() {
    Matrix a(1, 2, {1.0, 2.0});
    Matrix b(1, 2, {1.1, 2.0});
    assert(!a.approx_equal(b));
    std::cout << "PASS test_approx_equal_outside_tolerance\n";
}

void test_approx_equal_custom_tolerance() {
    Matrix a(1, 2, {1.0, 2.0});
    Matrix b(1, 2, {1.05, 2.05});
    assert(!a.approx_equal(b, 1e-9));  // fails with tight tolerance
    assert( a.approx_equal(b, 0.1));   // passes with loose tolerance
    std::cout << "PASS test_approx_equal_custom_tolerance\n";
}

void test_approx_equal_different_shapes() {
    Matrix a(2, 2, {1.0, 2.0, 3.0, 4.0});
    Matrix b(1, 4, {1.0, 2.0, 3.0, 4.0});
    assert(!a.approx_equal(b));
    std::cout << "PASS test_approx_equal_different_shapes\n";
}

int main() {
    test_construction();
    test_element_access();
    test_multiplication_default_constructor();
    test_multiplication_factor();
    test_division_factor();
    test_addition_elementwise();
    test_scalar_addition();
    test_subtraction_elementwise();
    test_scalar_subtraction();
    test_dot_product();
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
    test_transpose();
    test_slice();
    test_zeros();
    test_ones();
    test_identity();
    test_fill();
    test_clip();
    test_reshape();
    test_flatten();
    test_hstack();
    test_hstack_throws_on_row_mismatch();
    test_vstack();
    test_vstack_throws_on_col_mismatch();
    test_argmax_flat();
    test_argmax_flat_first_element();
    test_argmax_flat_last_element();
    test_argmin_flat();
    test_argmin_flat_first_element();
    test_argmin_flat_last_element();
    test_argmax_axis0();
    test_argmax_axis0_first_col();
    test_argmax_axis1();
    test_argmin_axis0();
    test_argmin_axis1();
    test_lu_decompose();
    test_lu_singular();
    test_lu_non_square_throws();
    test_determinant_2x2();
    test_determinant_identity();
    test_determinant_singular();
    test_inverse_2x2();
    test_inverse_3x3();
    test_solve_2x2();
    test_solve_3x3();
    test_solve_identity();
    test_solve_singular_throws();
    test_solve_wrong_b_throws();
    test_random_dimensions();
    test_random_custom_range();
    test_random_not_all_same();
    test_outer_product();
    test_outer_product_wrong_shape_throws();
    test_outer_product_vs_matmul();
    test_row_accessor();
    test_row_accessor_first_row();
    test_row_accessor_out_of_range_throws();
    test_col_accessor();
    test_col_accessor_first_col();
    test_col_accessor_out_of_range_throws();
    test_trace_square();
    test_trace_identity();
    test_trace_non_square_throws();
    test_broadcast_add_axis0();
    test_broadcast_add_axis1();
    test_broadcast_add_does_not_modify_original();
    test_broadcast_add_non_square();
    test_broadcast_add_axis0_wrong_cols_throws();
    test_broadcast_add_axis1_wrong_rows_throws();
    test_softmax_sums_to_one();
    test_softmax_known_values();
    test_softmax_all_same_input();
    test_softmax_all_values_positive();
    test_softmax_large_values();
    test_softmax_does_not_modify_original();
    test_softmax_axis0();
    test_softmax_axis1();
    test_set_row();
    test_set_row_out_of_range_throws();
    test_set_row_wrong_size_throws();
    test_set_col();
    test_set_col_out_of_range_throws();
    test_diag_extract();
    test_diag_construct();
    test_diag_non_square_throws();
    test_approx_equal_identical();
    test_approx_equal_within_tolerance();
    test_approx_equal_outside_tolerance();
    test_approx_equal_custom_tolerance();
    test_approx_equal_different_shapes();
    std::cout << "\nAll tests passed.\n";
    return 0;
}