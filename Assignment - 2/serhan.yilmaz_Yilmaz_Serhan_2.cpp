#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "sparse_matrix_2d_linked_list.h"

using namespace std;


row_node* read_matrix(const string& filename, int& num_rows, int& num_columns)
{
    ifstream file;
    string line;
    int num_rs, num_cs;
    file.open(filename.c_str());
    getline(file, line); //take the first line
    stringstream s(line); //stream the first line into the program
    s >> num_rs >> num_cs; //take the #rows and #cols
    num_rows = num_rs;
    num_columns = num_cs;
    #ifdef _DEBUG
    cout << "num_rows = " << num_rows << " and num_columns = " << num_columns << endl; // this checks out
    cout << "num_rs = " << num_rs << " and num_cs = " << num_cs << endl;
    #endif

    //at this point, we have what we need. now we know the size of the matrix.
    //now, we should move on to create the linked list.
    row_node* headRow = new row_node(); // allocate memory for the first row pointer.
    row_node* tempHeadRow = headRow; //allocate memory for the temp row pointer
    for (int i = 0; i < num_rows; i++)
    {
        getline(file, line);
        stringstream s(line); // taking every row and streaming into the program
        int current_element, col = 0;
        row_node* rowFirstPointer = new row_node(); //allocate memory
        tempHeadRow->down = rowFirstPointer;
        //now we have the algorithm working for the row pointers, now we should have cells.
        //let's start for each column:
        cell_node* tempColumnHead = nullptr;

        while (s >> current_element) // while the program takes inputs
        {
            //inside, current_element is equal to the element we have at hand
            //this element is at row row, column col. -> (row, col).
            //then inside, create the cell
            if (current_element != 0) //check this as we have a sparse matrix so there will be zeroes
            {
                cell_node* cellNode = new cell_node(); //allocate memory for a new node
                cellNode->value = current_element;
                cellNode->column = col;
                //now that the private variables of the struct element are assigned, 
                //let's move onto the next step: linking the cells to the row!
                if (rowFirstPointer->cell == nullptr)
                {
                    rowFirstPointer->cell = cellNode;
                }
                else
                {
                    tempColumnHead->right = cellNode;
                    cellNode->left = tempColumnHead;
                }
                tempColumnHead = cellNode;
            }
            col++;
        }

        tempHeadRow = rowFirstPointer;
    }

    tempHeadRow = headRow->down;
    delete headRow;
    return tempHeadRow;
}

//we are now done with the first function.
//the second and third ones are definitely easier, 4th one will take a bit of time and 
//we will see how much god loves me on the 5th and 6th functions.

void print_matrix(row_node *head, int num_rows, int num_columns)
{
    for (int i = 0; i < num_rows; i++)
    {
        cell_node* temp = head->cell;
        for (int j = 0; j < num_columns - 1; j++)
        {
            if (!temp || temp->column != j) // if temp does not exist (since the 0's does not exist in our linked list) or if the columns' are not right, since we skipped the zeroes
            {
                cout << "0" << ' ';
            }
            else
            {
                cout << temp->value << ' ';
                temp = temp->right;
            }
        }
        if (!temp || temp->column != num_columns - 1)
        {
            cout << "0" << endl;
        }
        else
        {
            cout << temp->value << endl;
        }
        head = head->down;
        //not putting any checks as they were not needed in the document.
    }

}

void delete_matrix(row_node* head)
{
    row_node *temp_row;
    while (head != nullptr)
    {
        //we are in the first row, now let's get all the columns and delete them
        cell_node *first_cell = head->cell;
        cell_node *temp_cell;

        while (first_cell != nullptr)
        {
            //now we are starting to delete every element on the row
            temp_cell = first_cell->right;
            delete first_cell;
            first_cell = temp_cell;
            //this is literally the interpretation of the code from the lectures.
            //it is not exactly the same -no plag!- but it has the same gist, a quite similar code could be found on the CS204 slides

        }

        //now that one row is gone, it is time that we assign the next row as temp
        //then we will delete the current row
        //and then we will assign the first row to the second row and so forth
        //it is exactly like what we have done with the columns above.
        temp_row = head->down;
        delete head;
        head = temp_row;
    }

    // and we are done, great!
}

