#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "variable.h"
using namespace std;

//Code written by Serhan Yilmaz, with the student number 00031275.

vector<vector<int>> matrix_assigner(string matrix_filename)
{
	//takes the given matrix filename, opens the file and takes it from the file, assigns it to a C++ matrix within the code.
	ofstream file_out;
	ifstream file;
	string line;
	file.open(matrix_filename.c_str());
    if (!file)
    {
        cout << "Error" << endl;
		file_out.open("output.txt");
		file_out << "Error" << endl;
		file_out.close();
        exit(0);
    }
    getline (file,line);
    stringstream s(line);
    int num_rows, num_cols;
    s >> num_rows >> num_cols;
    vector<vector<int>> my_matrix(num_rows, vector<int> (num_cols));
    int linecount = 0;
    while(getline(file,line))
    {
		#ifdef _DEBUG // a little debug mode code, attempted to have a nice mini interface with the linecount.
		cout << line <<	"	this is line #" << linecount << endl;
		#endif
		int colcount_loop = 0;
        stringstream s(line);
        int colNum;
        while (s >> colNum)
        {
            my_matrix[linecount][colcount_loop] = colNum;
            colcount_loop ++;
        }
        linecount ++;
    }
	#ifdef _DEBUG // a little debug mode code, attempted to have a nice mini interface there with the separator lines.
	cout << endl;
	cout << "-------Moving onto the next debug point-------" << endl;
	cout << endl;
	#endif

	file.close();

	return my_matrix;
}

void error_checker(string matrix_filename)
{
	ofstream file_out;
	ifstream file;
	string line;
	int linecount = 0;

	file.open(matrix_filename.c_str());
	getline (file,line);

    stringstream s(line);
    int num_rows, num_cols;
    s >> num_rows >> num_cols;

	while(getline(file,line))
    {
		int colcount_loop = 0;
        stringstream s(line);
        int colsLine;
        while (s >> colsLine)
        {
            colcount_loop ++;
        }
		if (colcount_loop != num_cols) // if, at literally any point in the text provided, there is a missing element, the program gives an error and exits.
		{
			file_out.open("output.txt");
			file_out << "Error" << endl;
			file_out.close();
			cout << "Error" << endl;
			exit(0);
		}
		linecount ++;
    }

	if(linecount != num_rows) // if the number of rows in the text does not match the rows in the matrix, the proogram gives an error and exits. 
	{
		file_out.open("output.txt");
		file_out << "Error" << endl;
		file_out.close();
		cout << "Error" << endl;
		exit(0);
	}

	file.close();
}

void column_checker(string matrix_filename)
{
	ofstream file_out;
	ifstream file;
	string line;

	file.open(matrix_filename.c_str());
	getline (file,line);

    stringstream s(line);
    int num_rows, num_cols;
    s >> num_rows >> num_cols;

	while(getline(file,line))
    {
		int colcount_loop = 0;
        stringstream s(line);
        int cols;
        while (s >> cols) // while we can take an input from the line, increment the number of columns by 1.
        {
            colcount_loop ++;
        }
		if (colcount_loop != 1) // if, at literally any point in the text provided, there is a missing element, the program gives an error and exits.
		{
			cout << "Error" << endl;
			file_out.open("output.txt");
			file_out << "Error" << endl;
			file_out.close();
			exit(0);
		}
    }

	file.close();
}

void lhs_checker(string matrix_filename)
{
	ofstream file_out;
	ifstream file;
	string line;
	int linecount = 0;

	file.open(matrix_filename.c_str());
	getline (file,line);

    stringstream s(line);
    int num_rows, num_cols;
    s >> num_rows >> num_cols;

	while(getline(file,line))
    {
        stringstream s(line);
        int numLhs;
        while (s >> numLhs)
        {
			if((numLhs > 9 || numLhs < 1) && numLhs != -1)
			{
				cout << "Error" << endl;
				file_out.open("output.txt");
				file_out << "Error" << endl;
				file_out.close();
				exit(0);
			}
        }
		linecount ++;
    }
	file.close();

}

void rhs_checker(string matrix_filename)
{
	ofstream file_out;
	ifstream file;
	string line;
	int linecount = 0;

	file.open(matrix_filename.c_str());
	getline (file,line);

    stringstream s(line);
    int num_rows, num_cols;
    s >> num_rows >> num_cols;

	while(getline(file,line))
    {
        stringstream s(line);
        int numRhs;
        while (s >> numRhs)
        {
			if((numRhs > 9 || numRhs < 1)) // check if there are numbers that are not in [1,9]
			{
				file_out.open("output.txt");
				file_out << "Error" << endl;
				file_out.close();
				cout << "Error" << endl;
				exit(0);
			}
        }
		linecount ++;
    }
	file.close();

}

