#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <iostream>
#include <algorithm>
using namespace std;

class Matrix
{
	int m, n;
	string **matrix;
	public:
		Matrix();
		Matrix(int&, int&);
		void Fill(string&);
		void Print();
		int FindSquare(int, int);
		~Matrix();
};

Matrix::Matrix()
{
}

Matrix::Matrix(int & row, int & col)
{
	m = row;
	n = col;

	matrix = new string*[m];
	for(int i = 0; i < m; i++)
		matrix[i] = new string[n];
}

void Matrix::Fill(string & s)
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

int Matrix::FindSquare(int x, int y)
{
	int case1;
	int case2;
	int case3;
	int result;
	if(x==0 || y == 0) return 0;
	if(matrix[x][y] == "R") return 0;
	else
	{
		case1 = FindSquare(x-1,y) + 1;
		case2 = FindSquare(x,y-1) + 1;
		case3 = FindSquare(x-1,y-1) + 1;
		result = min(case1,case2);
		return min(result,case3);
	}
}

void Matrix::Print()
{

}

Matrix::~Matrix()
{
	for(int i = 0; i < m; i++)
		delete matrix[i];

	delete matrix;
}

#endif
