#ifndef FILE_MATRIX_H
#define FILE_MATRIX_H

#include <iostream>
#include <vector.h>

namespace ASC_bla
{
enum ORDERING { ColMajor, RowMajor };

template <typename R, ORDERING ORD>
class Matrix
{
    size_t rows_;
    size_t columns_;
    R **data_;

public:
    // Constructor to create a matrix with specified rows and columns
    Matrix(size_t rows, size_t columns)
        : rows_(rows), columns_(columns)
    {
        data_ = new R *[rows_];
        for (size_t i = 0; i < rows_; ++i)
        {
            data_[i] = new R[columns_];
        }
    }

    // Copy constructor
    Matrix(const Matrix &other)
        : Matrix(other.rows_, other.columns_)
    {
        for (size_t i = 0; i < rows_; ++i)
        {
            for (size_t j = 0; j < columns_; ++j)
            {
                if (ORD == ColMajor)
                {
                    data_[i][j] = other.data_[i][j];
                }
                else
                {
                    data_[i][j] = other.data_[j][i];
                }
            }
        }
    }

    // Move constructor
    Matrix(Matrix &&other)
        : rows_{0}, columns_{0}, data_(nullptr)
    {
        std::swap(rows_, other.rows_);
        std::swap(columns_, other.columns_);
        std::swap(data_, other.data_);
    }

    // Destructor
    ~Matrix()
    {
        for (size_t i = 0; i < rows_; ++i)
        {
            delete[] data_[i];
        }
        delete[] data_;
    }
    // Overload () operator to access elements of the matrix
R& operator() (size_t row, size_t col)
{
    if (ORD == ColMajor)
    {
        return data_[row][col];
    }
    else // ORD == RowMajor
    {
        return data_[col][row];
    }
}

// Overload () operator for const access to elements
const R& operator() (size_t row, size_t col) const
{
    if (ORD == ColMajor)
    {
        return data_[row][col];
    }
    else // ORD == RowMajor
    {
        return data_[col][row];
    }
}

// Overload = operator for assignment
Matrix<R, ORD>& operator= (const Matrix<R, ORD>& other)
{
    if (this != &other)
    {
        // Deallocate existing data if any
        for (size_t i = 0; i < rows_; ++i)
        {
            delete[] data_[i];
        }
        delete[] data_;

        // Copy dimensions
        rows_ = other.rows_;
        columns_ = other.columns_;

        // Allocate new data
        data_ = new R *[rows_];
        for (size_t i = 0; i < rows_; ++i)
        {
            data_[i] = new R[columns_];
        }

        // Copy data
        for (size_t i = 0; i < rows_; ++i)
        {
            for (size_t j = 0; j < columns_; ++j)
            {
                (*this)(i, j) = other(i, j);
            }
        }
    }
    return *this;
}
// Member function to get the number of rows
size_t NumRows() const {
    return rows_;
}

// Member function to get the number of columns
size_t NumColumns() const {
    return columns_;
}
};


// Matrix-Matrix Multiplication
template <typename T, ORDERING ORD>
Matrix<T, ORD> MatrixMatrixMultiply(const Matrix<T, ORD> &mat1, const Matrix<T, ORD> &mat2)
{
    if (mat1.NumColumns() != mat2.NumRows())
    {
        throw std::invalid_argument("Matrix dimensions are not compatible for multiplication.");
    }

    size_t numRows = mat1.NumRows();
    size_t numCols = mat2.NumColumns();
    size_t commonDim = mat1.NumColumns();

    Matrix<T, ORD> result(numRows, numCols);

    if (ORD == ColMajor)
    {
        for (size_t i = 0; i < numRows; ++i)
        {
            for (size_t j = 0; j < numCols; ++j)
            {
                T sum = 0;
                for (size_t k = 0; k < commonDim; ++k)
                {
                    sum += mat1(i, k) * mat2(k, j);
                }
                result(i, j) = sum;
            }
        }
    }
    else // ORD == RowMajor
    {
        for (size_t i = 0; i < numRows; ++i)
        {
            for (size_t j = 0; j < numCols; ++j)
            {
                T sum = 0;
                for (size_t k = 0; k < commonDim; ++k)
                {
                    sum += mat1(i, k) * mat2(k, j);
                }
                result(i, j) = sum;
            }
        }
    }

    return result;
}

// Vector-Matrix Multiplication
template <typename R, ORDERING ORD>
Matrix<R, ORD> VectorMatrixMultiply(const Vector<R> &vec, const Matrix<R, ORD> &mat)
{
    if (ORD == ColMajor)
    {
        if (vec.size() != mat.NumRows())
        {
            throw std::invalid_argument("Vector size must match matrix number of rows for multiplication.");
        }

        size_t numCols = mat.NumColumns();
        Matrix<R, ORD> result(1, numCols);

        for (size_t j = 0; j < numCols; ++j)
        {
            R sum = 0;
            for (size_t i = 0; i < vec.size(); ++i)
            {
                sum += vec[i] * mat(i, j);
            }
            result(0, j) = sum;
        }

        return result;
    }
    else // ORD == RowMajor
    {
        if (vec.size() != mat.NumColumns())
        {
            throw std::invalid_argument("Vector size must match matrix number of columns for multiplication.");
        }

        size_t numRows = mat.NumRows();
        Matrix<R, ORD> result(numRows, 1);

        for (size_t i = 0; i < numRows; ++i)
        {
            R sum = 0;
            for (size_t j = 0; j < vec.size(); ++j)
            {
                sum += mat(i, j) * vec[j];
            }
            result(i, 0) = sum;
        }

        return result;
    }
}

// Transposition of Matrix
template <typename R, ORDERING ORD>
Matrix<R, ORD> Transpose(const Matrix<R, ORD> &mat)
{
    size_t numRows = mat.NumRows();
    size_t numCols = mat.NumColumns();

    Matrix<R, ORD> result(numCols, numRows);

    for (size_t i = 0; i < numRows; ++i)
    {
        for (size_t j = 0; j < numCols; ++j)
        {
            if (ORD == ColMajor)
            {
                result(j, i) = mat(i, j);
            }
            else // ORD == RowMajor
            {
                result(j, i) = mat(i, j);
            }
        }
    }

    return result;
}

// Overload * operator for Vector-Matrix Multiplication
template <typename R, ORDERING ORD>
Matrix<R, ORD> operator* (const Vector<R> &vec, const Matrix<R, ORD> &mat)
{
    return VectorMatrixMultiply(vec, mat);
}

// Overload * operator for Matrix-Matrix Multiplication
template <typename R, ORDERING ORD>
Matrix<R, ORD> operator* (const Matrix<R, ORD> &mat1, const Matrix<R, ORD> &mat2)
{
    return MatrixMatrixMultiply(mat1, mat2);
}

};
#endif