#include "map.hpp"
#include <sstream>
#include <fstream>

void Map::initMapMatrix()
{
    mapMatrix = new Cell *[dimX];
    for (int i = 0; i < dimX; i++)
        mapMatrix[i] = new Cell[dimY];

    initVisitorsPreferenceMatrix();
    initBikesPreferenceMatrix();
    initCoordOfBikesVector();
    initCoordOfVisitorsVector();
}

void Map::initVisitorsPreferenceMatrix()
{
    visitorsPreferenceMatrix = new pair<int, int> *[numElements];
    for (int i = 0; i < numElements; i++)
        visitorsPreferenceMatrix[i] = new pair<int, int>[numElements];
}

void Map::initBikesPreferenceMatrix()
{
    bikesPreferenceMatrix = new pair<int, int> *[numElements];
    for (int i = 0; i < numElements; i++)
        bikesPreferenceMatrix[i] = new pair<int, int>[numElements];
}

void Map::updateMapMatrixCell(int mapMatrixLinePosition, int mapMatrixColumnPosition, bool isObstacle, int bikeID, int visitorID)
{
    if (isObstacle == true)
        mapMatrix[mapMatrixLinePosition][mapMatrixColumnPosition].obstacle = isObstacle;
    else
    {
        if (bikeID == -1)
            mapMatrix[mapMatrixLinePosition][mapMatrixColumnPosition].visitorID = visitorID;
        else
            mapMatrix[mapMatrixLinePosition][mapMatrixColumnPosition].bikeID = bikeID;
    }
}

bool Map::checkCell(int i, int j) // verify if the adjacent cell has been visited or have a obstacle or the coordenates are invalid
{
    if (i < 0 || j < 0 || i >= dimX || j >= dimY)
        return false;
    else if (mapMatrix[i][j].visited == true || mapMatrix[i][j].obstacle == true)
        return false;
    else
        return true;
}

int auxLine[] = {-1, 0, 1, 0};
int auxCol[] = {0, 1, 0, -1};

int Map::BFS(int bi, int bj, int vi, int vj) // BFS method
{
    bool visitorFound = false;
    int updtNumOfPaths = 0, numOfPaths = 1, distance = 0; // numOfPaths: number of paths | uptdNumOfPaths: aux to update the number of paths
    queue<pair<int, int>> adjCells;                       // queue to store the adjacent cells
    pair<int, int> initCoord, moveAux;                    // initCoords are the initial coordenate of the bike | moveAux helps to create paths

    initCoord.first = bi;
    initCoord.second = bj;

    adjCells.push(initCoord);
    mapMatrix[bi][bj].visited = true;

    while (!adjCells.empty())
    {
        int auxI = adjCells.front().first;
        int auxJ = adjCells.front().second;
        adjCells.pop();

        if (auxI == vi && auxJ == vj)
        {
            visitorFound = true;
            break;
        }

        for (int k = 0; k < 4; k++)
        {
            int ai = auxI + auxLine[k];
            int aj = auxJ + auxCol[k];

            if (checkCell(ai, aj))
            {
                moveAux.first = ai;
                moveAux.second = aj;
                adjCells.push(moveAux);
                mapMatrix[ai][aj].visited = true;
                updtNumOfPaths++;
            }
        }

        numOfPaths--;

        if (numOfPaths == 0)
        {
            numOfPaths = updtNumOfPaths;
            updtNumOfPaths = 0;
            distance++;
        }
    }

    allNoVisited(); // turn all cells to not visited

    if (visitorFound)
        return distance;
    else
        return -1;
}

void Map::addCoordOfBike(int id, int i, int j)
{
    coordsOfBikes[id].first = i;
    coordsOfBikes[id].second = j;
}

void Map::addCoordOfVisitor(int id, int i, int j)
{
    coordsOfVisitors[id].first = i;
    coordsOfVisitors[id].second = j;
}

void Map::updateBikesPreferenceMatrix()
{
    int bi, bj, vi, vj;
    for (int i = 0; i < numElements; i++)
    {
        bi = coordsOfBikes[i].first;
        bj = coordsOfBikes[i].second;

        for (int j = 0; j < numElements; j++)
        {
            vi = coordsOfVisitors[j].first;
            vj = coordsOfVisitors[j].second;

            bikesPreferenceMatrix[i][j].first = j;
            bikesPreferenceMatrix[i][j].second = BFS(bi, bj, vi, vj);
        }
    }
}

void Map::allNoVisited() // turn all cells to unvisited
{
    for (int i = 0; i < dimX; i++)
        for (int j = 0; j < dimY; j++)
            if (mapMatrix[i][j].visited == true)
                mapMatrix[i][j].visited = false;
}

bool Map::preference(int idB, int propose, int current)
{
    for (int i = 0; i < numElements; i++)
    {
        if (bikesPreferenceMatrix[idB][i].first == propose)
            return true;

        if (bikesPreferenceMatrix[idB][i].first == current)
            return false;
    }
    return false;
}

