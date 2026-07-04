/**
 * include/matrix.hpp
 * author: Bao Le
 */

#pragma once

#include <fstream>
#include <vector>
#include <cstddef>   
#include <stdexcept> 
#include <iostream>
#include <optional>
#include <tuple>

class Matrix {
    private:
        size_t rows_, cols_;
        std::vector<double> data_;  // row-major storage

    public:
        Matrix();
        // default constructor, all zeroes
        Matrix(size_t rows, size_t cols);

        // constructor with specific inputs
        Matrix(size_t rows, size_t cols, std::vector<double> ip);

        // Matrix shape (rows, cols)
        std::tuple<size_t, size_t> shape() const;
        
        // Element access
        double operator()(size_t r, size_t c) const;    // reading
        double& operator()(size_t r, size_t c); // writing

        // Dimensions
        size_t rows() const { return rows_; }
        size_t cols() const { return cols_; }

        // Multiplication
        Matrix operator*(const Matrix& other) const;
        Matrix operator*(double factor) const;
        Matrix& operator*=(const Matrix& other);
        Matrix& operator*=(double factor);

        // Addition
        Matrix operator+(const Matrix& other) const;
        Matrix& operator+(const Matrix& other);
        Matrix& operator+=(const Matrix& other);

        // Subtraction
        Matrix operator-(const Matrix& other) const;
        Matrix& operator-(const Matrix& other);
        Matrix& operator-=(const Matrix& other);

        // Division
        Matrix operator/(double scalar) const;
        Matrix& operator/(double scalar);
        Matrix& operator/= (double scalar);

        // Comparison
        bool operator==(const Matrix& other) const;
        bool operator!=(const Matrix& other) const;

        // Structural
        Matrix transpose() const;
        Matrix slice(size_t r0, size_t r1, size_t c0, size_t c1) const;

        // Reductions
        double sum() const;
        Matrix sum(int axis) const;
        Matrix mean(int axis) const;
        double mean() const;
        double max() const;
        Matrix max(int axis) const;
        double min() const;
        Matrix min(int axis) const;
    
        // Custom application
        Matrix apply(std::function<double(double)> func); 
        Matrix& apply_(std::function<double(double)> func); 
        
        // Matrix utils
        static Matrix zeros(size_t rows, size_t cols);
        static Matrix ones(size_t rows, size_t cols);
        static Matrix identity(size_t n);

        friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
};