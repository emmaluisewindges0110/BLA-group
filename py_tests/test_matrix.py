# search for libraray like bla.cpython-312-darwin.so in the build directory:
# import sys
# sys.path.append('/home/peter/uni/scicomp/bla-group/build')
# from bla import Vector

# import from the installed ASCsoft package:
from ASCsoft.bla import Matrix, Vector

A = Matrix(3, 4)
A[2, 3] = 4.0
print(A[2, 3])
print(A.shape)