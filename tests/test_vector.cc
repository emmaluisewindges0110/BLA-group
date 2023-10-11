#include <iostream>
#include <vector.h>
#include <matrix3.h>

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
  bla::Matrix<double, bla::ORDERING::ColMajor> Matrix(5, 5);
  std::cout << "Matrix: " << Matrix << std::endl;
  
}