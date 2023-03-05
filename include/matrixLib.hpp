#ifndef MATRIXLIB_H
#define MATRIXLIB_H

#include <array>
#include <iostream>
#include <type_traits>
#include <initializer_list>
#include <type_traits>
#include <algorithm>
#include <string>
#include <sstream>

#include "utils.h"

namespace MatrixLib {
    /**
     * @brief A class representing a matrix of arbitrary size.
     * @tparam _Scalar The scalar type of the matrix elements. Must be a numeric type.
     * @tparam _RowCount The number of rows in the matrix.
     * @tparam _ColCount The number of columns in the matrix.
     */
    template <typename _Scalar, size_t _RowCount, size_t _ColCount>
    class Matrix {
        static_assert(std::is_arithmetic<_Scalar>::value, "Matrix element type must be numeric");
        std::array<std::array<_Scalar, _ColCount>, _RowCount> data_;

    public:
        /**
         * @brief Default constructor that initializes all elements to zero.
         */
        constexpr Matrix() :data_{} {}

        /**
         * @brief Constructor that initializes the matrix from an initializer list.
         * @param list The initializer list of lists of _Scalar values. The outer list must have _RowCount elements,
         * and each inner list must have _ColCount elements.
         * @throw std::invalid_argument if the dimensions of the initializer list do not match the dimensions of the matrix.
         */
        constexpr Matrix(std::initializer_list<std::initializer_list<_Scalar>> list) :data_{} {
            if (list.size() != _RowCount) {
                Utils::throw_invalid_argument_error("Expected %zu rows in initializer list, got %zu instead", _RowCount, list.size());
            }

            for (size_t i = 0; i < _RowCount; ++i) {
                auto& row = list.begin()[i];

                if (row.size() != _ColCount) {
                    Utils::throw_invalid_argument_error("Expected %zu columns in initializer list, got %zu on row %zu", _ColCount, row.size(), i);
                }

                for (size_t j = 0; j < _ColCount; ++j) {
                    data_[i][j] = list.begin()[i].begin()[j];
                }
            }
        }

        /**
         * @brief Constructor that initializes the matrix from a std::array of std::arrays.
         * @param data The std::array of std::arrays representing the matrix elements.
         */
        constexpr Matrix(const std::array<std::array<_Scalar, _ColCount>, _RowCount>& data) : data_{data} {}

        /**
         * @brief Copy constructor.
         * @param other The Matrix object to copy from.
         */
        constexpr Matrix(const Matrix& other) : Matrix(other.data_) {}

        /**
         * @brief Move constructor.
         * @param other The Matrix object to move from.
         */
        constexpr Matrix(Matrix&& other) : Matrix(std::move(other.data_)) {}

        /**
         * @brief Assigns the contents of another matrix to this matrix using the copy assignment operator.
         * 
         * @tparam _Scalar The scalar type of the matrix.
         * @tparam _RowCount The number of rows in the matrix.
         * @tparam _ColCount The number of columns in the matrix.
         * @param other The matrix to copy from.
         * @return A reference to this matrix.
         */
        constexpr Matrix& operator=(const Matrix& other) {
            this->data_ = other.data_;
            return *this;
        }

        /**
         * @brief Assigns the contents of another matrix to this matrix using the move assignment operator.
         * 
         * @tparam _Scalar The scalar type of the matrix.
         * @tparam _RowCount The number of rows in the matrix.
         * @tparam _ColCount The number of columns in the matrix.
         * @param other The matrix to move from.
         * @return A reference to this matrix.
         */
        constexpr Matrix& operator=(Matrix&& other) {
            this->data_ = std::move(other.data_);
            return *this;
        }

        /**
         * @brief Destroys the matrix and releases any allocated resources.
         * 
         * @tparam _Scalar The scalar type of the matrix.
         * @tparam _RowCount The number of rows in the matrix.
         * @tparam _ColCount The number of columns in the matrix.
         * @remark This destructor is implicitly declared as a defaulted function.
         */
        ~Matrix() = default;

    public: 
        /**
         * Access an element in the matrix using the subscript operator.
         *
         * @param index The row index of the element to access.
         * @return A constant reference to the array of elements in the specified row.
         */
        constexpr const std::array<_Scalar, _ColCount>& operator[](size_t index) const {
            if (index >= _RowCount) Utils::throw_out_of_range_error("Index %zu is out of bounds", index);

            return this->data_[index];
        }

        /**
         * Access an element in the matrix using the function call operator.
         *
         * @param indexOuter The row index of the element to access.
         * @param indexInner The column index of the element to access.
         * @return A constant reference to the element at the specified row and column.
         */
        constexpr const _Scalar& operator()(size_t indexOuter, size_t indexInner) const {
            if (indexOuter < 0 || indexOuter >= _RowCount) Utils::throw_out_of_range_error("Index outer %zu is out of bounds", indexOuter);
            if (indexInner < 0 || indexInner >= _ColCount) Utils::throw_out_of_range_error("index inner %zu is out of bounds", indexInner);

            return this->data_[indexOuter][indexInner];
        }