void res_checker(string matrix_filename)
{
	ofstream file_out;
	ifstream file;
	string line;
	int linecount = 0;

	file.open(matrix_filename.c_str());
	getline (file,line);

    stringstream s(line); // create a stringstream object s
	while(getline(file,line))
    {
        stringstream s(line);
        int numRes;
        while (s >> numRes) // feed s into a temporary variable, numRes here.
        {
			if(numRes < 1) //check if any of them are smaller than 1, if yes, then print error to output.txt and terminate the program.
			{
				file_out.open("output.txt");
				file_out << "Error" << endl;
				file_out.close();
				cout << "Error" << endl;
				exit(0);
			}
        }
		linecount ++;
    }
	file.close();

}

vector<Variable> VariableVec;
vector<int> remainder_vector;

void var_assigner(vector<vector<int>> lhs_matrix, vector<vector<int>> rhs_matrix, vector<vector<int>> res_matrix)
{
	for (int i = 0; i < lhs_matrix.size(); i++) //for each row in the lhs_matrix
	{
		for (int j = 0; j < lhs_matrix[0].size(); j++) //for each element on that row
		{
			Variable myVar; //declare a Variable-type object temporarity
			if (lhs_matrix[i][j] == -1)
			{
				myVar.setLocation_x(i); //set x location (row)
				myVar.setLocation_y(j); //set y location (column)
				myVar.setValue(1); //initialize the value as 1 to start with
				myVar.setWeight(rhs_matrix[j][0]); //find the corresponding weight on the rhs_matrix and assign that.
				VariableVec.push_back(myVar); //push back the Variable object into a vector of Variable objects.
			}
		}
	}
	//first for loop ends here, by this point the following are created:
	//VariableVec: a vector of n Variable-class objects {x1, x2, x3, ... , xn}
	//And, for every instance of the Variable-class objects in VariableVec, the following properties are assigned:
	//Location_x, Location_y, Value and Weight.
	//Among these properties, Location_x, Location_y and Weight are set once and for all, and will not change through the program
	//Meanwhile Value is set to 1 to start, and is limited with [1,9]. Therefore, it is prone to change through the runtime.
	//Value will reset to 1 every time the assigner reaches 10, and will therefore stay within [1,9].
	for (int i = 0; i < lhs_matrix.size(); i ++) // for every row in the lhs matrix
	{
		int sum = 0;
		for (int j = 0; j < rhs_matrix.size(); j++)
		{
			if (lhs_matrix[i][j] != -1)
			{
				int temp_var;
				temp_var = lhs_matrix[i][j] * rhs_matrix[j][0]; // row-vector multiplication is done here
				sum += temp_var; // the result for every existing element is added into the sum variable
			}
		}
		
		int remainder = res_matrix[i][0] - sum;
		remainder_vector.push_back(remainder);
		// here, the remainder is found to calculate how much is remaining for each row.
		// at that point, the remainder for each line is pushed back into the remainder_vector.
	}
}

//after this function, all variable-class instances in VariableVec are assigned, and the remainder vector is assigned.
Variable a; // defining an empty variable-class instance to safely use some methods of the class later in the code.

vector<Variable> finalValues;

void row_solver(int row) // here begins the real deal.
{
	//for this code, there are three algorithms which came into my mind: iterative, recursive and sort of a combination of both, using division rules.
	//among these three, the iteratiive option seemed the safest as the complexity is lower than recursive, and it -hopefully- does not use as much resources as the recursive one
	//now, here is how the algorithm will proceed:
	bool flag = true; //first defining a flag here, to determine when it is time to go out the while loop.
	vector<Variable> allVarsOnRow = a.allVarOnRow(VariableVec, row); //for each row, first a vector of variables will be created, which will hold all the Variable-class elements on the specified row.
	// check Variable.cpp for more information of allVarOnRow method, it basically takes a vector of variable type, and the row number, then returns a vector of "Variable"s with all variables on the requested column.
	
	while (flag)
	{
		int sum = 0; // for every major iteration, reset sum.
		int myVarsOnRow = allVarsOnRow.size(); // to iterate through the numbers, first get the number of elements there will be
		for (int i = 0; i < myVarsOnRow; i++)
		{
			#ifdef _DEBUG // code to try in debug mode, it helped me see if the method functions worked properly and if the values were assigned correctly.
			cout << allVarsOnRow[i].getValue() << " is multiplied with " << allVarsOnRow[i].getWeight() << endl;
			#endif
			sum += allVarsOnRow[i].getValue() * allVarsOnRow[i].getWeight();
			// basically, take the current value of every Variable-class object on the specified row, multiply it with its weight, and take the result, and add it to the sum variable
		}
		//here, by the end of this loop, the sum variable for the line is found.

		if (sum == remainder_vector[row])
		{
			//remember our remainder_vector.  now, if the sum we have at hand equals the remainder value for the row, this means that we are done.
			flag = false;
			//so, we make the flag false, and get out of the while loop. we are done with this function
		}
		else
		{
			//the algorithm here is particularly important, I am proud of myself for coming up with this because it looks so elegant.

			int elementToIncrement = myVarsOnRow - 1; //we start by declaring which element of the vector we want to increment.
			// this variable is needed, since we want to have sort of an element pointer that has to move to the first element from the last
			//the algorithm below is so nice that, it is written in a way which does not require us to sort the potential results to get the smallest integer.
			//the algorithm operates from the last operator to the first one which is why elementToIncrement = myVarsOnRow - 1
			//and therefore, it already produces the smallest output possible, without further ado.
			while (true)
			{
				if (allVarsOnRow[elementToIncrement].getValue() == 9) // get the value of the last variable, if it is equal to 9, reset it back to 1 since the interval is [1,9].
				{
					//cout <<	"It's Nine!" << endl;
					allVarsOnRow[elementToIncrement].setValue(1);
					elementToIncrement -= 1; // shift the 'pointer' to the left by 1 element, to allow the algorithm to check the previous element.
				}
				else
				{
					int temp_new = allVarsOnRow[elementToIncrement].getValue(); // if the value is not 9 yet, basically increase it by 1.
					temp_new++;
					allVarsOnRow[elementToIncrement].setValue(temp_new);
					break;
				}
			}
			//note that, for the algorithm to work, it is absolutely essential that the elementToIncrement is redefined after every take.
			//that is since, we want the program to work with rightmost element at all times, it is as  if we are working on an integer on mod 10, except we do not have 0 :)

		}
	}


	for (int i = 0; i < allVarsOnRow.size(); i++)
	{
		finalValues.push_back(allVarsOnRow[i]); //for every value found, push back the final values into a vector to print it later to output.txt
	}
}

