#include <iostream>
#include <vector.h>
#include <matrix.h>

#include <simd.h>

namespace bla = pep::bla;


int main() {
    // Creating Matrix examples
    bla::Matrix<double, bla::ORDERING::ColMajor> Matrix1(5, 5);
    bla::Matrix<double, bla::ORDERING::ColMajor> Matrix2(5, 3);

    // Initialize the ColMajor matrix with some values
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            Matrix1(i, j) = i+j;
            // Matrix2(i, j) = i + j * 5;
        }
    }
    Matrix2 = 3.7;
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

    std::cout << "Matrix2.Rows(1, 3):" << std::endl;
    auto test = Matrix1.Rows(1, 3);
    std::cout << test << std::endl;
    std::cout << "Matrix2.Rows(1, 3).Cols(2, 4):" << std::endl;
    auto test2 = test.Cols(2, 4);
    std::cout << test2 << std::endl;

    std::cout << "Matrix2.Rows(1, 3).Cols(2, 4).Col(1)" << std::endl;
    std::cout << test2.Col(1) << std::endl;

    std::cout << "Matrix2.Rows(1, 3).Cols(2, 4).Transpose()" << std::endl;
    std::cout << test2.Transpose() << std::endl;

    {
        // Test Matrix-Vector product.
        std::cout << std::endl << "Matrix - Vector product" << std::endl;
        bla::Matrix<double, bla::ORDERING::ColMajor> A(3, 2);
        bla::Vector<double> x(2);
        A(0, 0) = 1;
        A(0, 1) = 0;
        A(1, 0) = 0;
        A(1, 1) = 2;
        A(2, 0) = 0.5;
        A(2, 1) = 0.5;
        x(0) = 3;
        x(1) = 5;
        std::cout << A*x << std::endl;
    }

    {
        // Test Matrix-Matrix product.
        std::cout << std::endl << "Matrix - Matrix product" << std::endl;
        bla::Matrix<double, bla::ORDERING::ColMajor> A(3, 2);
        bla::Matrix<double, bla::ORDERING::ColMajor> B(2, 2);
        A(0, 0) = 1;
        A(0, 1) = 0;
        A(1, 0) = 0;
        A(1, 1) = 2;
        A(2, 0) = 0.5;
        A(2, 1) = 0.5;
        B(0, 0) = 0;
        B(0, 1) = 1;
        B(1, 0) = 2;
        B(1, 1) = 0;
        std::cout << A << std::endl;
        std::cout << B << std::endl;
        std::cout << A*B << std::endl;
    }

    {
        bla::Vector<double> v { 0.0, 0.0 };
        bla::Vector<double> w { 0.5, 2.0 };

        bla::VectorView<double> x(v);
        x = w;
        std::cout << "v = " << v << std::endl;
        std::cout << "w = " << w << std::endl;
        std::cout << "x = " << x << std::endl;
    }

    {
        bla::Vec<3> v { 1.0, 1.5, -1.5 };
        std::cout << "v = " << v << std::endl;
    }
}