        /**
         * Access an element in the matrix using the subscript operator.
         *
         * @param index The row index of the element to access.
         * @return A reference to the array of elements in the specified row.
         */
        constexpr std::array<_Scalar, _ColCount>& operator[](size_t index) {
            if (index >= _RowCount) Utils::throw_out_of_range_error("Index %zu is out of bounds", index);

            return this->data_[index];
        }

        /**
         * Access an element in the matrix using the function call operator.
         *
         * @param indexOuter The row index of the element to access.
         * @param indexInner The column index of the element to access.
         * @return A reference to the element at the specified row and column.
         */
        constexpr _Scalar& operator()(size_t indexOuter, size_t indexInner) {
            if (indexOuter >= _RowCount) Utils::throw_out_of_range_error("Index outer %zu is out of bounds", indexOuter);
            if (indexInner >= _ColCount) Utils::throw_out_of_range_error("index inner %zu is out of bounds", indexInner);

            return this->data_[indexOuter][indexInner];
        }

        /**
         * @brief Check if the matrix is equal to another matrix.
         *
         * @param other The matrix to compare against.
         * @return True if the matrices are equal, false otherwise.
         */
        constexpr bool operator==(const Matrix& other) const {
            for (size_t i = 0; i < _RowCount; ++i) {
                for (size_t j = 0; j < _ColCount; ++j) {
                    if (this->data_[i][j] != other.data_[i][j]) return false;
                }
            }

            return true;
        }

        /**
         * @brief Check if the matrix is not equal to another matrix.
         *
         * @param other The matrix to compare against.
         * @return True if the matrices are not equal, false otherwise.
         */
        constexpr bool operator!=(const Matrix& other) const {
            return !(operator==(other));
        }


        /**
         * Add another matrix to this matrix element-wise.
         *
         * @pre The number of columns and rows in both matrices must be equivalent
         * @post The resulting matrix will have the same column and row count
         * 
         * @param other The matrix to add to this matrix.
         * @return A reference to this matrix after the addition.
         */
        constexpr Matrix& operator+=(const Matrix& other) {
            for (size_t i = 0; i < _RowCount; ++i) {
                for (size_t j = 0; j < _ColCount; ++j) {
                    this->data_[i][j] += other.data_[i][j];
                }
            }

            return *this;
        }

        /**
         * Subtract another matrix to this matrix element-wise.
         *
         * @pre The number of columns and rows in both matrices must be equivalent
         * @post The resulting matrix will have the same column and row count
         * 
         * @param other The matrix to subtract from this matrix.
         * @return A reference to this matrix after the addition.
         */
        constexpr Matrix& operator-=(const Matrix& other) {
            for (size_t i = 0; i < _RowCount; ++i) {
                for (size_t j = 0; j < _ColCount; ++j) {
                    this->data_[i][j] -= other.data_[i][j];
                }
            }

            return *this;
        }

        /**
         * Multiply this matrix by a scalar value.
         *
         * @tparam _NumericScalar The type of the scalar value to multiply by.
         * @param val The scalar value to multiply by.
         * @return A reference to this matrix after the multiplication.
         */
        template <typename _NumericScalar>
        constexpr Matrix& operator*=(const _NumericScalar& val) {
            static_assert(std::is_arithmetic<_NumericScalar>::value, "Can only do scalar multiplication with a numeric type!");

            for (size_t i = 0; i < _RowCount; ++i) {
                for (size_t j = 0; j < _ColCount; ++j) {
                    this->data_[i][j] *= val;
                }
            }

            return *this;
        }

        /**
         * Multiply two matrices together.
         *
         * @tparam T The type of the elements in both matrices
         * @tparam M The number of rows in the left-hand matrix.
         * @tparam N The number of columns in the left-hand matrix and the number of rows in the right-hand matrix.
         * @tparam _OtherRowCount The number of rows in the right-hand matrix.
         * @tparam _OtherColCount The number of columns in the right-hand matrix.
         * 
         * @param lhs The left-hand matrix.
         * @param rhs The right-hand matrix.
         * 
         * @pre The number of columns in the left matrix must be equal to the number of rows in the right matrix.
         * @post The resulting matrix has the same number of rows as the left matrix and the same number of columns as the right matrix.
         * 
         * @return The matrix resulting from the multiplication.
         */
        template <typename T, size_t M, size_t N, size_t _OtherRowCount, size_t _OtherColCount>
        constexpr friend Matrix<T, M, _OtherColCount> operator*(const Matrix<T, M, N>& lhs, const Matrix<T, _OtherRowCount, _OtherColCount>& rhs);

