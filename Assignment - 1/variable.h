#ifndef variable_h
#define variable_h

//Code written by Serhan Yilmaz, with the student number 00031275.


#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

//defining a class named Variable, to store the following information for each variable found on lhs_matrix:
// x_coordinate, a.k.a. the row; y_coordinate, a.k.a. the column; value and the weight(scalar, found in the rhs_matrix)

class Variable{
public:
	Variable();
	
	void setLocation_x(int);
	int getLocation_x() const;

	void setLocation_y(int);
	int getLocation_y() const;
	
	void setValue(int);
	int getValue() const;
	
	void setWeight(int);
	int getWeight() const;
	
	
	int variablesOnRow(vector<Variable>, int);

	vector<Variable> allVarOnRow(vector<Variable>&, int);

private:
    int Location_x; // the x-location of the variable in the lhs matrix.
	int Location_y; // the y-location of the variable in the lhs matrix.
	int Value; // the value which the variable currently holds.
	int Weight; // the weight the variable has.
};



#endif