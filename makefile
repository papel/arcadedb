

all: listing

listing:
	g++ src/*.cpp pugixml.o -o listing -I./pugixml-1.2/src/ -std=c++11
