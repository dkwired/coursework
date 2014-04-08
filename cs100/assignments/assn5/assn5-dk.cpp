// David Klein
// CS 100
// Assignment 5

#include <iostream>
#include <string.h>
#include <vector.h>
#include <map.h>
#include <set.h>

using namespace std;

#define each(I) \
	for( __typeof__ ((I).begin()) it=(I).begin(); it!=(I).end(); ++it)

int main( int argc, char* argv[] )
{
	if( argc != 1 )
	{
		cerr << argv[0] << " usage: start end < dictionary\n";
		exit(-1);
	}
	map< string, bool > in_dict;
	map< string, set<string> > d;						// map of sets
	for( string s; cin >> s; )
	{
		in_dict[s] = true;
		for( unsigned int i = 0; i!= s.size(); ++i )	// this builds our adjacency list
		{
			for( char c = 'a'; c != 'z'; ++c )
			{
				string w = s;
				w[i] = c;
				if( in_dict[w] )						// if the new word (different by one
				{										// character is in the dictionary then
					d[s].insert(w);						// we add it to the list and set the
				}
			}
		}
	}

	map< string, bool > in_dict;
	each( d )
	{
		string temp = (*it).first;
	}
	each( d )
	{
		string temp = (*it).first;
		each( d[temp] )

	}

	return 0;
}


