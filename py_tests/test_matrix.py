# search for libraray like bla.cpython-312-darwin.so in the build directory:
# import sys
# sys.path.append('/home/peter/uni/scicomp/bla-group/build')
# from bla import Vector

# import from the installed pepbla package:
from pepbla.bla import Matrix, Vector

A = Matrix(3, 4)
A[2, 3] = 4.0
for i in range(A.shape[0]):
    for j in range(A.shape[1]):
        A[i , j] = i +j -1
B = Matrix(3, 4)
for i in range(B.shape[0]):
    for j in range(B.shape[1]):
        B[i, j] = 2

# print(A[2, 3])
# print(A.shape)
print(f"A: {A}")
print(f"B: {B}")
print(f"Sum A + B: {A + B}\n")

# v = Vector(3)
# v[:] = 7
# print("Skalar-vector mult: ", 2 * v)

# A = Matrix(2, 2)
# B = Matrix(2, 3)

# A[0, 0] = 2
# A[0, 1] = 0
# A[1, 0] = 0
# A[1, 1] = 1

# B[0, 0] = 0
# B[0, 1] = 1
# B[0, 2] = 2
# B[1, 0] = 3
# B[1, 1] = 4
# B[1, 2] = 5

# print("Matrix A: \n")
# print(A)
# print("Matrix B: \n")
# print(B)
# print("Product A@B: \n")
# print(A@B)

# # import pickle
# # f = open("file.txt", 'wb')
# # pickle.dump([2,"hello", A], f)
# # print("STORED")
# # print
# # del f

# # f2 = open("file.txt", 'rb')
# # val = pickle.load(f2)
# # print(val)
# # print(val[2])

# print("Matrix-Vector Product:")
# A = Matrix(3, 2)
# v = Vector(2)
# A[0, 0] = 1
# A[0, 1] = 0
# A[1, 0] = 0
# A[1, 1] = 2
# A[2, 0] = 0.5
# A[2, 1] = 0.5
# v[0] = 3
# v[1] = 5
# print(A@v)