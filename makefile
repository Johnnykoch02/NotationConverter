all: 
        g++ main.cpp -g -o run
        ./run
compile:
        g++ main.cpp .\src\NotationConverter.cpp -g -o run
run:
        ./run