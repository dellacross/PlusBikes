#include "map.hpp"
#include "tests.hpp"
#include <sstream>
#include <fstream>
#include <cassert>

bool BikeOrVisitor(char s) { // true if is bike; false if is visitor;
    return (s >= '0' && s <= '9');
}

int getElementID(char character) { // return the element's id
    if (character < 58) return character - 47;
    return character - 96;
}

bool ifExists(int x, vector<int> q) { // check if exists the element on the vector
    int size = q.size();
    if (q.empty())
        return false;
    else
    {
        for (int i = 0; i < size; i++)
        {
            if (x == q[i])
                return true;
        }
        return false;
    }
}

vector<int> getDimensions(fstream &file) {
    string line = "";
    int xAxis, yAxis, numberOfElements;
    for (int i = 0; i < 2; i++) {
        getline(file, line);
        stringstream lineStream(line);

        if (i == 0)
            lineStream >> numberOfElements;
        else
            lineStream >> xAxis >> yAxis;
    }

    return {numberOfElements, xAxis, yAxis};
}

void setMapMatrixCells(fstream &file, Map &map, int xAxis, int yAxis, int numberOfElements) {
    string line = "";
    for (int lines = 0; lines < xAxis; lines++)
    {
        getline(file, line);

        for (int k = 0; k < yAxis; k++)
        {
            if (line[k] == '-')
                map.updateMapMatrixCell(lines, k, true, -1, -1);
            else if (line[k] == '*')
                map.updateMapMatrixCell(lines, k, false, -1, -1);
            else if (BikeOrVisitor(line[k]))
            {
                map.updateMapMatrixCell(lines, k, false, getElementID(line[k]), -1);
                map.addCoordOfBike(getElementID(line[k]) - 1, lines, k);
            }
            else if (!BikeOrVisitor(line[k]))
            {
                map.updateMapMatrixCell(lines, k, false, -1, getElementID(line[k]));
                map.addCoordOfVisitor(getElementID(line[k]) - 1, lines, k);
            }
        }
    }
}

// UNIT TESTS

int numberOfElements = -1, x_dimension = -1, y_dimension = -1;

// *1* 
void Tests::test_BikeOrVisitor(){
    assert(BikeOrVisitor('a') == false);
    assert(BikeOrVisitor('d') == false);    
    assert(BikeOrVisitor('2') == true);
    assert(BikeOrVisitor('3') == true);
}

// *2*
void Tests::test_ifExists() {
    vector<int> _vector;
    _vector.push_back(1);
    _vector.push_back(2);
    _vector.push_back(3);

    assert(ifExists(1, _vector) == true);
    assert(ifExists(2, _vector) == true);
    assert(ifExists(3, _vector) == true);
    assert(ifExists(4, _vector) == false);
}

// *3*
void Tests::test_getElementID() {
    assert(getElementID('0') == 1);
    assert(getElementID('2') == 3);
    assert(getElementID('a') == 1);
    assert(getElementID('b') == 2);
}

// *4* 
void Tests::test_InitMapMatrix(Map* map) {
    assert(map->dimX == 4);
    assert(map->dimY == 4);
    assert(map->numElements == 3);
}

// *5* 
void Tests::test_cell_constructor() {
    Cell *cell;
    cell = new Cell(-1, 2, false, false);
    assert(cell->obstacle == false);
    assert(cell->visited == false);
    assert(cell->bikeID == -1);
    assert(cell->visitorID == 2);
}

// *6*
void Tests::test_UpdateMapMatrixCell(Map* map) {
    Map* _map = map;
    _map->updateMapMatrixCell(2, 3, true, -1, -1);
    _map->updateMapMatrixCell(1, 4, false, 2, -1);
    _map->updateMapMatrixCell(0, 2, false, -1, 3);

    assert(_map->mapMatrix[2][3].obstacle == true);
    assert(_map->mapMatrix[1][4].bikeID == 2);
    assert(_map->mapMatrix[0][2].visitorID == 3);
}

// *7*
void Tests::test_checkCell_out_of_range(Map* map) {
    Map* _map = map;
    bool invalid_out_of_range_1 = _map->checkCell(11, 3);
    bool invalid_out_of_range_2 = _map->checkCell(1, 13);

    assert(invalid_out_of_range_1 == false);
    assert(invalid_out_of_range_2 == false);
}

