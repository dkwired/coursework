# To generate the executeable, type "make all" or "make" at the command
# prompt.
# To remove the executeable and any extraneous files type "make clean" at
# the command prompt.

# Variables make your life easy

# The compiler and compiler options
CXX= g++
CXXFLAGS= -g -W -Wall -Werror -ansi -pedantic -I/usr/csshare/include

#Targets
#Compile link objects
all:  #$(OBJECTS)
    $(CXX) $(CXXFLAGS) -o assn3-dk assn3-dk.cpp

#Remove unnecessary files
clean:
    rm -f *~ *.o *.out assn3-dk assn3-dk.zip
