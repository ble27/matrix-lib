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
    std::cout << "\nAll tests passed.\n";
    return 0;
}