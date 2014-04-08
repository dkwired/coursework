#ifndef __MATRIXHELPER_H__
#define __MATRIXHELPER_H__

#include <iostream>
#include <fstream>

using namespace std;

class MatrixHelper
{
	int m, n;
	string **matrix;
	string **result;
	public:
		MatrixHelper(int&, int&);
		void Init(int&, int&);
		void Fill(string&);
		void Transpose();
		void Print();
		void MapMatrix();
		~MatrixHelper();
};

MatrixHelper::MatrixHelper(int & row, int & col)
{
	m = row;
	n = col;

	matrix = new string*[m];
	for(int i = 0; i < m; i++)
		matrix[i] = new string[n];

	result = new string*[n];
	for(int i = 0; i < n; i++)
		result[i] = new string[m];
}

void MatrixHelper::Init(int & row, int & col)
{
	m = row;
	n = col;
	matrix = new string*[m];

	for(int i = 0; i < m; i++)
		matrix[i] = new string[n];
}

void MatrixHelper::Fill(string & s)
{
	int pos = 0;
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n; j++)
		{
			matrix[i][j] = s[pos];
			pos++;
		}
	}
}

void MatrixHelper::Transpose()
{
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n; j++)
			result[j][i] = matrix[i][j];
	}
}

void MatrixHelper::MapMatrix()
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
		{
			if(result[i][j] == "A")
				result[i][j] = "S";
			if(result[i][j] == "B")
				result[i][j] = "L";
			if(result[i][j] == "C")
				result[i][j] = "D";
			if(result[i][j] == "D")
				result[i][j] = "U";
			if(result[i][j] == "E")
				result[i][j] = "B";
			if(result[i][j] == "F")
				result[i][j] = "V";
			if(result[i][j] == "G")
				result[i][j] = "E";
			if(result[i][j] == "H")
				result[i][j] = "X";
			if(result[i][j] == "I")
				result[i][j] = "Q";
			if(result[i][j] == "J")
				result[i][j] = "T";
			if(result[i][j] == "K")
				result[i][j] = "O";
			if(result[i][j] == "L")
				result[i][j] = "F";
			if(result[i][j] == "M")
				result[i][j] = "N";
			if(result[i][j] == "N")
				result[i][j] = "Z";
			if(result[i][j] == "O")
				result[i][j] = "K";
			if(result[i][j] == "P")
				result[i][j] = "H";
			if(result[i][j] == "Q")
				result[i][j] = "M";
			if(result[i][j] == "R")
				result[i][j] = "J";
			if(result[i][j] == "S")
				result[i][j] = "Y";
			if(result[i][j] == "T")
				result[i][j] = "C";
			if(result[i][j] == "U")
				result[i][j] = "L";
			if(result[i][j] == "V")
				result[i][j] = "G";
			if(result[i][j] == "W")
				result[i][j] = "W";
			if(result[i][j] == "X")
				result[i][j] = "A";
			if(result[i][j] == "Y")
				result[i][j] = "R";
			if(result[i][j] == "Z")
				result[i][j] = "P";
		}
	}

}

void MatrixHelper::Print()
{
	ofstream outfile;
	outfile.open("output.txt");
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
			outfile << result[i][j] << " ";
	}
	outfile.close();
}
MatrixHelper::~MatrixHelper()
{
	for(int i = 0; i < m; i++)
		delete matrix[i];

	for(int i = 0; i < n; i++)
		delete result[i];

	delete matrix;
	delete result;
}

#endif 
