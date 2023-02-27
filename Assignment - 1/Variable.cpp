#include "variable.h"
#include <iostream>
#include <vector>
#include <fstream>

//Code written by Serhan Yilmaz, with the student number 00031275.

Variable::Variable()
{
	Location_x = 0;
	Location_y = 0;
	Value = 0;
	Weight = 0;
	// declaring all the private elements of an object in the Variable class.
}

void Variable::setLocation_x(int x_loc)
{
	Location_x = x_loc;
}

int Variable::getLocation_x() const
{
	return Location_x;
}

void Variable::setLocation_y(int y_loc)
{
	Location_y = y_loc;
}

int Variable::getLocation_y() const
{
	return Location_y;
}


void Variable::setValue(int val)
{
	/*
	Value = val % 10; // value here, is the remainder of val from 10, since we want it so stay in [1,9]
	if (Value == 0) //for when val = 10k, Value would equal 0, which is out of the scope [1,9]. therefore, we want value to reset into the smallest integer in the set [1,9] which is 1.
	{
		Value = 1;
	}
	*/

	Value = val;
	
}

int Variable::getValue() const
{
	return Value;
}

void Variable::setWeight(int wght)
{
	Weight = wght;
}

int Variable::getWeight() const
{
	return Weight;
}


int Variable::variablesOnRow(vector<Variable> VariableVec, int row)
{
	int count = 0;

	for (int i = 0; i < VariableVec.size(); i++)
	{
		if(VariableVec[i].getLocation_x() == row)
		{
			count++;
		}
	}
	return count; // literally a function that returns how many elements the vector has, on the given row.
}

vector<Variable> Variable::allVarOnRow(vector<Variable> &VariableVec, int row)
{
	vector<Variable> allVec;

	for (int i = 0; i < VariableVec.size(); i++)
	{
		if (VariableVec[i].getLocation_x() == row)
		{
			allVec.push_back(VariableVec[i]);
		}
	}
	return allVec;
}