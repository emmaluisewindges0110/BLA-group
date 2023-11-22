#include <iostream>
#include <vector.h>
#include <matrix.h>

#include <simd.h>

namespace bla = pep::bla;


int main() {
    // Creating Matrix examples
    bla::Matrix<double, bla::ORDERING::ColMajor> Matrix1(5, 5);
    bla::Matrix<double, bla::ORDERING::ColMajor> Matrix2(5, 5);

    // Initialize the ColMajor matrix with some values
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (i==j) { Matrix1(i, j) = i;}
            else { Matrix1(i, j) = 0;}
            Matrix2(i, j) = i+j;
            // Matrix2(i, j) = i + j * 5;
        }
    }

    // Testing Matrix initialization and printing
    std::cout << "Matrix1: \n" << Matrix1 << std::endl;
    std::cout << "Matrix2: \n" << Matrix2 << std::endl;

    std::cout << "Sum: \n" << (Matrix1 + Matrix2) << std::endl;
    std::cout << "mm-Mult: \n" << (Matrix1 * Matrix2) << std::endl;
    std::cout << "Matrix2 Zeile 3 " << std::endl << Matrix2.Row(3) << std::endl;
    std::cout << "Matrix2 Spalte 2 " << std::endl << Matrix2.Col(2) << std::endl;

    std::cout << "Produkt: \n" << (Matrix1 * Matrix2) << std::endl;

    bla::Vector<double> v(5);
    v(0) = 1;
    v(1) = 2;
    v(2) = 3;
    v(3) = 4;
    v(4) = 5;

    std::cout << "MV Produkt: \n" << (Matrix2 * v) << std::endl;

    // // Testing RowMajor Matices
    // bla::Matrix<double, bla::ORDERING::RowMajor> Matrix4(5, 5);
    // for (int i = 0; i < 5; ++i) {
    //     for (int j = 0; j < 5; ++j) {
    //         Matrix4(i,j) = i+j;
    //     }
    // }
    // std::cout << "Matrix 4 (RowMajor):\n" << Matrix4 << std::endl;

    // // Testing difference between ColMajor and RowMajor
    // std::cout << "Matrix 2 (ColMajor):\n" << Matrix2 << std::endl;

    std::cout << std::endl;
    std::cout << "Matrix2:" << std::endl;
    std::cout << Matrix2 << std::endl;
    std::cout << "Matrix2.Rows(2, 4):" << std::endl;
    auto test = Matrix2.Rows(2, 4);
    std::cout << test << std::endl;
    std::cout << "Matrix2.Rows(2, 4).Cols(2, 5):" << std::endl;
    auto test2 = test.Cols(2, 5);
    std::cout << test2 << std::endl;

    std::cout << "Matrix2.Rows(2, 4).Cols(2, 5).Col(1)" << std::endl;
    std::cout << test2.Col(1) << std::endl;

    std::cout << "Matrix2.Rows(2, 4).Cols(2, 5).Transpose()" << std::endl;
    std::cout << test2.Transpose() << std::endl;
}