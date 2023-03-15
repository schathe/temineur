all:
	g++ *.cpp src/myLib/*.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system -I /src/myLibHeaders/myLib.h

run: 
	make all
	./main

debug: 
	g++ --std=c++11 -g -o maindebug *.cpp src/myLib/*.cpp ddd debug