void output_printer()
{
	ofstream file_out; // create an ofstream object

	file_out.open("output.txt"); //open the file output.txt

	for (int i = 0; i < VariableVec.size(); i++) //for every variable, print it as Location_x(row), Location_y(column), Value
	{
		file_out << VariableVec[i].getLocation_x() << " " << VariableVec[i].getLocation_y() << " " << finalValues[i].getValue() << endl;
	}

	file_out.close(); //close the file to free up resources.
}

int main()
{
	vector<vector<int>> lhs_matrix, rhs_matrix, res_matrix;
    string lhs_filename, rhs_filename, res_filename, line;
    cout << "Enter the filename for the left-hand-side matrix." << endl;
    cin >> lhs_filename;
	lhs_matrix = matrix_assigner(lhs_filename);
	cout << "Enter the filename for the right-hand-side matrix." << endl;
    cin >> rhs_filename;
	rhs_matrix = matrix_assigner(rhs_filename);
	cout << "Enter the filename for the resulting matrix." << endl;
    cin >> res_filename;
	res_matrix = matrix_assigner(res_filename);
	// at this point, all files are carefully assigned to a matrix in the code, without problems.
	cout << endl <<  "-----Matrices Successfully Assigned-----" << endl;

	// the assigner functions already have error protection, against problems with the file opening

	// now it is time to write the other error functions

	error_checker(lhs_filename);
	error_checker(rhs_filename);
	error_checker(res_filename);
	//first error check is done above, this checks if the number of rows and cols in the txt matches with that of the matrix.
	
	column_checker(rhs_filename);
	column_checker(res_filename);
	//second error check is done above, this checks if the number of columns in rhs and res are 1.

	lhs_checker(lhs_filename);
	//third error check is done above, this checks if the matrix lhs has any elements that are not in [1,9] U {-1}.

	rhs_checker(rhs_filename);
	//fourth error check is done above, this checks if the vector rhs has any elements that are not in [1,9].

	res_checker(res_filename);
	//fifth and the last error check is done above, this checks if the vector res has any elements that are smaller than 1.

	cout << endl <<  "-----Matrices Passed All Tests-----" << endl;
	//when the statement above is printed, this shows that the matrices have been successfully checked.


	//All checks and input assignments are completed here, now the program will find the missing numbers.

	var_assigner(lhs_matrix, rhs_matrix, res_matrix);

	for (int k = 0; k < lhs_matrix.size(); k++) // solve for each row
	{
		row_solver(k);
	}

	output_printer();

	#ifdef _DEBUG // some code for debugging, with a minor debug interface attempt by me, with using separator lines for each row of matrices and such :).
	vector<vector<vector<int>>> all_matrices;
	all_matrices.push_back(lhs_matrix);
	all_matrices.push_back(rhs_matrix);
	all_matrices.push_back(res_matrix);

	for (int k = 0; k < 3; k++)
	{
		for (int i = 0; i < all_matrices[k].size(); i++)
		{
			if (i > 0 && all_matrices[k][i].size() != 1)
			{
				cout << "-----Row Separator-----" << endl;
			}
			for (int j = 0; j < all_matrices[k][i].size(); j++)
			{
				cout << all_matrices[k][i][j] << endl;
			}
		}
		cout << endl;
		cout << "This was matrix #" << k << endl;
		cout << endl;
		cout << "-------Moving onto the next debug point-------" << endl;
		cout << endl;
	}
	#endif

    return 0;
}