string outputFilePath() {
    char number = '1';
    string file_path = "tests/current_output1.txt";
    while(true) {
        ifstream file(file_path);
        if(file.good()) {
            number++;
            string file_number = file_path.substr(file_path.length() - 4);
            file_path = file_path.substr(0, file_path.length() - 5) + number + file_number;
        }
        else 
            break;
    }
    return file_path;
}

void stableMatchingOutput(int *v, int n, string fileName, bool testRun)
{
    char fileNumber = fileName[fileName.length() - 4];
    string filePath = "tests/file";
    filePath = filePath + fileNumber + "_output.out";
    ofstream output_file(filePath);

    char aux = 'a';
    for (int i = 0; i < n; i++)
    {   
        if(!testRun) cout << aux << " " << v[i] << "\n"; // print the output
        if(testRun) output_file << aux << " " << v[i] << "\n";
        aux++;
    }
    output_file.close();
}

void Map::GaleShapley(string fileName, bool testRun)
{
    updateBikesPreferenceMatrix();

    // auto compare to sort the visitor's preference list correctly
    auto compare = [](const pair<int, int> &x1, const pair<int, int> &x2) -> bool
    {
        if (x1.second == x2.second)
            return x1.first > x2.first;
        return x1.second < x2.second;
    };
    // auto compare to sort the bike's preference list correctly
    auto compare2 = [](const pair<int, int> &x1, const pair<int, int> &x2) -> bool
    {
        if (x1.second == x2.second)
            return x1.first > x2.first;
        return x1.second > x2.second;
    };

    Sort(bikesPreferenceMatrix, compare2);   // sort the preferences list of the visitors
    Sort(visitorsPreferenceMatrix, compare); // sort the preferences list of the bikes

    int visitors[numElements]; // visitors[i] is the bike whom visitor i is matched
    int bikes[numElements];    // bikes[i] is the bike whom bike i is matched
    pair<int, int> proposes[numElements][numElements];
    int unmatchedVisitors = numElements;
    int visitorWhoProposes = 0, current_bike = 0;

    for (int i = 0; i < numElements; i++) // init visitors[], bikes[] and proposes[][]
    {
        visitors[i] = -1;
        bikes[i] = -1;
        for (int j = 0; j < numElements; j++)
        {
            proposes[i][j].first = visitorsPreferenceMatrix[i][j].first;
            proposes[i][j].second = 0;
        }
    }

    while (unmatchedVisitors > 0)
    {
        for (int i = 0; i < numElements; i++)
        {
            if (visitors[i] == -1) // pick the first unmatched visitor
            {
                visitorWhoProposes = i;
                break;
            }
        }

        for (int j = 0; j < numElements; j++) // pick the first bike on visitor's list to whom has not yet propose
        {
            if (proposes[visitorWhoProposes][j].second == 0)
            {
                current_bike = proposes[visitorWhoProposes][j].first;
                proposes[visitorWhoProposes][j].second = 1;
                break;
            }
        }

        if (bikes[current_bike] == -1) // if the current bike is unmatched
        {
            visitors[visitorWhoProposes] = current_bike;
            bikes[current_bike] = visitorWhoProposes;
            unmatchedVisitors--;
        }
        else
        {
            if (preference(current_bike, visitorWhoProposes, bikes[current_bike])) // compare the bike's preference between the visitor who propose and your current match
            {
                visitors[bikes[current_bike]] = -1;
                bikes[visitors[visitorWhoProposes]] = -1;
                bikes[current_bike] = visitorWhoProposes;
                visitors[visitorWhoProposes] = current_bike;
            }
        }
    }

    stableMatchingOutput(visitors, numElements, fileName, testRun); // print the output
}

void Map::partition(int left, int right, int &i, int &j, pair<int, int> *v, bool (*comp)(const pair<int, int> &x1, const pair<int, int> &x2))
{
    pair<int, int> pivot, aux;

    i = left;
    j = right;

    pivot = v[(i + j) / 2]; /*define the pivot*/

    do
    {
        while (comp(pivot, v[i]))
            i++;
        while (comp(v[j], pivot))
            j--;
        if (i <= j)
        {
            aux = v[i];
            v[i] = v[j];
            v[j] = aux;
            i++;
            j--;
        }
    } while (i <= j);
}

void Map::order(int left, int right, pair<int, int> **v, bool (*comp)(const pair<int, int> &x1, const pair<int, int> &x2))
{
    int i, j;
    for (int k = 0; k < numElements; k++)
    {
        partition(left, right, i, j, v[k], comp);
        if (left < j)
            order(left, j, v, comp);
        if (i < right)
            order(i, right, v, comp);
    }
}

Map::~Map()
{
    for(int i = 0; i < dimX; i++)
        delete[] mapMatrix[i];

    for(int i = 0; i < numElements; i++)
    {
        delete[] visitorsPreferenceMatrix[i];
        delete[] bikesPreferenceMatrix[i];
    }

    delete[] mapMatrix;
    delete[] visitorsPreferenceMatrix;
    delete[] bikesPreferenceMatrix;
    delete[] coordsOfBikes;
    delete[] coordsOfVisitors;
}