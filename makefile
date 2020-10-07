CFLAGS  = -g -Wall
all: main.cpp tst.cpp
	g++ $(CFLAGS) -std=c++11 -o project1.out main.cpp tst.cpp