#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class Cell
{
public:
    Cell(int bID = -1, int vID = -1, bool obst = false, bool visited = false) : bikeID(bID), visitorID(vID), obstacle(obst){};

    bool ifIsObstacle() {
        return this->obstacle;
    }

    int getBikeID() {
        return this->bikeID;
    }

    int getVisitorID() {
        return this->visitorID;
    }

    bool ifVisited() {
        return this->visited;
    }

    void setVisited(bool _visited) {
        this->visited = _visited;
    }

private:
    int bikeID; 
    int visitorID;
    bool obstacle;

    bool visited;

    friend class Map;
};