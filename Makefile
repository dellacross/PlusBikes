CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
TESTS = tests
OBJS = $(OBJ)/map.o $(OBJ)/main.o
HDRS = $(INC)/map.hpp 
CFLAGS = -Wall -I$(INC) -Og -g -std=c++11

EXE_TESTS = $(BIN)/testRunner

all: $(EXE_TESTS) 

$(OBJ)/map.o: $(HDRS) $(SRC)/map.cpp
	$(CC) $(CFLAGS) -c -o $(OBJ)/map.o $(SRC)/map.cpp

$(OBJ)/testRunner.o: $(HDRS) $(TESTS)/testRunner.cpp
	$(CC) $(CFLAGS) -c -o $(OBJ)/testRunner.o $(TESTS)/testRunner.cpp

$(BIN)/testRunner: $(OBJ)/map.o
	g++ -o bin/testRunner $(CFLAGS) $(TESTS)/testRunner.cpp $(OBJ)/map.o $(LIBS)

clean:
	rm $(OBJS) $(BIN)/* $(TESTS)/*_output.out