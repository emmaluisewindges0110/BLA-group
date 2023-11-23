#ifndef FILE_MATRIX_H
#define FILE_MATRIX_H

#include <iostream>

#include "vector.h"

namespace pep::bla {
    enum class ORDERING { ColMajor, RowMajor };

    template <typename T, ORDERING ORD>
    class MatrixView : public MatrixExpr<MatrixView<T, ORD>> {
    protected:
        T* data_;
        size_t rows_, cols_, dist_;

    public:
        MatrixView (size_t rows, size_t cols, size_t dist, T * data) : data_(data), rows_(rows), cols_(cols), dist_(dist) {}

        template <typename TB>
        MatrixView& operator= (const MatrixExpr<TB>& v2) {
            for (size_t i = 0; i < rows_; i++) {
                for (size_t j = 0; j < cols_; ++j) {
                    (*this)(i, j) = v2(i, j);
                }
            }
            return *this;
        }

        MatrixView& operator= (T scal) {
            for (size_t i = 0; i < rows_; i++) {
                for (size_t j = 0; j < cols_; ++j) {
                    (*this)(i, j) = scal;
                }
            }
            return *this;
        }

        auto View() const {
            return MatrixView(rows_, cols_, dist_, data_);
        }

        size_t Rows() const {
            return rows_;
        }

        size_t Cols() const {
            return cols_;
        }

        auto Dist() const {
            return dist_;
        }

        auto Data() {
            return data_;
        }

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
                return VectorView<T,size_t> (cols_, dist_, data_ + row);
            } else {
                return VectorView<T> (cols_, data_ + row * dist_);
            }
        }

        auto Col(size_t col) const {
            if constexpr (ORD == ORDERING::ColMajor) {
                return VectorView<T> (rows_, data_ + col * dist_);
            } else {
                return VectorView<T,size_t> (rows_, dist_, data_ + col);
            }
        }

        auto Rows(size_t first, size_t next) {
            size_t n_rows = next - first;

            if constexpr (ORD == ORDERING::ColMajor) {
                return MatrixView<T, ORD> (n_rows, cols_, dist_, data_ + first);
            } else {
                return MatrixView<T, ORD> (n_rows, cols_, dist_, data_ + first * dist_);
            }
        }

        auto Cols(size_t first, size_t next) {
            size_t n_cols = next - first;

            if constexpr (ORD == ORDERING::ColMajor) {
                return MatrixView<T, ORD> (rows_, n_cols, dist_, data_ + first * dist_);
            } else {
                return MatrixView<T, ORD> (rows_, n_cols, dist_, data_ + first);
            }
        }

        auto Transpose() {
            if constexpr (ORD == ORDERING::ColMajor) {
                return MatrixView<T, ORDERING::RowMajor>(cols_, rows_, dist_, data_);
            } else {
                return MatrixView<T, ORDERING::ColMajor>(cols_, rows_, dist_, data_);
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
        Matrix(size_t rows, size_t cols) : MatrixView<T, ORD>(rows, cols, (ORD == pep::bla::ORDERING::ColMajor) ? rows : cols, new T[rows * cols]) {}

        // Copy constructor
        Matrix(const Matrix& other) : Matrix(other.rows_, other.cols_) {
            *this = other;
        }

        // Move constructor
        Matrix(Matrix&& other) noexcept : MatrixView<T, ORD>(other.rows_, other.cols_, other.dist_, nullptr) {
            std::swap(data_, other.data_);
            std::swap(rows_, other.rows_);
            std::swap(cols_, other.cols_);
        }

        template <typename TB>
        Matrix(const MatrixExpr<TB>& M) : Matrix(M.Rows(), M.Cols()) {
            *this = M;
        }

        // Destructor
        ~Matrix() {
            delete [] data_;
        }

        // Assignment operator
        using BASE::operator=;
        Matrix& operator=(const Matrix& other) {
            for (size_t row = 0; row < other.Rows(); ++row) {
                for (size_t col = 0; col < other.Cols(); ++col) {
                    (*this)(row, col) = other(row, col);
                }
            }
            return *this;
        }

        // Assignment operator
        Matrix& operator=(Matrix&& other) {
            for (size_t row = 0; row < other.Rows(); ++row) {
                for (size_t col = 0; col < other.Cols(); ++col) {
                    (*this)(row, col) = other(row, col);
                }
            }
            return *this;
        }
    };
}
#endif