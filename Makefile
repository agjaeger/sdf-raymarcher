
CPP_FILES = $(wildcard source/*.cpp)

compile:
	clang++ -std=c++11 -o build/sdf $(CPP_FILES) -Iinclude/
	
run:
	./build/sdf
