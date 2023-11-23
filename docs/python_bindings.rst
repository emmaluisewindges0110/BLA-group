.. _Python Bindings:

Python Bindings
===================================

This project provides python bindings.
To use the the python bindings in your project, you must first install it via the following command:

..  code-block::

    pip install git+https://github.com/emmaluisewindges0110/BLA-group.git

You can then import the bindings in your project.

..  code-block:: python

    from pepbla.bla import Matrix, Vector

    x = Vector(3)
    y = Vector(3)
    A = Matrix(2, 2)

Value assignment of vectors works with square brackets, matrix entries are seperated with a comma:

..  code-block:: python

    v[:] = 7

    A[0, 0] = 2
    A[0, 1] = 0
    A[1, 0] = 0
    A[1, 1] = 1


Basic operations such as skalar vector multiplication, Matrix addition and multiplication are used the same way as in c++ ,
same goes for operators like printing and getting single entries of a vector/matrix:

..  code-block:: python

    B = Matrix(2, 3)
    for i in range(B.shape[0]):
        for j in range(B.shape[1]):
            B[i, j] = 2
    C = A @ B

    w = 3 * v

    print(A[1, 1])


