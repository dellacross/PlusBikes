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
        map = new Map(3, 4, 4);
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

    CHECK_EQUAL(_numberOfElements, 5);
    CHECK_EQUAL(_dimX, 4);
    CHECK_EQUAL(_dimY, 5);
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
    CHECK_FALSE(ifExists(4, _vector));
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
    CHECK_EQUAL(2, _map[1][4].getBikeID());
    CHECK_EQUAL(3, _map[0][2].getVisitorID());
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
TEST(MapTests, allNoVisited) {
    map->allNoVisited();
    Cell** _map1 = map->getMapMatrix();
    Cell** _map2 = _map1;
    _map2[0][0].setVisited(true);
    int x_dimension = map->getDimX(), y_dimension = map->getDimY();
    bool ifExistVisitedCell_map1 = false, ifExistVisitedCell_map2 = false;

    for(int i = 0; i < x_dimension; i++) {
        for(int j = 0; j < y_dimension; j++) {
            if(_map1[i][j].ifVisited())
                ifExistVisitedCell_map1 = true;
            if(_map2[i][j].ifVisited())
                ifExistVisitedCell_map2 = true;
        }
    }

    CHECK_FALSE(ifExistVisitedCell_map1);
    CHECK_TRUE(ifExistVisitedCell_map2);
}

// *14*
TEST(MapTests, updateVisitorsPreferenceMatrix) {
    map->initVisitorsPreferenceMatrix();
    map->updateVisitorsPreferenceMatrix(0,0,0,2);
    map->updateVisitorsPreferenceMatrix(0,1,0,0);
    map->updateVisitorsPreferenceMatrix(0,2,0,1);
    map->updateVisitorsPreferenceMatrix(1,0,1,1);
    map->updateVisitorsPreferenceMatrix(1,1,1,0);
    map->updateVisitorsPreferenceMatrix(1,2,1,2);
    map->updateVisitorsPreferenceMatrix(2,0,3,0);
    map->updateVisitorsPreferenceMatrix(2,1,3,2);
    map->updateVisitorsPreferenceMatrix(2,2,3,1);

    pair<int,int>** _visitorsPreferenceMatrix = map->getVisitorsPreferenceMatrix();
    CHECK_EQUAL(_visitorsPreferenceMatrix[0][0].second, 2);
    CHECK_EQUAL(_visitorsPreferenceMatrix[0][1].second, 0);
    CHECK_EQUAL(_visitorsPreferenceMatrix[0][2].second, 1);
    CHECK_EQUAL(_visitorsPreferenceMatrix[1][0].second, 1);
    CHECK_EQUAL(_visitorsPreferenceMatrix[1][1].second, 0);
    CHECK_EQUAL(_visitorsPreferenceMatrix[1][2].second, 2);
    CHECK_EQUAL(_visitorsPreferenceMatrix[2][0].second, 0);
    CHECK_EQUAL(_visitorsPreferenceMatrix[2][1].second, 2);
    CHECK_EQUAL(_visitorsPreferenceMatrix[2][2].second, 1);
}

// *15*
TEST(MapTests, addCoordOfBike) {
    map->addCoordOfBike(0,2,2);
    map->addCoordOfBike(1,0,3);
    map->addCoordOfBike(2,3,1);

    pair<int,int>* _coordsOfBikes = map->getCoordsOfBikes();

    CHECK_EQUAL(_coordsOfBikes[0].first, 2);
    CHECK_EQUAL(_coordsOfBikes[0].second, 2);
    CHECK_EQUAL(_coordsOfBikes[1].first, 0);
    CHECK_EQUAL(_coordsOfBikes[1].second, 3);
    CHECK_EQUAL(_coordsOfBikes[2].first, 3);
    CHECK_EQUAL(_coordsOfBikes[2].second, 1);
}