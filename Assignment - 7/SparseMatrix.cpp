#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <vector>
using namespace std;

#include "SparseMatrix.h"

//Written by Serhan Yilmaz
//Student Number: 00031275

SparseMatrix::SparseMatrix(const string &file_name) {
    ifstream fin(file_name);
    if (fin.fail()) {
        throw "File couldn't be opened";
    }
    // actual head_
    head_ = nullptr;
    // head_ of current row
    row_node *curr_head = nullptr;
    // row counter for error checking
    int row = 0;
    fin >> num_rows_ >> num_columns_;
    if (fin.fail()){
        throw "Invalid number of rows or number of columns";
    }
    string line;
    getline(fin, line);
    while (getline(fin, line)) {
        int col = 0, val;
        stringstream ss(line);
        // if this is the first row
        if (head_ == nullptr) {
            head_ = curr_head = new row_node;
        } else {
            curr_head->down = new row_node;
            curr_head = curr_head->down;
        }
        // pointer at last cell added in this row
        cell_node *curr_cell = nullptr;
        while (ss >> val) {
            if (val != 0) {
                cell_node *new_cell = new cell_node;
                new_cell->value = val;
                new_cell->column = col;
                // if first cell in this row
                if (curr_cell == nullptr)
                    curr_head->cell = curr_cell = new_cell;
                else {
                    curr_cell->right = new_cell;
                    curr_cell->right->left = curr_cell;
                    curr_cell = curr_cell->right;
                }
            }
            col++;
            if (col > num_columns_) {
                throw "Too many columns in row " + to_string(row);
            }
        }
        row++;
        if (row > num_rows_) {
            throw "Too many rows";
        }
        if (col < num_columns_) {
            throw "Not enough columns in row " + to_string(row);
        }
    }
    if (row < num_rows_) {
        throw "Not enough rows";
    }
}

SparseMatrix::~SparseMatrix() {
    while (head_ != nullptr) {
        cell_node *cell = head_->cell;
        while (cell != nullptr) {
            cell_node *t = cell->right;
            delete cell;
            cell = t;
        }
        row_node *t = head_->down;
        delete head_;
        head_ = t;
    }
}

ostream &operator<<(ostream &out, const SparseMatrix & rhs) {
    int rows = 0;
    row_node * head = rhs.head_;
    while (head != nullptr) {
        // To know how many zeros to print between cells
        int col = -1;
        cell_node *cell = head->cell;
        while (cell != nullptr) {
            col++;
            // until we get to this cell's column, print zeros
            while (col < cell->column) {
                out << "0 ";
                col++;
            }
            out << cell->value << " ";
            col = cell->column;
            cell = cell->right;
        }
        // If there are more zeros after the last cell in the row,
        // print them
        while (col < rhs.num_columns_ - 1) {
            out << "0 ";
            col++;
        }
        out << endl;
        head = head->down;
        rows++;
    }
    // If there are rows with no cells at all, print zeros for them
    while (rows < rhs.num_rows_) {
        for (int i = 0; i < rhs.num_columns_; i++) {
            out << "0 ";
        }
        out << endl;
        rows++;
    }
    return out;
}

SparseMatrix::SparseMatrix(SparseMatrix&& rhs) {
    head_ = rhs.head_;
    rhs.head_ = nullptr;
    num_rows_ = rhs.num_rows_;
    num_columns_ = rhs.num_columns_;
}

SparseMatrix::SparseMatrix(row_node *head, int num_rows, int num_columns): head_(head), num_rows_(num_rows), num_columns_(num_columns) {}

SparseMatrix::SparseMatrix(const SparseMatrix &rhs): head_(nullptr), num_columns_(rhs.num_columns_), num_rows_(rhs.num_rows_) {
    copy(rhs, head_, num_rows_, num_columns_);
}

SparseMatrix &SparseMatrix::operator=(const SparseMatrix & rhs) {
    if (&rhs != this)
        copy(rhs, head_, num_rows_, num_columns_);
    return *this;
}

void SparseMatrix::copy(const SparseMatrix& rhs, row_node *&head, int &num_rows, int &num_columns) {
    num_rows = rhs.num_rows_;
    num_columns = rhs.num_columns_;
    if (rhs.num_rows_ == 0 || rhs.num_columns_ == 0) return;
    row_node* curr = head = new row_node;
    row_node* other_head = rhs.head_;
    while(other_head!= nullptr){
        cell_node* rhs_cell = other_head->cell;
        cell_node* my_cell = nullptr;
        while (rhs_cell!=nullptr){
            cell_node * new_cell = new cell_node(rhs_cell->column, rhs_cell->value);
            if (my_cell == nullptr) my_cell = curr->cell = new_cell;
            else{
                my_cell->right = new_cell;
                my_cell->right->left = my_cell;
                my_cell = my_cell->right;
            }
            rhs_cell = rhs_cell->right;
        }
        if (other_head->down!=nullptr){
            curr->down = new row_node;
            curr = curr->down;
        }
        other_head = other_head->down;
    }
}

