# search for libraray like bla.cpython-312-darwin.so in the build directory:
# import sys
# sys.path.append('/home/peter/uni/scicomp/bla-group/build')
# from bla import Vector

# import from the installed pepbla package:
from pepbla.bla import Matrix, Vector

A = Matrix(3, 4)
A[2, 3] = 4.0

B = Matrix(3, 4)
B[2, 3] = 2.0

print(A[2, 3])
print(A.shape)
print(A)

sum = (A + B)
print(sum[2, 3])

v = Vector(3)
v[:] = 7



A = Matrix(2, 2)
B = Matrix(2, 3)

A[0, 0] = 2
A[0, 1] = 0
A[1, 0] = 0
A[1, 1] = 1

B[0, 0] = 0
B[0, 1] = 1
B[0, 2] = 2
B[1, 0] = 3
B[1, 1] = 4
B[1, 2] = 5

print("PRODUCT")
print(A)
print(B)
print(A@B)

# import pickle
# f = open("file.txt", 'wb')
# pickle.dump([2,"hello", A], f)
# print("STORED")
# print
# del f

# f2 = open("file.txt", 'rb')
# val = pickle.load(f2)
# print(val)
# print(val[2])