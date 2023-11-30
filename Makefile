CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/map.o $(OBJ)/main.o
HDRS = $(INC)/map.hpp 
CFLAGS = -Wall -I$(INC) -Og -g -std=c++11

EXE = $(BIN)/tp01

all: $(EXE)

$(OBJ)/map.o: $(HDRS) $(SRC)/map.cpp
	$(CC) $(CFLAGS) -c -o $(OBJ)/map.o $(SRC)/map.cpp

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -c -o $(OBJ)/main.o $(SRC)/main.cpp 

$(BIN)/tp01: $(OBJS)
	$(CC) -o $(BIN)/tp01 $(CFLAGS) $(OBJS) $(LIBS)

clean:
	rm $(OBJS) $(BIN)/tp01