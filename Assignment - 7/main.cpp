#include <iostream>
#include "SparseMatrix.h"
#include <chrono>

using namespace std;

int main() {
    SparseMatrix lhs(R"(C:\Users\Serhan\Desktop\serhan.yilmaz_Yilmaz_Serhan_7\m1.txt)"); // reads the matrix stored in m1.txt
    SparseMatrix rhs(R"(C:\Users\Serhan\Desktop\serhan.yilmaz_Yilmaz_Serhan_7\m2.txt)"); // reads the matrix stored in m2.txt
    // Stores in the SparseMatrix "result" the result of the following operation
    // lhs * rhs
    //SparseMatrix result = lhs.mat_mul(rhs);
    //cout << "Here's the lhs: " << endl << lhs << endl << "and here's rhs: " << endl << rhs << endl;
    //cout << "Finally, here's the resulting matrix from lhs * rhs: " << endl << result;
    auto start = std::chrono::steady_clock::now();
    SparseMatrix result = lhs.mat_mul(rhs);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    return 0;
}
