#include "map.hpp"
#include "matrixCells.hpp"
#include "CppUTest/TestHarness.h"

TEST_GROUP(MapTests) {
    Map* map;

    void setup() {
        map = new Map(10, 10, 5);
        map->initMapMatrix();
    }

    void tearDown() {
        delete map;
    }
};

// test initialization of the map
TEST(MapTests, InitMapMatrix) {
    int _dimX = map->getDimX();
    int _dimY = map->getDimY();
    int _numElements = map->getNumberOfElements();

    CHECK_EQUAL(_dimX, 10);
    CHECK_EQUAL(_dimY, 10);
    CHECK_EQUAL(_numElements, 5);
}

// test if the matrix cell was correctly updated for obstacle case
TEST(MapTests, UpdateMapMatrixCell) {
    map->updateMapMatrixCell(2, 3, true, -1, -1);
    Cell** _map = map->getMapMatrix();
    CHECK_TRUE(_map[2][3].ifIsObstacle());
}

// test if the matrix cell was correctly updated for visitor case
TEST(MapTests, UpdateMapMatrixCell) {
    map->updateMapMatrixCell(0, 2, false, -1, 3);
    Cell** _map = map->getMapMatrix();
    CHECK_EQUAL(3, _map[2][3].getVisitorID());
}

// test if the matrix cell was correctly updated for bike case
TEST(MapTests, UpdateMapMatrixCell) {
    map->updateMapMatrixCell(1, 4, false, 2, -1);
    Cell** _map = map->getMapMatrix();
    CHECK_EQUAL(2, _map[1][4].getBikeID());
}