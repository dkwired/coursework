// David Klein
// CS 153
// Project 3

//This website helped me understand a bit on pipes: http://infohost.nmt.edu/~eweiss/222_book/222_book/0201433079/ch15.html

#include "popen.h"

inline FILE* Popen( const string command, const string direction )
{
	int pfd[2];
	FILE* fp;
	string path;
	char str[128];

	pipe(pfd);

	switch( pid_t kid = fork() )
	{
		case -1: // error
			return( NULL );
		case 0: // you're the child
			if( direction == "r" )
			{
				close( pfd[0] );
				dup2( pfd[1], STDOUT_FILENO );
				close( pfd[1] );
			}
			else if( direction == "w" )
			{
				close( pfd[1] );
				dup2( pfd[0], STDIN_FILENO );
				close( pfd[0] );
			}
			path = "/bin/" + command;
			execlp( path.c_str(), command.c_str(), NULL );
		default: // you're the parent
			if( direction == "r" )
			{
				close( pfd[1] );
				fp = fdopen(pfd[0], direction.c_str());
			}
			else if( direction == "w" )
			{
				close( pfd[0] );
				fp = fdopen(pfd[1], direction.c_str());
			}
	}	
	return( fp );
}

inline int Pclose( FILE* fp )
{
	int status;
	pid_t kid;

	if( fclose(fp) == EOF ) return -1;	

	while(wait(&status) < 0)
		if(errno != EINTR)
			return -1;
}

int main( int argc, char **argv)
{
	FILE* f = Popen( "ls", "w" );

	if( f == NULL )
	{
		printf("popen failed.\n");
		exit(-1);
	}

	string s = "hello, world\n";
	fwrite( s.c_str(), 1, s.size(), f);
	Pclose(f);

	return 0;
}