// *8*
void Tests::test_checkCell_negative(Map* map) {
    bool invalid_negative_1 = map->checkCell(-1, 3);
    bool invalid_negative_2 = map->checkCell(1, -3);

    assert(invalid_negative_1 == false);
    assert(invalid_negative_2 == false);
}

// *9*
void Tests::test_initVisitorsPreferenceMatrix(Map* map) {
    Map* _map = map;
    _map->initVisitorsPreferenceMatrix();
    bool _nullptr = false;
    if(_map->visitorsPreferenceMatrix == nullptr) _nullptr = true;
    assert(_nullptr == false);
}

// *10* 
void Tests::test_initBikesPreferenceMatrix(Map* map) {
    Map* _map = map;
    _map->initBikesPreferenceMatrix();
    bool _nullptr = false;
    if(_map->bikesPreferenceMatrix == nullptr) _nullptr = true;
    assert(_nullptr == false);
}

// *11* 
void Tests::test_initCoordOfBikesVector(Map* map) {
    Map* _map = map;
    _map->initCoordOfBikesVector();
    bool _nullptr = false;
    if(_map->coordsOfBikes == nullptr) _nullptr = true;
    assert(_nullptr == false);
}

// *12* 
void Tests::test_initCoordOfVisitorsVector(Map* map) {
    Map* _map = map;
    _map->initCoordOfVisitorsVector();
    bool _nullptr = false;
    if(_map->coordsOfVisitors == nullptr) _nullptr = true;
    assert(_nullptr == false);
}

// *13* 
void Tests::test_allNoVisited(Map* map) {
    Map* _map = map;
    _map->mapMatrix[0][0].visited = true;
    _map->mapMatrix[1][2].visited = true;
    _map->mapMatrix[1][0].visited = true;
    _map->allNoVisited();
    int x_dimension = map->dimX, y_dimension = map->dimY;
    bool ifExistVisitedCell_map = false;

    for(int i = 0; i < x_dimension; i++) {
        for(int j = 0; j < y_dimension; j++) {
            if(_map->mapMatrix[i][j].visited == true)
                ifExistVisitedCell_map = true;
        }
    }

    assert(ifExistVisitedCell_map == false);
}

// *14* 
void Tests::test_updateVisitorsPreferenceMatrix(Map* map) {
    Map* _map = map;
    _map->initVisitorsPreferenceMatrix();
    _map->updateVisitorsPreferenceMatrix(0,0,0,2);
    _map->updateVisitorsPreferenceMatrix(0,1,0,0);
    _map->updateVisitorsPreferenceMatrix(0,2,0,1);
    _map->updateVisitorsPreferenceMatrix(1,0,1,1);
    _map->updateVisitorsPreferenceMatrix(1,1,1,0);
    _map->updateVisitorsPreferenceMatrix(1,2,1,2);
    _map->updateVisitorsPreferenceMatrix(2,0,3,0);
    _map->updateVisitorsPreferenceMatrix(2,1,3,2);
    _map->updateVisitorsPreferenceMatrix(2,2,3,1);

    pair<int,int>** _visitorsPreferenceMatrix = _map->visitorsPreferenceMatrix;

    assert(_visitorsPreferenceMatrix[0][0].second == 2);
    assert(_visitorsPreferenceMatrix[0][1].second == 0);
    assert(_visitorsPreferenceMatrix[0][2].second == 1);
    assert(_visitorsPreferenceMatrix[1][0].second == 1);
    assert(_visitorsPreferenceMatrix[1][1].second == 0);
    assert(_visitorsPreferenceMatrix[1][2].second == 2);
    assert(_visitorsPreferenceMatrix[2][0].second == 0);
    assert(_visitorsPreferenceMatrix[2][1].second == 2);
    assert(_visitorsPreferenceMatrix[2][2].second == 1);
}

// *15* 
void Tests::test_addCoordOfBike(Map* map) {
    Map* _map = map;
    _map->addCoordOfBike(0,2,2);
    _map->addCoordOfBike(1,0,3);
    _map->addCoordOfBike(2,3,1);

    pair<int, int> *coordsOfBikes = map->coordsOfBikes;

    assert(coordsOfBikes[0].first == 2);
    assert(coordsOfBikes[0].second == 2);
    assert(coordsOfBikes[1].first == 0);
    assert(coordsOfBikes[1].second == 3);
    assert(coordsOfBikes[2].first == 3);
    assert(coordsOfBikes[2].second == 1);
}

