// David Klein
// CS 141
// Fall 2013
// Assignment 2

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "matrix.h"

using namespace std;

int main(int argc, char *argv[])
{
	ifstream infile;
	ofstream outfile;
	string line;
	int count = 0;
	int num_matricies = 0;
	int ncount = 0;
	int m = 0;
	int n = 0;
	int result = 0;

	if ( argc != 3 )
		cout<<"usage: "<< argv[0] <<" <filename>\n";
	else {
 		infile.open(argv[1]);
		if ( !infile.is_open() )
			cout<<"Could not open file\n";
		else
		{
			outfile.open(argv[2], std::ios_base::app);
			getline(infile, line);
			num_matricies = atoi(line.c_str());
			while(count < num_matricies)
			{
				getline(infile, line);
				m = line[0]-48;
				n = line[2]-48;
				Matrix matrix(m, n);
				string tstring = "";
				string outstring = "";
				while( ncount < m )
				{
					getline(infile, line);
					for(int i = 0; i < line.length()-1; i++)
					{
						tstring += line[i++];
					}
					outstring.append(tstring);
					tstring = "";
					ncount++;
				}
				matrix.Fill(outstring);
				result = matrix.FindSquare(m-1,n-1);
				result = result * result;
				outfile << result << endl;
				getline(infile, line);
				count++;
			}
			infile.close();
    		}
	}
	infile.close();

	return 0;
}
