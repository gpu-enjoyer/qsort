
MAKEFLAGS += s

CXXFLAGS += -std=c++98 #
CXXFLAGS += -Wall

all: clean build run

clean:
	clear
	rm -rf build

build: qsort.cpp
	mkdir build
	g++ $(CXXFLAGS) -o build/qsort qsort.cpp

run:
	./build/qsort
