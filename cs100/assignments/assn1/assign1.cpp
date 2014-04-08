// David Klein
// CS 100
// Assignment 1
// Oct 2, 2011

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <langinfo.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <list>

#include <locale.h>
#include <iostream>

using namespace std;

#define each(I) \
	for( typof((I).begin()) it=(I).begin(); it!=(I).end(); ++i)

/*
DIR *opendir(const char *dirname);
struct dirent *readdir(DIR *dir);
int closedir(DIR *dir);
int lstat(const char *path, struct stat *buf);*/

int visit( string root )
{
	DIR *dirp;

	if( !(dirp = opendir(root.c_str() ) ) )
	{
		cerr << "cannot open directory" << root << endl;
		return -1;
	}

	list <string> files;
	list <string> hard_subdirectories;

	while( dirent *dp = readdir(dirp) )
	{
		string s = dp->d_name;
		if( s == "." || s == ".." )
			continue;
		files.push_back(s);
		if( (dp->d_type & DT_DIR) && !(dp->d_type & DT_LNK) )
			hard_subdirectories.push_back( root + "/" + s);
	}

	closedir(dirp);

	files.sort();

/*	cout << root << ":" << endl;
	cout << "total";
	int size = 0;
	each(files)
	{
		struct stat st;
		string filename = root + "/" + *it;
		if (lstat( filename.c_str(), &st) == 0 )
		{
		//	cerr << "filename.c_str() error";
		//	return -1;
			size += st.blocks;
		}
		cout << size/2;
	}*/

	return 0;
}

int main( int argc, char *argv[] )
{
	return visit( argc > 0 ? argv[1] : "." );
}
