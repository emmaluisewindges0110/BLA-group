Usage
=====================================

To use bla-group in your code, set the compiler include path properly, and include the header files

..  code-block::

    #include <vector.h>
    #include <matrix.h>

All objects are implemented in the namespace pep::bla. To use them with less typing, you can set

..  code-block::

    namespace bla = pep::bla;

or even

..  code-block::

    using namespace pep::bla;



You can create vectors and compute with vectors like:

..  code-block:: cpp

   Vector<double> x(5), y(5), z(5);
   for (int i = 0; i < x.Size(); i++)
      x(i) = i;
   y = 5.0
   z = x+3*y;
   cout << "z = " << z << endl;


For matrices you can choose between row-major (`RowMajor`) or column-major (`ColMajor`) storage.
Default is row-major. You can add and multiply matrices as follows:

..  code-block:: cpp

   Matrix<double,RowMajor> m1(5,5), m2(5,3);
   for (int i = 0; i < m1.Height(); i++)
     for (int j = 0; j < m1.Width(); j++)
       m1(i,j) = i+j;
   m2 = 3.7;
   Matrix sum = m1 + m2
   Matrix product = m1 * m2;

Operators such as << >> for printing or () for assigning are compatible with matrices:

..  code-block:: cpp

   std::cout << "m1: \n" << m1 << std::endl;


You can extract a single row or column from a matrix:

..  code-block:: cpp

   Vector col1 = product.Col(1);

   Vector row2 = product.Row(2);

You can also extract multiple rows or columns from a matrix:

..  code-block:: cpp

   // Gets the 2 and 5 column of the matrix.
   auto cols = product.Cols(2, 5);

   // Gets the 2 and 5 row of the matrix.
   auto rows = product.Rows(2, 5);

Extracting both rows and columns at once yields a sub-matrix of the original one:

..  code-block:: cpp

   auto sub = m2.rows(1,3).cols(2,4)

Other features are:

Matrix transposition:

..  code-block:: cpp

   sub.T
Matrix-Vector Multiplication:

..  code-block:: cpp

   auto res = m2*z
