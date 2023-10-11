#include <iostream>
#include <vector.h>
#include <matrix.h>

namespace bla = ASC_bla;


int main()
{

  //creating Vektor examples
  size_t n = 5;
  bla::Vector<double> x(n), y(n);

  for (size_t i = 0; i < x.Size(); i++)
    {
      x(i) = i;
      y(i) = 10;
    }
//demonstrating Vektor Operations
  bla::Vector<double> z = x+y;
  
  std::cout << "x+y = " << z << std::endl;

  //creating Matrix examples
  bla::Matrix<double, bla::ORDERING::ColMajor> Matrix1(5, 5);
  bla::Matrix<double, bla::ORDERING::ColMajor> Matrix2(5, 5);
  // Initialize the matrix with some values
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (i==j) { Matrix1(i, j) = i;}
            else { Matrix1(i, j) = 0;}
            Matrix2(i,j) = i+j;
        }
    }
  //testing Matrix initialization and printing
    std::cout << "Matrix1: \n" << Matrix1 << std::endl;
    std::cout << "Matrix2: \n" << Matrix2 << std::endl;

    //testing Matrix-Matrix multiplication
    bla::Matrix<double, bla::ORDERING::ColMajor> Matrix3 = Matrix1 * Matrix2;
    std::cout << "Matrix3: \n" << Matrix3 << std::endl;
    //testing transpose
    std::cout << "transposed Matrix3: \n" << Matrix3.transpose() << std::endl;
    //testing Matrix-Vector multiplication
    std::cout << "A*z = " << Matrix1 * z << std::endl;
    //Praying it will work...


}