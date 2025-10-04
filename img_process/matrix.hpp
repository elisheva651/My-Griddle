#pragma once

#include <vector>
#include <stdexcept>
#include <cstddef>  
#include <utility>  

namespace img
{

/**
 * @brief A simple 2D matrix class for storing elements in row-major order.
 * 
 * @tparam T The type of elements stored in the matrix.
 */
template <typename T>
class Matrix {

public:
    // Constructors
    Matrix() = default;

    /**
     * @brief Constructs a Matrix of given dimensions, initialized with a specified value.
     * 
     * @param rows Number of rows.
     * @param cols Number of columns.
     * @param value Value to initialize all elements with (default-constructed if not specified).
     */
    Matrix(size_t rows, size_t cols, const T& value = T{});

    /**
     * @brief Copy constructor.
     * 
     * @param other Matrix to copy from.
     */
    Matrix(const Matrix& other);

    /**
     * @brief Move constructor.
     * 
     * @param other Matrix to move from.
     */
    Matrix(Matrix&& other) noexcept;

    /**
     * @brief Copy assignment operator.
     * 
     * @param other Matrix to copy from.
     * @return Reference to this matrix.
     */
    Matrix& operator=(const Matrix& other);

    /**
     * @brief Constructs a Matrix from existing data.
     * 
     * @param rows Number of rows.
     * @param cols Number of columns.
     * @param data Flat vector of data in row-major order.
     */
    Matrix(size_t rows, size_t cols, std::vector<T> data);

    /**
     * @brief Move assignment operator.
     * 
     * @param other Matrix to move from.
     * @return Reference to this matrix.
     */
    Matrix& operator=(Matrix&& other) noexcept;

    /**
     * @brief Access a row of elements (modifiable).
     * 
     * @param row Row index.
     * @return Pointer to the first element of the specified row.
     */
    T* operator[](size_t row);

    /**
     * @brief Access a row of elements (read-only).
     * 
     * @param row Row index.
     * @return Const pointer to the first element of the specified row.
     */
    const T* operator[](size_t row) const;

    /**
     * @brief Returns the number of rows.
     * 
     * @return Number of rows.
     */
    size_t rows() const noexcept;

    /**
     * @brief Returns the number of columns.
     * 
     * @return Number of columns.
     */
    size_t cols() const noexcept;

    /**
     * @brief Swaps contents with another matrix.
     * 
     * @param other Matrix to swap with.
     */
    void swap(Matrix& other) noexcept;

private:
    size_t rows_; ///< Number of rows.
    size_t cols_; ///< Number of columns.
    std::vector<T> data_; ///< Data storage (row-major).

    /**
     * @brief Computes the flat index in data_ for a given (row, col) pair.
     * 
     * @param row Row index.
     * @param col Column index.
     * @return Flat index corresponding to (row, col).
     */
    size_t index(size_t row, size_t col) const noexcept;

    /**
     * @brief Checks if a given (row, col) is within bounds. Throws std::out_of_range if not.
     * 
     * @param row Row index to check.
     * @param col Column index to check.
     */
    void check_bounds(size_t row, size_t col) const;
};

} // namespace img

#include "matrix.inl"