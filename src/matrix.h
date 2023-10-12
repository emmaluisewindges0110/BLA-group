#ifndef FILE_MATRIX_H
#define FILE_MATRIX_H

#include <iostream>

#include "vector.h" // Assuming your Vector class is in "vector.h"

namespace ASC_bla {
    enum class ORDERING { ColMajor, RowMajor };

    template <typename T, ORDERING ORD>
    class MatrixView : public MatrixExpr<MatrixView<T, ORD>>
    {
        protected:
        T* data_;
        size_t rows_, cols_, dist_;

        public:
        MatrixView (size_t rows, size_t cols, size_t dist, T * data) : data_(data), rows_(rows), cols_(cols), dist_(dist) {}
        
        template <typename TB>
        MatrixView& operator= (const MatrixExpr<TB>& v2)
        {
            for (size_t i = 0; i < rows_; i++) {
                for (size_t j = 0; j < cols_; ++j) {
                    (*this)(i, j) = v2(i, j);
                }
            }
            return *this;
        }

        MatrixView& operator= (T scal)
        {
            for (size_t i = 0; i < rows_; i++) {
                for (size_t j = 0; j < cols_; ++j) {
                    (*this)(i, j) = scal;
                }
            }
            return *this;
        }
    
        auto View() const { return MatrixView(rows_, cols_, dist_, data_); }
        size_t Rows() const { return rows_; }
        size_t Cols() const { return cols_; }

        T& operator()(size_t i, size_t j) {
            if constexpr (ORD == ORDERING::ColMajor) {
                return data_[i + j * dist_];
            } else {
                return data_[j + i * dist_];
            }
        }

        // Const version of the access operator
        const T& operator()(size_t i, size_t j) const {
            if constexpr (ORD == ORDERING::ColMajor) {
                return data_[i + j * dist_];
            } else {
                return data_[j + i * dist_];
            }
        }

        auto Row(size_t row) const {
            if constexpr (ORD == ORDERING::ColMajor) {
                return VectorView<T,size_t> (cols_, cols_, data_ + row);
            } else {
                return VectorView<T,size_t> (cols_, 1, data_ + row * cols_);
            }
        }

        auto Col(size_t col) const {
            if constexpr (ORD == ORDERING::ColMajor) {
                return VectorView<T,size_t> (rows_, 1, data_ + col * rows_);
            } else {
                return VectorView<T,size_t> (rows_, rows_, data_ + col);
            }
        }
    };

    template <typename T, ORDERING ORD>
    class Matrix : public MatrixView<T, ORD> {
        typedef MatrixView<T, ORD> BASE;
        using BASE::rows_;
        using BASE::cols_;
        using BASE::data_;
    public:
        // Constructors
        Matrix(size_t rows, size_t cols) : MatrixView<T, ORD>(rows, cols, (ORD == ASC_bla::ORDERING::ColMajor) ? rows : cols, new T[rows * cols]) {}

        // Copy constructor
        Matrix(const Matrix& other) : MatrixView<T, ORD>(other.rows_, other.cols_, other.dist_, other.data_) {}

        // Move constructor
        Matrix(Matrix&& other) noexcept :  MatrixView<T, ORD>(other.rows_, other.cols_, other.dist_, std::move(other.data_)) {}

        // Destructor
        ~Matrix() = default;

        // // Access operator for element (i, j)
        // T& operator()(size_t i, size_t j) {
        //     if constexpr (ORD == ORDERING::ColMajor) {
        //         return data_[i + j * rows_];
        //     } else {
        //         return data_[j + i * cols_];
        //     }
        // }

        // // Const version of the access operator
        // const T& operator()(size_t i, size_t j) const {
        //     if constexpr (ORD == ORDERING::ColMajor) {
        //         return data_[i + j * rows_];
        //     } else {
        //         return data_[j + i * cols_];
        //     }
        // }


        // Assignment operator
        Matrix& operator=(const Matrix& other) {
            if (this != &other) {
                rows_ = other.rows_;
                cols_ = other.cols_;
                data_ = other.data_;
            }
            return *this;
        }

        // // Output stream operator for easy printing
        // friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        //     for (size_t i = 0; i < matrix.rows_; ++i) {
        //         if (i > 0) {
        //             os << "\n";
        //         }
        //         for (size_t j = 0; j < matrix.cols_; ++j) {
        //             if (j > 0) {
        //                 os << " ";
        //             }
        //             os << matrix(i, j);
        //         }
        //     }
        //     return os;
        // }

//         // Matrix-Matrix Multiplication
// Matrix operator*(const Matrix& other) const {
//     if (cols_ != other.rows_) {
//         // Invalid multiplication, return an empty matrix or throw an exception
//         return Matrix(0, 0);
//     }

//     Matrix result(rows_, other.cols_);

//     for (size_t i = 0; i < rows_; ++i) {
//         for (size_t j = 0; j < other.cols_; ++j) {
//             T sum = 0;
//             for (size_t k = 0; k < cols_; ++k) {
//                 if constexpr (ORD == ORDERING::ColMajor) {
//                     sum += (*this)(i, k) * other(k, j);
//                 } else {
//                     sum += (*this)(i, k) * other(k, j);
//                 }
//             }
//             result(i, j) = sum;
//         }
//     }
//     return result;
// }
// Transpose method
        // Matrix<T, ORD> transpose() const {
        //     Matrix<T, ORD> result(cols_, rows_);
        //     for (size_t i = 0; i < rows_; ++i) {
        //         for (size_t j = 0; j < cols_; ++j) {
        //             result(j, i) = (*this)(i, j);
        //         }
        //     }
        //     return result;
        // }
        // // Matrix-Vector Multiplication
        // Vector<T> operator*(const Vector<T>& vector) const {
        //     if constexpr (ORD == ORDERING::ColMajor) {
        //         if (cols_ != vector.Size()) {
        //             // Invalid multiplication, return an empty vector or throw an exception
        //             return Vector<T>(0);
        //         }

        //         Vector<T> result(rows_);
        //         for (size_t i = 0; i < rows_; ++i) {
        //             T sum = 0;
        //             for (size_t j = 0; j < cols_; ++j) {
        //                 sum += (*this)(i, j) * vector(j);
        //             }
        //             result(i) = sum;
        //         }
        //         return result;
        //     } else {
        //         if (rows_ != vector.Size()) {
        //             // Invalid multiplication, return an empty vector or throw an exception
        //             return Vector<T>(0);
        //         }

        //         Vector<T> result(cols_);
        //         for (size_t j = 0; j < cols_; ++j) {
        //             T sum = 0;
        //             for (size_t i = 0; i < rows_; ++i) {
        //                 sum += (*this)(i, j) * vector(i);
        //             }
        //             result(j) = sum;
        //         }
        //         return result;
        //     }
        // }
    };
}
#endif