void exec_system(string filePath) {
    fstream file(filePath);
    if (file)
    {
        string line = "";
        vector<int> values = getDimensions(file);

        int n = values[0], x = values[1], y = values[2];

        Map map(x, y, n);

        setMapMatrixCells(file, map, x, y, n);
        pair<int, int> vm[n][n];
        vector<int> auxV;
        for (int i = 0; i < n; i++)
        {
            int aux = 0;
            getline(file, line);
            stringstream auxLine(line);

            for (int j = 0; j < n; j++)
            {
                auxLine >> aux;
                vm[i][j].first = j;
                vm[i][j].second = aux;
            }
        }

        int g = -1, gpos = -1;
        //cout << "n:" << n << "\n";
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                for (int k = 0; k < n; k++)
                {
                    if (vm[i][k].second >= g && !ifExists(k, auxV))
                    {
                        //cout << "i:" << i << " k:" << k << "\n";
                        g = vm[i][k].second;
                        gpos = k;
                    }
                }
                auxV.push_back(gpos);
                map.updateVisitorsPreferenceMatrix(i, j, gpos, g);
                g = -1;
                gpos = -1;
            }
            auxV.clear();
        }
        
        map.GaleShapley(filePath, true);
        file.close();
    }
    else
        cout << "ERROR: FILE NOT FOUND!"
             << "\n";
}

void compareFiles(string fileName) {
    char fileNumber = fileName[fileName.length() - 4];

    string outputFilePath = "tests/file";
    outputFilePath = outputFilePath + fileNumber + "_output.out";

    string expectedOutputFilePath = "tests/teste";
    expectedOutputFilePath = expectedOutputFilePath + fileNumber + ".out";
    
    ifstream outputFile(outputFilePath, ios::binary | ios::ate);
    ifstream expectedOutputFile(expectedOutputFilePath, ios::binary | ios::ate);

    bool equal = true;

    if(outputFile.tellg() != expectedOutputFile.tellg())
        equal = false;

    outputFile.seekg(0);
    expectedOutputFile.seekg(0);

    const size_t bufferSize = 4096;
    vector<char> buffer1(bufferSize);
    vector<char> buffer2(bufferSize);

    do {
        outputFile.read(buffer1.data(), bufferSize);
        expectedOutputFile.read(buffer2.data(), bufferSize);

        if(buffer1 != buffer2) 
            equal = false;
            
    } while (outputFile.good() && expectedOutputFile.good());

    outputFile.close();
    expectedOutputFile.close();
    
    assert(equal == true);
}

int main(int argc, char** argv) {

    Tests tests;
    Map* map = new Map(4, 4, 3);
    map->initMapMatrix();

    cout << "Starting unit tests..." << "\n";

    // *1*
    tests.test_BikeOrVisitor();

    // *2*
    tests.test_ifExists();

    // *3*
    tests.test_getElementID();

    // *4* 
    tests.test_InitMapMatrix(map);

    // *5* 
    tests.test_cell_constructor();

    // *6*
    tests.test_UpdateMapMatrixCell(map);

    // *7*
    tests.test_checkCell_out_of_range(map);

    // *8*
    tests.test_checkCell_negative(map);

    // *9*
    tests.test_initVisitorsPreferenceMatrix(map);

    // *10* 
    tests.test_initBikesPreferenceMatrix(map);

    // *11* 
    tests.test_initCoordOfBikesVector(map);

    // *12* 
    tests.test_initCoordOfVisitorsVector(map);

    // *13* 
    tests.test_allNoVisited(map);

    // *14* 
    tests.test_updateVisitorsPreferenceMatrix(map);

    // *15* 
    tests.test_addCoordOfBike(map);

    cout << "Success! All unit tests passed!" << "\n";
    
    cout << "Starting system tests..." << "\n";

    exec_system(argv[1]);
    compareFiles(argv[1]);

    cout << "Success! All system tests passed!" << "\n";
    cout << "All tests passed for '" << argv[1] << "' file!\n";
    

    return 0;
}