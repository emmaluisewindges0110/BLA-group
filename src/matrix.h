#ifndef FILE_MATRIX_H
#define FILE_MATRIX_H
#include <vector>
#include <iostream>

namespace ASC_bla
{
enum ORDERING { ColMajor, RowMajor };

template <typename T, ORDERING ORD>
class Matrix
  {
   private:
    std::vector<T> data;
    int rows, cols;

public:
    // Constructor
    Matrix(int numRows, int numCols) : rows(numRows), cols(numCols) {
        data.resize(rows * cols);
    }

    // Destructor
    ~Matrix() {}

    // Method for matrix multiplication
    Matrix<T, ORD> multiply(const Matrix<T, ORD>& other) const {
        if (cols != other.rows) {
            std::cerr << "Matrix dimensions are not compatible for multiplication." << std::endl;
            exit(1);
        }

        int resultRows = rows;
        int resultCols = other.cols;
        Matrix<T, ORD> result(resultRows, resultCols);

        if (ORD == ColMajor) {
            for (int i = 0; i < resultRows; ++i) {
                for (int j = 0; j < resultCols; ++j) {
                    T sum = 0;
                    for (int k = 0; k < cols; ++k) {
                        sum += data[i * cols + k] * other.data[k * other.cols + j];
                    }
                    result.data[i * resultCols + j] = sum;
                }
            }
        } else if (ORD == RowMajor) {
            for (int i = 0; i < resultRows; ++i) {
                for (int j = 0; j < resultCols; ++j) {
                    T sum = 0;
                    for (int k = 0; k < cols; ++k) {
                        sum += data[i * cols + k] * other.data[j * other.cols + k];
                    }
                    result.data[i * resultCols + j] = sum;
                }
            }
        }

        return result;
    }
};
}
#endif
