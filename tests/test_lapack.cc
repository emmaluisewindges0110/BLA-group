#include <iostream>

#include <vector.h>
#include <matrix.h>
#include <lapack_interface.h>

#include <chrono>

using namespace ASC_bla;
using namespace std;

namespace bla = ASC_bla;

int main()
{
    // Vector<double> x(5);
    // Vector<double> y(5);

    // for (int i = 0; i < x.Size(); i++)
    //   {
    //     x(i) = i;
    //     y(i) = 2;
    //   }

    // cout << "x = " << x << endl;
    // cout << "y = " << y << endl;

    // AddVectorLapack (2, x, y);
    // cout << "y+2*x = " << y << endl;

    const int n = 1000;

    bla::Matrix<double, bla::ORDERING::ColMajor> A(n, n);
    bla::Matrix<double, bla::ORDERING::ColMajor> B(n, n);
    bla::Matrix<double, bla::ORDERING::ColMajor> C(n, n);

    size_t flops = n*n*n;
    size_t runs = size_t (1e9 / flops) + 1;

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < runs; i++) {
        // bla::Matrix<double, bla::ORDERING::ColMajor>(A * B);
        MultMatMatLapack(A, B, C);
    }
    auto end = std::chrono::high_resolution_clock::now();
    double time = std::chrono::duration<double>(end-start).count();

    cout << "n = " << n << ", time = " << time << " s, GFlops = " << (flops*runs)/time*1e-9 << endl;
}
