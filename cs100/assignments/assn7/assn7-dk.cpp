// David Klein
// CS 100
// Assignment 7
// Due 11/21/11

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <set.h>

using namespace std;

#define each(I) \
	for( __typeof__ ((I).begin()) it=(I).begin(); it!=(I).end(); ++it)

int open_dir( string dir, set<string> &sub_dirs )
{
	DIR *dp;
    struct dirent *dirp;

	if((dp  = opendir(dir.c_str())) == NULL)
	{
		cout << "Error(" << errno << ") opening " << dir << endl;
	 	return errno;
	}

    while ((dirp = readdir(dp)) != NULL)			// add individual files onto the set
    {
     	sub_dirs.insert(string(dirp->d_name));
    }

    closedir(dp);
    return 0;
}

void remove_dir( string dir, string sub_dir )
{
	string cmd = "rm -rf ";
	dir += sub_dir;
	cmd += dir;
	system( cmd.c_str() );				//remove the directory

	cmd = "mkdir ";
	cmd += dir;
	system( cmd.c_str() );				//recreate the directory
}

int test_input( string program_file, string test_file, string source_dir, string dest_dir )
{
	string file_source = source_dir + "/" + test_file;		// combine our source directory and test filename
	string file_dest = dest_dir + "/" + test_file;			// combine our destination directory and test filename

	string cmd;
	cmd = program_file + " < " + file_source + " > " + file_dest;	// form the i/o direction for using a program file

	if( system( cmd.c_str() ) != 0 )
		return 1;
	else
		return 0;
}

int test_diff( string test_file, string corrects_dir, string outputs_dir )
{
	string corrects_file = corrects_dir + "/" + test_file;	// combine our "corrects" directory and test filename
	string outputs_file = outputs_dir + "/" + test_file;	// combine our "outputs" directory and test filename

	string cmd = "diff " + corrects_file + " " + outputs_file;	// form the "diff" command

	system( cmd.c_str() );

	return 0;
}

int main( int argc, char* argv[] )
{
	string temp;
	getline( cin, temp );				// Get the file and test directory
	stringstream ss( temp );

	vector<string> vec;					// holds our test filename and directory
 	while( ss >> temp )
 		vec.push_back( temp );			// vec[0] is the program file and vec[1] is the directory

 	set<string> sub_dirs;
	if( open_dir(vec[1], sub_dirs) != 0 )	// if cannot open directory - exit
		return -1;

	temp = "/outputs";
	remove_dir( vec[1], temp );		//remove our ouputs directory and recreate it

	temp = "/errs";
	remove_dir( vec[1], temp );		//remove our errs directory and recreate it
////////////////////////////////
	set<string> inputs_files;		// holds the list of files in our inputs subdir
	temp = vec[1] + "/inputs";
	open_dir( temp, inputs_files );

	string dest_dir = vec[1] + "/outputs";
	string source_dir = temp;

	inputs_files.erase(".");
	inputs_files.erase("..");

	each( inputs_files )			// creates a output file for each input file
		test_input( vec[0], *it, source_dir, dest_dir );
////////////////////////////////
	set<string> corrects_files;		// holds the list of files in our corrects subdir
	temp = vec[1] + "/corrects";
	open_dir( temp, corrects_files );

	corrects_files.erase(".");		// remove the . and .. at the beginning of the list
	corrects_files.erase("..");

	string outputs_dir = vec[1] + "/outputs";
	string corrects_dir = temp;

	each( corrects_files )			// test for each corrects file to a same named outputs file
	{
		if( test_diff( *it, corrects_dir, outputs_dir ) != 0 )
			exit(0);				// exit if the files are different
	}
////////////////////////////////

	return 0;
}