row_node* add_matrices(row_node* left, row_node* right, int num_rows, int num_columns)
{
    row_node* initialHead = new row_node();
    row_node* head = initialHead; //this will be the head of the linked list which we will return at the end
    for (int row = 0; row < num_rows; row++) //iterate through each row
    {
        //now we are inside one row, say the first one

        //what we need to do now, is to create a new row_node object to succesfully move onto the next one
        row_node* nextRow = new row_node();
        //now, assign the 'down' element to the new node.
        head->down = nextRow;
        //and, replace head with the next one.
        head = nextRow;

        //create temporary cell_node objects to work with:
        cell_node* tempCell = new cell_node();
        cell_node* tempLeft = left->cell;
        cell_node* tempRight = right->cell;

        for (int col = 0; col < num_columns; col++)
        {
            //now, check the data on each linked list, left and right and add them up into a third matrix
            int left_val, right_val;
            if (!tempRight || tempRight->column != col)
            {
                right_val = 0;
            }
            else
            {
                right_val = tempRight->value;
                tempRight = tempRight->right;
            }
            if (!tempLeft || tempLeft->column != col)
            {
                left_val = 0;
            }
            else
            {
                left_val = tempLeft->value;
                tempLeft = tempLeft->right;
            }
            if (left_val + right_val != 0)
            {
                cell_node* cell = new cell_node();
                if (head->cell != nullptr)
                {
                    tempCell->right = cell;
                    cell->left = tempCell;
                }
                else
                {
                    head->cell = cell;
                }
                cell->column = col;
                cell->value = left_val + right_val;
                tempCell = cell;
            }
        }
        left = left->down;
        right = right->down;
    }

    head = initialHead->down;
    delete initialHead;
    return head;
}




int get_the_value_at_the_location(row_node* head, int row, int column, bool& flag) 
{
    row_node* currentRow = head;
    for (int i = 0; i <= row; i++)
    {
        currentRow = currentRow->down;
    }
    cell_node* currentCell = currentRow->cell;
    for (int j = 0; j <= column; j++)
    {
        currentCell = currentCell->right;
    }
    if (currentCell != nullptr) {
        int value = currentCell->value;
        return value;
    }
    else 
    { 
        flag = false; 
    }

}

bool is_symmetric(row_node* head, int num_rows, int num_columns) 
{
   // first off, we check the first condition provided in the homework document:
    if (num_rows != num_columns)
    {
        return false; // a symmetric matrix HAS TO be a square
    }
    now, moving onto the second condition
    element at (i,j) MUST be equal to the element at (j,i) for every i and j.
    bool flag = true;
    for (int i = 0; i < num_rows; i++) 
    {

            for (int j = 0; j < num_columns; j++)
            {

                int first = get_the_value_at_the_location(head, i, j, flag);
                int second = get_the_value_at_the_location(head, j, i, flag);
                if (first != second && flag == true)
                {
                    return false;
                }
            }
       /* when the program enters here it means that the current index is a nullptr.*/

    }
    return true;

    ////hence, we start by assigning the first row node.
    //row_node* currentRow = head;
    ////now we iterate through each row:
    //for (int i = 0; i < num_rows; i++) 
    //{
    //    //let's get the current cell we are at:
    //    cell_node *currentCell = currentRow->cell;
    //    //now, let's iterate on every cell on the row:
    //    for (int j = 0; j < num_columns; j++) 
    //    {
    //        if (currentCell->column != i) //it is meaningless to look into the ones on the diagonal on the matrix. therefore we skip those
    //        {
    //            if (currentCell != nullptr) //if, in fact the matrix starts with a number different than zero on the original matrix:
    //            {
    //                if()
    //            }
    //        }
    //    }
    //}
}



row_node* transpose(row_node* head, int num_rows, int num_columns) 
{
   /* row_node* newHead = new row_node();
    row_node* currentNewHead = newHead;
    row_node *currentNode = head;

    for (int i = 0; i < num_columns - 1; i++) 
    {
        row_node *nextRow
    }

    for (int i = 0; i < num_rows; i++) 
    {
        cell_node* newCell = new cell_node();
        cell_node* currentCellNode = new cell_node();
        if (currentNode->cell == nullptr) 
        {
            break;
        }
        else 
        {
            currentCellNode = currentNode->cell;
            while (currentCellNode->column > -1) 
            {
                int column = currentCellNode->column;
                int value = currentCellNode->value;
                currentNewHead = newHead;
                for (int j = 0; j < column; j++) 
                {
                    currentNewHead = currentNewHead->down;
                }
                if (currentNewHead->cell != nullptr) 
                {*/
    row_node* blankNode = new row_node();
    return blankNode;
}
