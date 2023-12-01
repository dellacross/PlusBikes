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
    map->updateMapMatrixCell(1, 4, false, 2, -1);
    map->updateMapMatrixCell(0, 2, false, -1, 3);
    Cell** _map = map->getMapMatrix();
    CHECK_TRUE(_map[2][3].ifIsObstacle());
    CHECK_EQUAL(3, _map[2][3].getVisitorID());
    CHECK_EQUAL(2, _map[1][4].getBikeID());
}

TEST(MapTests, cell) {
    Cell *cell;
    cell = new Cell(-1, 2, false, false);
    CHECK_FALSE(cell->ifIsObstacle());
    CHECK_FALSE(cell->ifVisited());
    CHECK_EQUAL(-1, cell->getBikeID());
    CHECK_EQUAL(2, cell->getBikeID());
}

TEST(MapTests, checkCell) {
    bool invalid_negative_1 = map->checkCell(-1, 3);
    bool invalid_negative_2 = map->checkCell(1, -3);
    bool invalid_out_of_range_1 = map->checkCell(11, 3);
    bool invalid_out_of_range_2 = map->checkCell(1, 13);

    CHECK_FALSE(invalid_negative_1);
    CHECK_FALSE(invalid_negative_2);
    CHECK_FALSE(invalid_out_of_range_1);
    CHECK_FALSE(invalid_out_of_range_2);
}