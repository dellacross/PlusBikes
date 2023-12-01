#include "map.hpp"
#include "matrixCells.hpp"
#include <sstream>
#include <fstream>
#include "CppUTest/TestHarness.h"

vector<int> getDimensions(fstream &file);
bool BikeOrVisitor(char s);
int getElementID(char character);
bool ifExists(int x, vector<int> q);

TEST_GROUP(MapTests) {
    Map* map;

    void setup() {
        map = new Map(12, 10, 10);
        map->initMapMatrix();
    }

    void tearDown() {
        delete map;
    }
};
// *1*
TEST(MapTests, getDimensions) {
    string line = "";
    fstream file("/tests/teste1.txt");
    vector<int> values = getDimensions(file);

    int _numberOfElements = values[0], _dimX = values[1], _dimY = values[2];

    CHECK_EQUAL(_numberOfElements, 12);
    CHECK_EQUAL(_dimX, 10);
    CHECK_EQUAL(_dimY, 10);
}

// *2*
TEST(MapTests, ifExists) {
    vector<int> _vector;
    _vector.push_back(1);
    _vector.push_back(2);
    _vector.push_back(3);

    CHECK_TRUE(ifExists(1, _vector));
    CHECK_TRUE(ifExists(2, _vector));
    CHECK_TRUE(ifExists(3, _vector));
}

// *3*
TEST(MapTests, getElementID) {
    CHECK_EQUAL(getElementID('0'), 1);
    CHECK_EQUAL(getElementID('5'), 6);
    CHECK_EQUAL(getElementID('9'), 10);
    CHECK_EQUAL(getElementID('a'), 1);
    CHECK_EQUAL(getElementID('d'), 5);
}

// *4*
TEST(MapTests, InitMapMatrix) {
    int _dimX = map->getDimX();
    int _dimY = map->getDimY();
    int _numElements = map->getNumberOfElements();

    CHECK_EQUAL(_dimX, 10);
    CHECK_EQUAL(_dimY, 10);
    CHECK_EQUAL(_numElements, 12);
}

// *5* 
TEST(MapTests, cell) {
    Cell *cell;
    cell = new Cell(-1, 2, false, false);
    CHECK_FALSE(cell->ifIsObstacle());
    CHECK_FALSE(cell->ifVisited());
    CHECK_EQUAL(-1, cell->getBikeID());
    CHECK_EQUAL(2, cell->getBikeID());
}

// *6*
TEST(MapTests, UpdateMapMatrixCell) {
    map->updateMapMatrixCell(2, 3, true, -1, -1);
    map->updateMapMatrixCell(1, 4, false, 2, -1);
    map->updateMapMatrixCell(0, 2, false, -1, 3);
    Cell** _map = map->getMapMatrix();
    CHECK_TRUE(_map[2][3].ifIsObstacle());
    CHECK_EQUAL(3, _map[2][3].getVisitorID());
    CHECK_EQUAL(2, _map[1][4].getBikeID());
}

// *7*
TEST(MapTests, checkCell) {
    bool invalid_out_of_range_1 = map->checkCell(11, 3);
    bool invalid_out_of_range_2 = map->checkCell(1, 13);
    bool invalid_out_of_range_3 = map->checkCell(-1, 3);
    bool invalid_out_of_range_4 = map->checkCell(1, -3);

    CHECK_FALSE(invalid_out_of_range_1);
    CHECK_FALSE(invalid_out_of_range_2);
    CHECK_FALSE(invalid_out_of_range_3);
    CHECK_FALSE(invalid_out_of_range_4);
}

// *8*
TEST(MapTests, checkCell) {
    bool invalid_negative_1 = map->checkCell(-1, 3);
    bool invalid_negative_2 = map->checkCell(1, -3);

    CHECK_FALSE(invalid_negative_1);
    CHECK_FALSE(invalid_negative_2);
}

// *9*
TEST(MapTests, initVisitorsPreferenceMatrix) {
    map->initVisitorsPreferenceMatrix();
    pair<int, int>** _visitorMatrix = map->getVisitorsPreferenceMatrix();
    bool _nullptr = false;
    if(_visitorMatrix == nullptr) _nullptr = true;
    CHECK_FALSE(_nullptr);
}

// *10*
TEST(MapTests, initBikesPreferenceMatrix) {
    map->initBikesPreferenceMatrix();
    pair<int, int>** _bikesMatrix = map->getBikesPreferenceMatrix();
    bool _nullptr = false;
    if(_bikesMatrix == nullptr) _nullptr = true;
    CHECK_FALSE(_nullptr);
}

// *11*
TEST(MapTests, initCoordOfBikesVector) {
    map->initCoordOfBikesVector();
    pair<int, int>* _coordsOfBikes = map->getCoordsOfBikes();
    bool _nullptr = false;
    if(_coordsOfBikes == nullptr) _nullptr = true;
    CHECK_FALSE(_nullptr);
}

// *12*
TEST(MapTests, initCoordOfVisitorsVector) {
    map->initCoordOfVisitorsVector();
    pair<int, int>* _coordsOfVisitors = map->getCoordsOfVisitors();
    bool _nullptr = false;
    if(_coordsOfVisitors == nullptr) _nullptr = true;
    CHECK_FALSE(_nullptr);
}

// *13*


// *14*


// *15*

