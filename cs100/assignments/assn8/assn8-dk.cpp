// David Klein
// CS 100
// Assignment 8
// Due 12/4/12

#include <iostream>
#include <string>
#include <vector>
#include <errno.h>
#include <cassert>

using namespace std;

class String
{
	string s;
	public:
		String( );										// assign a string
		String( string );								// user has entered a string
		int find( String );								// will return the starting location of a string
		String substr( int, int );						// will return the substring at a location
		String replace( int, int, String );				// will replace a string in another string
		String operator=(char *str)						// overload of assignment operator
		{
			s = str;
			return *this;
		}
		friend ostream &operator<<(ostream &out, String temp)	// overload of << operator
		{
			out << temp.s;
			return out;
		}
};

String::String( )
{
	s = "";
}

String::String( string str )
{
	s = str;
}

int String::find( String str )
{
	for( unsigned int i = 0; i < s.length(); ++i )					// This cycles through until we reach the first
	{																//  character that we are looking for in the word
		if( s[i] == str.s[0] )										//  then we check to see if the next location is
		{															//  what we are looking for. If not we keep looking
			for( unsigned int j = 0; j < str.s.length(); ++j )
			{
				if( s[i+j] != str.s[j] )
					break;
				if( s[i+j] == str.s[str.s.length()-1] )
					return i;
			}
		}
	}
	return 0;
}

String String::substr( int pos, int length )
{
	String temp;

	if( pos > s.length() )		// if our position is outside of our string
	{
		cout << "Error(" << errno << "): Position " << pos << " outside string." << endl;
		return temp;
	}
	if( pos + length > s.length() )		// if our pos + length is outside of our string
	{
		errno = 1;
		cout << "Error(" << errno << "): Length " << length << " is too large." << endl;
		return temp;
	}
	for( int i = 0; i < length; ++i)	// sets up the substring
		temp.s += s[pos++];

	return temp;
}

String String::replace( int pos, int length, String str )
{
	if( pos > s.length() )		// if our position is outside of our string
	{
		errno = 2;
		cout << "Error(" << errno << "): Position " << pos << " outside string." << endl;
		return *this;
	}
	if( pos + length > s.length() )		// if our position + length is outside of our string
	{
		errno = 3;
		cout << "Error(" << errno << "): Length " << length << " is too large." << endl;
		return *this;
	}
	for( int i = 0; i < length; ++i )		// does the replace
		s[pos++] = str.s[i];

	return *this;
}

int main( )		// test harness
{
	String base("The itsy bitsy spider climbed up the water spout.");
	String temp("spider");

	assert( base.find(temp) > 0 );		// ASSERT if it doesn't find the word then we stop
	cout << base.find(temp) << endl;

	cout << base.substr( 4, 4 ) << endl;

	temp = "what";
	cout << base.replace( 4, 4, temp ) << endl;

	return 0;
}
