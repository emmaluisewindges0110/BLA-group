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


For matrices you can choose between row-major (`RowMajor`) or column-major (`ColMajor`) storage,
default is row-major.

..  code-block:: cpp

   Matrix<double,RowMajor> m1(5,3), m2(3,3);
   for (int i = 0; i < m1.Height(); i++)
     for (int j = 0; j < m1.Width(); j++)
       m1(i,j) = i+j;
   m2 = 3.7;
   Matrix product = m1 * m2;

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