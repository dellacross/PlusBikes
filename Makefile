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

EXE = $(BIN)/tp02 
EXE_TESTS = $(BIN)/testRunner

all: $(EXE) $(EXE_TESTS) 

$(OBJ)/map.o: $(HDRS) $(SRC)/map.cpp
	$(CC) $(CFLAGS) -c -o $(OBJ)/map.o $(SRC)/map.cpp

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -c -o $(OBJ)/main.o $(SRC)/main.cpp 

$(OBJ)/testRunner.o: $(HDRS) $(TESTS)/testRunner.cpp
	$(CC) $(CFLAGS) -c -o $(OBJ)/testRunner.o $(TESTS)/testRunner.cpp

$(BIN)/testRunner: $(OBJ)/map.o
	g++ -o bin/testRunner $(CFLAGS) $(TESTS)/testRunner.cpp $(OBJ)/map.o $(LIBS)

$(BIN)/tp02: $(OBJS)
	$(CC) -o $(BIN)/tp02 $(CFLAGS) $(OBJS) $(LIBS)

clean:
	rm $(OBJS) $(BIN)/* $(TESTS)/*_output.out