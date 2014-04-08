#ifndef POPEN_H
#define POPEN_H

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <cassert>
#include <sstream>
#include <fstream>

using namespace std;

FILE* Popen( const string command, const string direction );
int Pclose(FILE* fp);

#endif
