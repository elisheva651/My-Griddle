#pragma once

#include "matrix.hpp"

namespace img
{
template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols, const T &value)
: rows_(rows), cols_(cols), data_(rows * cols, value)
{
    if (rows == 0 || cols == 0)
        throw std::invalid_argument("Matrix dimensions must be nonzero");
}

template <typename T>
Matrix<T>::Matrix(const Matrix &other)
: rows_(other.rows_), cols_(other.cols_), data_(other.data_)
{
}

template <typename T>
Matrix<T>::Matrix(Matrix &&other) noexcept
: rows_(0), cols_(0)
{
    swap(other);
}

template <typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix &other) {
    if (this != &other) {
        Matrix temp(other);
        swap(temp);
    }
    return *this;
}

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols, std::vector<T> data)
: rows_(rows), cols_(cols), data_(std::move(data))
{
    if (rows == 0 || cols == 0) {
        throw std::invalid_argument("Matrix dimensions must be nonzero");
}   
    if (data_.size() != rows_ * cols_) {
        throw std::invalid_argument("Data size does not match matrix dimensions");
    }
}

template <typename T>
Matrix<T> &Matrix<T>::operator=(Matrix &&other) noexcept
{
    if (this != &other) {
        swap(other);
    }
    return *this;
}

template <typename T>
T *Matrix<T>::operator[](size_t row) {
    if (row >= rows_)
        throw std::out_of_range("Row index out of bounds");
    return &data_[row * cols_];
}

template <typename T>
const T *Matrix<T>::operator[](size_t row) const {
    if (row >= rows_) {
        throw std::out_of_range("Row index out of bounds");
    }    
    return &data_[row * cols_];
}

template <typename T>
size_t Matrix<T>::rows() const noexcept
{
    return  rows_;
}

template <typename T>
size_t Matrix<T>::cols() const noexcept
{
    return cols_;
}

template <typename T>
void Matrix<T>::swap(Matrix &other) noexcept {
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    data_.swap(other.data_);
}

template <typename T>
size_t Matrix<T>::index(size_t row, size_t col) const noexcept
{
    return row * cols_ + col;
}

template <typename T>
void Matrix<T>::check_bounds(size_t row, size_t col) const
{
    if (row >= rows_ || col >= cols_) {
        throw std::out_of_range("Matrix subscript out of bounds");
    }
}

} // namespace img