//Here starts the part I added:
// Function to get the value of a cell at a given row and column
int get(const SparseMatrix& matrix, int row, int col)  {
    //Inside, the logic is simple, first the function iterates all through the rows to get the desired row:
    row_node* curr_row = matrix.head_;
    for (int i = 0; i < row; i++) {
        curr_row = curr_row->down;
    }
    //Then the function iterates through the cells on that row to reach the wanted column:
    cell_node* curr_cell = curr_row->cell;
    while (curr_cell != nullptr && curr_cell->column < col) { // these two conditions must be satisfied at the same time, whichever one fails, the loop breaks
        curr_cell = curr_cell->right;
    }
    // return 0 if the cell is empty, if not then return the value of the cell
    if (curr_cell != nullptr && curr_cell->column == col) {
        return curr_cell->value;
    } else {
        return 0;
    }
}

//here is the second helper function, removing all the excess code.
//this function 'set' is purposed to set the cell at 'row' and 'col' to the value 'val'
void set(SparseMatrix& matrix, int row, int col, int val) {
    //The logic is pretty similar to the get function, first iterate through the rows to get the row:
    row_node* curr_row = matrix.head_;
    for (int i = 0; i < row; i++) {
        //curr_row = curr_row->down;
        if(curr_row->down == nullptr){
            curr_row->down = new row_node();
            curr_row = curr_row->down;
        }
        else{curr_row = curr_row->down;}
    }
    //Then iterate through the cells to get the cell at the wanted column:
    cell_node* curr_cell = curr_row->cell;
    cell_node* prev_cell = nullptr;
    while (curr_cell != nullptr && curr_cell->column < col) {
        prev_cell = curr_cell;
        curr_cell = curr_cell->right;
    }
    //at this point, I'm starting to think that this is not very efficient, it will work alright but for too big matrices it might be a better idea to just use pointers among the functions really.
    //I will look into that if I have the time...
    //Anyways, so if the cell we got is nullptr OR if the cell exists but the column is larger than col
    //Note that cell->column > col might be true as this is a sparse matrix multiplication algorithm, in that case this means that we must still create a new cell for the exact location.
    //Hence, I wrote two parts here:
    // If the cell is nullptr, itself and the previous node or just itself will be created
    //If not, then that's an existing cell but not the one we desire, so the previous cell will be created and that will be our cell, and the right cell of the new cell will be assigned to the old cell.

    if (curr_cell == nullptr || curr_cell->column > col) {
        cell_node* new_cell = new cell_node(col, val);
        if (prev_cell != nullptr) {
            prev_cell->right = new_cell;
            new_cell->left = prev_cell;
        } else {
            curr_row->cell = new_cell;
        }
        if (curr_cell != nullptr) {
            curr_cell->left = new_cell;
            new_cell->right = curr_cell;
        }
        //If on the other hand the cell does exist at where we want it, then just update its value:
    } else {
        curr_cell->value = val;
    }
}

//And here's the final helper function:
//The logic for this is pretty much simple again, when given a rhs matrix, denoted by 'other', just go through its elements to perform a dot product.

void SparseMatrix::mat_mul_helper(const SparseMatrix &other, SparseMatrix &result, int i) {
    for (int j = 0; j < other.num_columns_; j++) { //through all columns
        int sum = 0; //initialize a sum to 0
        row_node *row = head_;
        for (int k = 0; k < i; k++) {// get the corresponding row
            row = row->down;
        }
        cell_node *cell = row->cell;
        for (int k = 0; k < other.num_rows_; k++) { //iterate through all the cells on the row
            if (cell != nullptr && cell->column == k) {
                sum += cell->value * get(other, k, j); // multiply and add up the cells
                cell = cell->right; //go to the next cell
            }
        }
        // Store result in corresponding cell of result matrix
        set(result, i, j, sum); //now modify the corresponding entry of the result matrix.
    }
}
//And finally, the beloved mat_mul:
SparseMatrix SparseMatrix::mat_mul(const SparseMatrix& other) {
    //First off, I know from linear algebra that the #columns of the first matrix must equal the #rows of the second matrix
    //So check that, and if that's not the case then print an error and terminate.
    if (num_columns_ != other.num_rows_) {
        cout << "Error! Number of columns in the first matrix != Number of rows in the second matrix!" << endl;
        exit(0);
    }
    //If not, then initialize the result matrix
    row_node *matrixHead = new row_node(); //here's the head
    SparseMatrix result(matrixHead, num_rows_, other.num_columns_); //matrix set
    //now, the with the helper functions we'll iterate through the rows of the 1st and columns of the 2nd matrix
    //Before that, make this multithreaded:
    vector<thread> threads; //creating a vector of threads
    for(int j = 0; j < num_rows_; ++j){ //assign each row to a thread, this improves the performance drastically
        threads.push_back(thread (&SparseMatrix::mat_mul_helper, this, ref(other), ref(result), j)); //and push back each thread to the vector
    }
    for(thread& thread : threads){
        thread.join(); // now join every thread in the vector back into the program
    }
    //note that given more time, this could be much more efficient in my opinion. however with limited time, there are some optimization issues here most likely.
    //I will try to turn this code into a fully pointer-based one later on, and will see how it goes then. That should eliminate unnecessary iterations.
    return result; //and finally, return the resulting matrix.
}

//Thank you for this great semester, it's been great taking CS204.
//Serhan


