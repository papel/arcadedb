

all: listador

listador:
	g++ src/*.cpp pugixml.o -o listador -I./pugixml-1.2/src/ -std=c++11
