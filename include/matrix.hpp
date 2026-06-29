/**
 * include/matrix.hpp
 * author: Bao Le
 */

#pragma once

#include <vector>
#include <cstddef>   
#include <stdexcept> 
#include <iostream>

class Matrix {
    public:
        // rows x cols, all zeroes
        Matrix(size_t rows, size_t cols);

        // Element access
        double operator()(size_t r, size_t c) const;    // reading
        double& operator()(size_t r, size_t c); // writing

        // Dimensions
        size_t rows() const { return rows_; }
        size_t cols() const { return cols_; }

        // Matrix multiply - the core operation
        Matrix operator*(const Matrix& other) const;

        // Print
        void print() const;

    private:
        size_t rows_, cols_;
        std::vector<double> data_;  // row-major storage
};