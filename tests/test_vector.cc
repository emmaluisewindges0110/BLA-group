#include <iostream>
//#include <matrix.h>
#include <vector.h>
#include <matrix2.h>

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

ASC_bla::Matrix<int> matrix(2,2);


//  //creating Matrix examples
//    bla::Matrix<double, bla::RowMajor> A(2, 2);
//  for (size_t i = 0; i < 2; ++i) {
//          for (size_t j = 0; j < 2; ++j) {
//              A(i, j) = i + j;
//          }
//      }
//      bla::Matrix<double, bla::RowMajor> B(2, 2);
//  for (size_t i = 0; i < 2; ++i) {
//          for (size_t j = 0; j < 2; ++j) {
//              B(i, j) = i;
//          }
//          }
//      // Perform matrix multiplication
//      bla::Matrix<double, bla::RowMajor> result = A * B;
//      // Output the result
//      std::cout << "Result of matrix multiplication:\n";
//      for (size_t i = 0; i < 2; ++i) {
//          for (size_t j = 0; j < 2; ++j) {
//              std::cout << result(i, j) << " ";
//          }
//          std::cout << "\n";
//      }
//      //testing transpose
//  bla::Matrix<double, bla::RowMajor> T = bla::Transpose(result);
//  std::cout << "Transposed result::\n";
//      for (size_t i = 0; i < 2; ++i) {
//          for (size_t j = 0; j < 2; ++j) {
//              std::cout << T(i, j) << " ";
//          }
//          std::cout << "\n";
 }
 //}
