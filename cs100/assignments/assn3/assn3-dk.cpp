// David Klein
// CS 100
// Assignment 3 part 2
// Oct 24th, 2011

#include <iostream>
#include <string>
#include <sys/wait.h>
#include <errno.h>
#include <vector>
#include <sstream>
#include <cassert>
#include <unistd.h>

using namespace std;

//#define each(I) \
//	for( typeof((I).begin()) it=(I).begin(); it!=(I).end(); ++it )

int Get_Er_Done( vector<string> tok )
{
	if( tok.empty() )	// if tok is empty >> out message
	{
		cout << "No Command Entered" << endl;
		return 0;
	}
	// Change Directory
	if( tok[0] == "cd" && (tok[1].c_str() == NULL) )				// if the first string == 'cd'...
	{															// and the next string is empty...
		char* dHome = getenv("HOME"); //home directory			// then we set directory to home
		chdir( (const char*)dHome );
		cout << "Current (HOME) directory: " << dHome << endl;
		return 0;
	}
	if( tok[0] == "cd" && (tok[1].c_str() != NULL) )
	{
		char buf[100] = { };
		char* dCurrent = dCurrent = getcwd(buf, 100 );			// else we set directory to entered...
		cout << "Current directory: " << dCurrent << endl;		// path name
		char* dPath = (char*) tok[1].c_str();
		if( chdir( (const char*)dPath ) == -1 )					// call change directory, return on error
			cout << strerror(errno) << endl;
		dCurrent = getcwd(buf, 100 );
		cout << "New Directory: " << dCurrent << endl;
		return 0;
	}
	// create parent and child
	int status;
	if( pid_t kidpid = fork() )
	{
		if( tok[tok.size()-1] != "&" )			// wait for child process to end when
		{										// ..."&" is entered
		//	cout << "wait called" << endl;
			waitpid(-1, &status, 0);
		}

		return(status);
	}
	else
	{
		char* arglist[1+tok.size()];				// we will store our pointers to strings here
		int argct = 0;

		for( int i = 0; i != tok.size(); ++i )		// loop for our string pointers
		{
			if( tok[i] == "&" )
				break;
			else if( tok[i] == "<" )
				freopen(tok[++i].c_str(), "r", stdin);	// write in a file
			else if( tok[i] == ">" )
				freopen(tok[++i].c_str(), "w", stdout);	// write out if the file does not exist
			else if( tok[i] == ">>" )
				freopen(tok[++i].c_str(), "a", stdout);	// write out to file if it does
			else if( tok[i] == "2>" )
				freopen(tok[++i].c_str(), "a", stderr);	// error
			else if( tok[i] == "|" )
			{
				int mypipe[2];
				if( pipe(mypipe) )	// creates a pair of file descriptors
				{
					cerr << "myshell " << strerror(errno) << endl;
					return -1;
				}
				else if( fork() )	// you're the consumer
				{
					close( mypipe[1] );				// close input to pipe
					dup2( mypipe[0], 0 );			// opens up pipe at [0]
					while( *tok.begin() != "|" )	// errase tok starting at the beginning
						tok.erase( tok.begin() );
					tok.erase( tok.begin() );		// ...and ending with the "|"
					exit( Get_Er_Done(tok) );
				}
				else				// you're the producer
				{
					close( mypipe[0] );				// close writing to pipe
					dup2( mypipe[1], 1 );			// opens up pipe at [1]
					break;
				}
			}
			else
			{	// list of char* string pointers
				arglist[argct] = const_cast <char*> ( tok[i].c_str() );
				arglist[++argct] = 0;
			}
		}
		if( (execvp( arglist[0], arglist)) == -1 )	// call execvp on our commands
			cout << "execvp " << strerror(errno) << endl;		// return on error
		exit( errno );
	}
	return 0;
}

int main( int argc, char* argv[] )
{
	vector<string> vec;	// vector of strings
	string pat = ";";	// this is our key when we search through the strings
	while( !cin.eof() )	// while we input
	{
		cout << "? ";	// prompt
		string temp = "";
		getline( cin, temp );	// get our input

		if( temp == "exit" )	// exit
		{
			cout << "exit" << endl;
			return 0;
		}

		stringstream ss(temp);	// use stringstreams to take out whitespace
		while( ss >> temp )		// while stringstream feeds strings to temp
		{
			int temp_size = temp.size();	// stores the size of input string

			if( temp[temp_size-1] != pat[0] )	// if the last character is != ';' then push temp...
				vec.push_back( temp );			// onto vector
			else
			{
				vec.push_back( temp.substr(0, temp_size-1) );	// else we've reached the end of...
				Get_Er_Done( vec );								// the first command and we call...
				vec.clear();									// our command function then clear vector
			}
		}
	}
	return 0;
}
