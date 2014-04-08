// David Klein
// CS 100
// Assignment 2
// Oct 9, 2011

#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

inline vector<string> split( const string s, const string pat )
{
	vector<string> fragments;
	string temp = "";

	for( int i = 0; i < s.size(); i++ )
	{
		if( s[i] != pat[0] )
			temp.push_back(s[i]);
		else
		{
			fragments.push_back(temp);
			temp = "";
		}
	}

	fragments.push_back(temp);

	return fragments;
}

inline string join( const vector<string> v, const string pat, int start, int end )
{
	assert( !(start > end) );
	assert( !(start > v.size()-1) );

	string temp = "";
	string return_t = "";

	while( start <= end )
	{
		temp = v[start];
		for( int i = 0; i < temp.size(); i++ )
			return_t.push_back( temp[i] );
		return_t.push_back( pat[0] );
		start++;
		if( start >= v.size() )
			return return_t;
	}

	return return_t;
}

#endif
