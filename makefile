#makefile for COP4530_P6_Hashtables
#referenced from Project 1
CC = g++ -std=c++11

all: proj6.x

proj6.x: proj6.cpp passserver.h passserver.cpp hashtable.h hashtable.hpp base64.h base64.cpp
	$(CC) -o proj6.x proj6.cpp passserver.cpp base64.cpp

clean: 
	rm -f *.o proj6.x
