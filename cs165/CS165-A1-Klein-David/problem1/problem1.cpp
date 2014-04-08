// David Klein
// CS 165
// Fall 2013
// Assignment 1 - Problem 1

#include <iostream>
#include <fstream>
#include "MatrixHelper.h"

//http://en.wikipedia.org/wiki/Letter_frequency

using namespace std;



int main()
{
	string line, total;
	ifstream infile("problem1.enc");
	string s = "A";

	if( infile.is_open() )
	{
		while( getline(infile, line) )
		{
			total.append(line);
		}
		infile.close();

		int a = 107;
		int b = 90;
		MatrixHelper matrix(a, b);
		matrix.Fill(total);
		matrix.Transpose();
		matrix.MapMatrix();
		matrix.Print();
	}
	
	else cout << "Unable to open problem1.enc" << endl;

	
	return 0;
}
