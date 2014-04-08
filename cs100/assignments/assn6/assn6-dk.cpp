// David Klein
// CS 100
// Assignment 6
// Due 11/14/11

#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector.h>
#include <map.h>
#include <set.h>
#include <sys/types.h>

using namespace std;

#define each(I) \
	for( __typeof__ ((I).begin()) it=(I).begin(); it!=(I).end(); ++it)

int kill_children( map< string, set<string> >& id_map, string ppid, string root )
{
	if( id_map[ppid].empty() )				// if our set is empty then there is nothing to remove
		return 0;
	else if( !id_map[ppid].empty() )		// otherwise our set is not empty and we iterate through
	{										// and call kill on the children
		each( id_map[ppid] )
		{
			string kidpid = *it;
			kill_children( id_map, kidpid, root );
		}

		if( ppid == root )					// this makes sure we do not call kill on
			return 0;						//   our root process;
		string temp = "kill ";
		temp += ppid;						// create our kill command
		int ret = system( temp.c_str() );	// call kill on our ppid
		if( ret == 0 )						// return 0 on success
			return 0;
		else
			return -1;						// return -1 on failure
	}
}

int main( int argc, char* argv[] )
{
	string parent_id;									//PID user is looking for
	getline( cin, parent_id );

	FILE *rf = popen( "ps -eoppid -eopid", "r" );		// run popen to find out PIDs and PPIDs
	char buff[20];										// buffer to store individual lines
	vector<string> vec;									// vector where we will store our PIDs and PPIDs
	while (fgets(buff, sizeof(buff), rf) != NULL )		// put each PID and corresponding PPID into vector location
		vec.push_back( buff );

	vector<string> user_pids;							// we will store our list of PPIDs to PIDs without spaces
	map< string, set<string> > id_map;					// we will store our list of PPIDs to PID sets
	for( unsigned int i = 0; i < vec.size(); ++i )
	{
		string temp = vec[i];							// get original line of PPID and PID
		stringstream ss(temp);							// take out the spaces
		vector<string> temp_pids;

		while( ss >> temp )								// we input the two numbers into a temp vector
			temp_pids.push_back( temp );
		id_map[temp_pids[0]].insert(temp_pids[1]);		// we link the key and set
	}

	kill_children( id_map, parent_id, parent_id );		// now we have our tree of sets, we call kill on those sets

	return 0;
}
