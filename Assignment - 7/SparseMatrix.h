#include <string>
#include <iostream>
using namespace std;
#ifndef CS204F22_HW7_SPARSEMATRIX_H
#define CS204F22_HW7_SPARSEMATRIX_H

//Written by Serhan Yilmaz
//Student Number: 00031275

struct cell_node{
    cell_node* right;
    cell_node* left;
    int column;
    int value;
    cell_node(): right(nullptr), left(nullptr){}
    cell_node(int c, int v): right(nullptr), left(nullptr), column(c), value(v){}
};

struct row_node{
    row_node* down;
    cell_node* cell;
    row_node(): cell(nullptr), down(nullptr){}
};

class SparseMatrix {
public:
    SparseMatrix(const string &file_name);
    SparseMatrix(row_node * head, int num_rows, int num_columns);
    SparseMatrix(SparseMatrix&& rhs);
    SparseMatrix(const SparseMatrix& rhs);
    SparseMatrix& operator=(const SparseMatrix& rhs);
    ~SparseMatrix();
    SparseMatrix mat_mul(const SparseMatrix& rhs) ; // the function itself
    friend ostream& operator<<(ostream& out, const SparseMatrix& rhs);
    friend int get(const SparseMatrix& matrix, int row, int col); //get the value of a given row and col
    friend void set(SparseMatrix& matrix, int row, int col, int val); //set the value of a given row and col to 'val'
    void mat_mul_helper(const SparseMatrix &other, SparseMatrix &result, int i); //the essential helper
private:
    row_node* head_;
    int num_rows_, num_columns_;
    static void copy(const SparseMatrix& rhs, row_node*& head, int& num_rows, int& num_columns);
};


#endif //CS204F22_HW7_SPARSEMATRIX_H
