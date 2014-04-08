// David Klein
// CS 100
// Test file for Assignment 2
// Oct 9, 2011

#include <iostream>
#include <vector>
#include <string>
#include "main.h"

using namespace std;

int main()
{
	vector<string> vec;
	string input = "";
	string pat = "";

	cout << "Please enter a string:";
	getline(cin, input);

	cout << "Please enter the character where to cut the string:";
	getline(cin, pat);

	vec = split( input, pat );

	vector<string>::iterator itr;

	for( itr = vec.begin(); itr < vec.end(); ++itr )
		cout << *itr << endl;

	cout <<  endl;

	input = join( vec, pat, 0, 3 );

	for( int i = 0; i < input.length(); i++)
		cout << input[i];

	return 0;
}
