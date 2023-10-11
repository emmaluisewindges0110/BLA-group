#ifndef FILE_MATRIX_H
#define FILE_MATRIX_H

#include <iostream>
#include "vector.h" // Include your custom vector class header here

namespace ASC_bla
{
    enum class Ordering {
        ColMajor,
        RowMajor
    };

    template <typename T, Ordering ORD = Ordering::ColMajor>
class Matrix {
public:
    // Custom constructor that initializes the matrix with the given size
    Matrix(int rows, int cols) : rows_(rows), cols_(cols), data_(cols) {
        for (int i = 0; i < cols; ++i) {
            data_(i) = ASC_bla::Vector<T>(rows);
        }
    }

// Copy constructor
        Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_), data_(other.data_) {}

        // Move constructor
        Matrix(Matrix&& other) noexcept : rows_(other.rows_), cols_(other.cols_), data_(std::move(other.data_)) {
            other.rows_ = 0;
            other.cols_ = 0;
        }

        // Destructor
        ~Matrix() {}

        // Accessor to get a specific element of the matrix
        T& operator()(int row, int col) {
            if (ORD == Ordering::ColMajor) {
                return data_[col](row);
            } else {
                return data_[row](col);
            }
        }

        // Const accessor to get a specific element of the matrix
        const T& operator()(int row, int col) const {
            if (ORD == Ordering::ColMajor) {
                return data_[col](row);
            } else {
                return data_[row](col);
            }
        }

        // Get the number of rows in the matrix
        int rows() const {
            return rows_;
        }

        // Get the number of columns in the matrix
        int cols() const {
            return cols_;
        }

        // Matrix-vector product method
        ASC_bla::Vector<T> operator*(const ASC_bla::Vector<T>& vec) const {
             if (ORD == Ordering::ColMajor) {
                if (vec.size() != cols_) {
                    throw std::invalid_argument("Vector size must match matrix column count.");
                }

                ASC_bla::Vector<T> result(rows_, 0);

                for (int i = 0; i < rows_; ++i) {
                    for (int j = 0; j < cols_; ++j) {
                        result(i) += data_[i](j) * vec(j);
                    }
                }

                return result;
            }  else {
                if (vec.size() != rows_) {
                    throw std::invalid_argument("Vector size must match matrix row count.");
                }

                ASC_bla::Vector<T> result(cols_, 0);

                for (int i = 0; i < cols_; ++i) {
                    for (int j = 0; j < rows_; ++j) {
                        result(i) += data_[j](i) * vec(j);
                    }
                }

                return result;
            }
        }

private:
    int rows_;
    int cols_;
    ASC_bla::Vector<ASC_bla::Vector<T>> data_;

        

  
};
}

#endif