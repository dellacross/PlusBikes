#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class Cell {
    public:
        Cell(int bID = -1, int vID = -1, bool obst = false, bool visited = false) : bikeID(bID), visitorID(vID), obstacle(obst){};

    private:
        int bikeID; 
        int visitorID;
        bool obstacle;
        bool visited;

    friend class Map;
    friend class Tests;
};