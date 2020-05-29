

all: listing

listing:
	g++ src/*.cpp pugixml.o -o listing -I./pugixml/src/ -std=c++11