        /**
         * @brief Overload of the stream output operator for the Matrix class.
         * 
         * @tparam _Scalar The scalar type of the matrix.
         * @tparam _RowCount The number of rows in the matrix.
         * @tparam _ColCount The number of columns in the matrix.
         * @param os The output stream to write to.
         * @param toPrint The matrix to write to the stream.
         * @return std::ostream& The output stream after the matrix has been written.
         *
         * This function overloads the stream output operator to allow easy printing of
         * Matrix objects. The matrix is printed in row-major order, with each row printed
         * on a separate line.
         */
        template <typename T, size_t M, size_t N>
        constexpr friend std::ostream& operator<<(std::ostream& os, Matrix<T, M, N> const &toPrint);

        /**
         * @brief Converts the matrix to a string representation.
         * 
         * @tparam _Scalar The scalar type of the matrix.
         * @tparam _RowCount The number of rows in the matrix.
         * @tparam _ColCount The number of columns in the matrix.
         * @param toPrint The matrix to convert to a string.
         * @return std::string A string representation of the matrix.
         *
         * This function converts the matrix to a string representation that can be used
         * for logging or other purposes. The matrix is printed in row-major order, with
         * each row separated by a newline character.
         */
        template <typename T, size_t M, size_t N>
        constexpr friend std::string to_string(const Matrix<T, M, N>& toPrint);
    };

    /**
     * @brief Returns the result of adding two matrices element-wise.
     *
     * This function returns a new matrix which is the result of adding
     * each element of the left-hand side matrix with the corresponding
     * element of the right-hand side matrix.
     *
     * @tparam _Scalar The scalar type of the matrix elements.
     * @tparam _RowCount The number of rows in the matrix.
     * @tparam _ColCount The number of columns in the matrix.
     * @param lhs The left-hand side matrix.
     * @param rhs The right-hand side matrix.
     * @return The result of adding the two matrices element-wise.
     */
    template <typename _Scalar, size_t _RowCount, size_t _ColCount>
    constexpr Matrix<_Scalar, _RowCount, _ColCount> operator+(const Matrix<_Scalar, _RowCount, _ColCount>& lhs, const Matrix<_Scalar, _RowCount, _ColCount>& rhs) {
        return Matrix<_Scalar, _RowCount, _ColCount>{lhs} += rhs;
    }

    /**
     * @brief Returns the result of subtracting two matrices element-wise.
     *
     * This function returns a new matrix which is the result of subtracting
     * each element of the right-hand side matrix from the corresponding
     * element of the left-hand side matrix.
     *
     * @tparam _Scalar The scalar type of the matrix elements.
     * @tparam _RowCount The number of rows in the matrix.
     * @tparam _ColCount The number of columns in the matrix.
     * @param lhs The left-hand side matrix.
     * @param rhs The right-hand side matrix.
     * @return The result of subtracting the two matrices element-wise.
     */
    template <typename _Scalar, size_t _RowCount, size_t _ColCount>
    constexpr Matrix<_Scalar, _RowCount, _ColCount> operator-(const Matrix<_Scalar, _RowCount, _ColCount>& lhs, const Matrix<_Scalar, _RowCount, _ColCount>& rhs) {
        return Matrix<_Scalar, _RowCount, _ColCount>{lhs} -= rhs;
    }

    template <typename T, size_t M, size_t N, size_t _OtherRowCount, size_t _OtherColCount>
    constexpr Matrix<T, M, _OtherColCount> operator*(const Matrix<T, M, N>& lhs, const Matrix<T, _OtherRowCount, _OtherColCount>& rhs) {
        static_assert(N == _OtherRowCount, "Matrix multiplication is only supported if second matrix's row count == first matrix's column count");

        Matrix<T, M, _OtherColCount> ret;

        for (size_t i = 0; i < M; ++i) {
            std::fill(ret.data_[i].begin(), ret.data_[i].end(), 0);
        }

        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < _OtherColCount; ++j) {
                for (size_t k = 0; k < N; ++k) {
                    ret.data_[i][j] += lhs.data_[i][k] * rhs.data_[k][j];
                }
            }
        }

        return ret;
    }

    template <typename _Scalar, size_t _RowCount, size_t _ColCount>
    constexpr std::string to_string(const Matrix<_Scalar, _RowCount, _ColCount>& toPrint) {
        std::stringstream ss;

        for (size_t i = 0; i < _RowCount; ++i) {
            ss << "| ";
            for (size_t j = 0; j < _ColCount - 1; ++j) {
                ss << toPrint.data_[i][j] << ", ";
            }

            ss << toPrint.data_[i][_ColCount - 1] << " |\n";
        }

        return ss.str();
    }

    template <typename _Scalar, size_t _RowCount, size_t _ColCount>
    constexpr std::ostream& operator<<(std::ostream& os, const Matrix<_Scalar, _RowCount, _ColCount>& toPrint) {
        for (size_t i = 0; i < _RowCount; ++i) {
            os << "| ";
            for (size_t j = 0; j < _ColCount - 1; ++j) {
                os << toPrint.data_[i][j] << ", ";
            }

            os << toPrint.data_[i][_ColCount - 1] << " |\n";
        }

        return os;
    }

} /* Matrix */


#endif /* MATRIXLIB_H */