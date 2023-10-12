#include <iostream>
#include <vector.h>
#include <matrix.h>

namespace bla = ASC_bla;


int main()
{
//   size_t n = 10;
//   bla::Vector<double> x(n), y(n);

//   for (size_t i = 0; i < x.Size(); i++)
//     {
//       x(i) = i;
//       y(i) = 10;
//     }
// //demonstrating Vektor Operations
//   bla::Vector<double> z = x+y;
  
//   std::cout << "x+y = " << z << std::endl;
  
//   std::cout << "type of (x+3*y) is  " << typeid(x+3*y).name() << std::endl;

//   std::cout << "x+3*y = " << x+3*y << std::endl;

//   std::cout << "sizeof(x+3*y) = " << sizeof(x+3*y) << std::endl;
  
//   x.Range(2,9) = 3;
//   x.Slice(1,5) = 10;
  
//   std::cout << "x = " << x << std::endl;  

  //creating Matrix examples
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
  //testing Matrix initialization and printing
    std::cout << "Matrix1: \n" << Matrix1 << std::endl;
    std::cout << "Matrix2: \n" << Matrix2 << std::endl;

    std::cout << "Sum: \n" << (Matrix1 + Matrix2) << std::endl;

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

    
    // //testing RowMajor Matices
    // bla::Matrix<double, bla::ORDERING::RowMajor> Matrix4(5, 5);
    // for (int i = 0; i < 5; ++i) {
    //     for (int j = 0; j < 5; ++j) {
    //         Matrix4(i,j) = i+j;
    //     }
    // }
    // std::cout << "Matrix 4 (RowMajor):\n" << Matrix4 << std::endl;

    // //testing difference between ColMajor and RowMajor
    // std::cout << "Matrix 2 (ColMajor):\n" << Matrix2 << std::endl;
}