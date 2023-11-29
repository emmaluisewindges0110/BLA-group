#ifndef FILE_MATRIX_H
#define FILE_MATRIX_H

#include <iostream>
#include <simd.h>

#include "vector.h"

namespace pep::bla {
    enum ORDERING {
        ColMajor,
        RowMajor
    };

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
        Matrix(const Matrix& other) : MatrixView<T, ORD>(other.rows_, other.cols_, other.dist_, other.data_) {}

        // Move constructor
        Matrix(Matrix&& other) noexcept : MatrixView<T, ORD>(other.rows_, other.cols_, other.dist_, std::move(other.data_)) {}

        template <typename TB>
        Matrix(const MatrixExpr<TB>& M) : Matrix(M.Rows(), M.Cols()) {
            // *this = M;
            for (size_t row = 0; row < M.Rows(); ++row) {
                for (size_t col = 0; col < M.Cols(); ++col) {
                    (*this)(row, col) = M(row, col);
                }
            }
        }

        // Destructor
        ~Matrix() { delete [] data_; }

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

    // AddMatMatKernel<H,W> (A.Width(), &A(i,0), A.Dist(), &B(0,j), B.dist(), &C(i,j), C.Dist());
    template<size_t H, size_t W, bool INIT>
    inline void AddMatMatKernel(size_t A_width, double *A, size_t A_dist, double *B, size_t B_dist, double *C, size_t C_dist) {
        if constexpr (H != 0 || W != 0) {
            return;
        }

        // Initialize SIMD objects.
        hpc::SIMD<double, W> sum[H];
        for (size_t j = 0; j < H; ++j) {
            if constexpr (INIT) {
                sum[j] = hpc::SIMD<double, W>(0.0);
            } else {
                sum[j] = hpc::SIMD<double, W>(C + j * C_dist);
            }
        }

        // Calculate multiple vector-vector products.
        for (size_t i = 0; i < A_width; ++i) {
            hpc::SIMD<double, W> y(B + i * B_dist);

            for (size_t j = 0; j < H; ++j) {
                sum[j] = hpc::FMA(hpc::SIMD<double, W>(A + i * A_dist + j), y, sum[j]);
            }
        }

        // Store results in C.
        for (size_t j = 0; j < H; ++j) {
            sum[j].Store(C + j * C_dist);
        }
    }

    template<size_t H, size_t W, bool INIT>
    void AddMatMat2 (MatrixView<double, ColMajor> A, MatrixView<double, RowMajor> B, MatrixView<double, RowMajor> C) {
        // constexpr size_t H=4;
        // constexpr size_t W=12;

        for (size_t j = 0; j+W <= C.Cols(); j += W)
            for (size_t i = 0; i+H <= C.Rows(); i += H)
                AddMatMatKernel<H, W, INIT>(A.Cols(), &A(i,0), A.Dist(), &B(0,j), B.Dist(), &C(i,j), C.Dist());
        // leftover rows and cols
    }

    void AddMatMat (MatrixView<double, RowMajor> A, MatrixView<double, RowMajor> B, MatrixView<double, RowMajor> C) {
        constexpr size_t BH=96;
        constexpr size_t BW=96;
        alignas (64) double memBA[BH*BW];
        for (size_t i1 = 0; i1+BH <= A.Rows(); i1 += BH)
            for (size_t j1 = 0; j1+BW <= A.Rows(); j1 += BW) {
            size_t i2 = std::min(A.Rows(), i1+BH);
            size_t j2 = std::min(A.Cols(), j1+BW);

            MatrixView<double, ColMajor> Ablock(i2-i1, j2-j1, BW, memBA);
            Ablock = A.Rows(i1,i2).Cols(j1,j2);
            AddMatMat2<4, 12, true>(Ablock, B.Rows(j1,j2), C.Rows(i1,i2));
        }
    }


}
#endif