#include <iostream>
#include <matrix.h>
#include <vector.h>

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
  bla::Matrix<int, bla::ColMajor> A(5, 5), B(5, 5);
for (size_t i = 0; i < 5; ++i) {
        for (size_t j = 0; j < 5; ++j) {
            A(i, j) = i + j;
            B(i, j) = 1;
        }
    }
    // Perform matrix multiplication
    bla::Matrix<int, bla::ColMajor> result = A * B;
    // Output the result
    std::cout << "Result of matrix multiplication:\n";
    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = 0; j < 5; ++j) {
            std::cout << result(i, j) << " ";
        }
        std::cout << "\n";
    }
}
