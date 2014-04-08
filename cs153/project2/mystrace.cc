// David Klein
// 860880864
// CS 153
// Project 2
// Spring 2013

#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/reg.h>
#include <iostream>
#include <fstream>
#include <vector.h>

using namespace std;

int main(int argc, char* argv[])
{
	pid_t child;
	long original_rax;

	child = fork();

	if( child == -1 )
	{
		perror("fork");
		exit(1);
	}	
	if(child == 0) 
	{
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		execvp(argv[1], argv + 1);
	}
	else 
	{
		wait(NULL);
		original_rax = ptrace(PTRACE_PEEKUSER, child, 8 * ORIG_RAX, NULL);
		ptrace(PTRACE_CONT, child, NULL, NULL);
	}

	printf("Ran command: %ld\n", original_rax);
	ptrace(PTRACE_KILL, child, NULL, NULL);
	
	ifstream file;
	file.open("syscall_mapping");

	vector<string> array;
	string temp;
	while( !file.eof() )
	{
		file >> temp;
		file >> temp;
		array.push_back(temp);
	}
	file.close();

	cout << "Child made a system call: " << original_rax << " " << array[original_rax];

	return 0;
}
