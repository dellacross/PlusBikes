#include "matrixCells.hpp"
#include <queue>

using namespace std;

class Map
{
    public:
        /**
         * @brief Constructor
         */
        Map(int x = 0, int y = 0, int n = 0) : dimX(x), dimY(y), numElements(n){ initMapMatrix(); };

        /**
         * @brief Destructor
         */
        ~Map();

        /**
         * @brief initialize the map's matrix
         */
        void initMapMatrix();

        /**
         * @brief initialize the matrix that store the visitor's preference lists
         */
        void initVisitorsPreferenceMatrix();

        /**
         * @brief initialize the matrix that store the bike's preference lists
         */
        void initBikesPreferenceMatrix();

        /**
         * @brief initialize the vector that store the coordinates of the bikes
         */
        void initCoordOfBikesVector() { coordsOfBikes = new pair<int, int>[numElements]; };

        /**
         * @brief initialize the vector that store the coordinates of the visitors
         */
        void initCoordOfVisitorsVector() { coordsOfVisitors = new pair<int, int>[numElements]; };

        /**
         * @brief update the matrix's cell[i][j]
         *
         * @param x coordinate x of the cell
         * @param y coordinate y of the cell
         * @param obst if is a obtacle
         * @param bID if its a bike, store its bike's id
         * @param vID if its a visitor, store its visitor's id
         */
        void updateMapMatrixCell(int x, int y, bool obst, int bID, int vID);

        /**
         * @brief update the visitor's preference list adding the cells
         *
         * @param i i position on the matrix of the visitor
         * @param j j position on the matrix of the visitor
         * @param bikId id of the bike
         * @param bikePref visitor's preference in relation to the bike with id i
         */
        void updateVisitorsPreferenceMatrix(int i, int j, int bikeId, int bikePref)
        {
            visitorsPreferenceMatrix[i][j].first = bikeId;
            visitorsPreferenceMatrix[i][j].second = bikePref;
        };

        /**
         * @brief updates the bike matrix according to the distance of each bike with each visitor
         *
         */
        void updateBikesPreferenceMatrix();

        /**
         * @brief add the bike's coordinate on the vector that store the bikes coordinates
         *
         * @param id bike's id
         * @param i coordinate i of the bike
         * @param j coordinate j of the bike
         */
        void addCoordOfBike(int id, int i, int j);

        /**
         * @brief add the visitor's coordinate on the vector that store the visitors coordinates
         *
         * @param id visitor's id
         * @param i coordinate i of the visitor
         * @param j coordinate j of the visitor
         */
        void addCoordOfVisitor(int id, int i, int j);

        /**
         * @brief breadth search method to calculate the distance between each bike with each visitor
         *
         * @param bi i coordinate i of the bike
         * @param bj j coordinate j of the bike
         * @param vi i coordinate i of the visitor
         * @param vj j coordinate j of the visitor
         * @return int return the distance between the bike and the visitor
         */
        int BFS(int bi, int bj, int vi, int vj);

        /**
         * @brief check if the cell is accessible
         *
         * @param i i coordinate i of the cell
         * @param j j coordinate i of the cell
         * @return true if is accessible
         * @return false if is inaccessible
         */
        bool checkCell(int i, int j);

        /**
         * @brief set all cells as unvisited
         *
         */
        void allNoVisited();

        /**
         * @brief Gale-Shapley method (stable matching)
         *
         */
        void GaleShapley(string fileName, bool testRun);

        /**
         * @brief Return the chosen visitor by the bike
         *
         * @param idB bike's id
         * @param idVPropose visitor id that proposes
         * @param idVCurrent visitor id whom the bike's match
         * @return true if prefere the visitor who propose
         * @return false if prefere the current match
         */
        bool preference(int idB, int idVPropose, int idVCurrent);

        /**
         * @brief sorter
         **/
        void Sort(pair<int, int> **v, bool (*comp)(const pair<int, int> &x1, const pair<int, int> &x2)) { order(0, numElements - 1, v, comp); };

        /**
         * @brief get value of dimX 
        */
        int getDimX() {
            return this->dimX;
        };

        /**
         * @brief get value of dimY
        */
        int getDimY() {
            return this->dimY;
        };

        /**
         * @brief get number of elements on the map 
        */
        int getNumberOfElements() {
            return this->numElements;
        };

        /**
         * @brief return the map matrix
        */
        Cell** getMapMatrix() {
            return this->mapMatrix;
        }

        pair<int, int>** getVisitorsPreferenceMatrix() {
            return this->visitorsPreferenceMatrix;
        }

        pair<int, int>** getBikesPreferenceMatrix() {
            return this->bikesPreferenceMatrix;
        }

        pair<int, int> *getCoordsOfBikes() {
            return this->coordsOfBikes;
        }

        pair<int, int> *getCoordsOfVisitors() {
            return this->coordsOfVisitors;
        }

    private:
        int dimX;        // axis X of the map
        int dimY;        // axis Y of the map
        int numElements; // number of each element on the map

        pair<int, int> *coordsOfBikes;    // coordenates of each bike
        pair<int, int> *coordsOfVisitors; // coordenates of each visitor

        pair<int, int> **visitorsPreferenceMatrix;
        pair<int, int> **bikesPreferenceMatrix;
        Cell **mapMatrix;

        /*take partitions of the vector to order*/
        void partition(int left, int right, int &i, int &j, pair<int, int> *v, bool (*comp)(const pair<int, int> &x1, const pair<int, int> &x2));

        /*order the vector*/
        void order(int left, int right, pair<int, int> **v, bool (*comp)(const pair<int, int> &x1, const pair<int, int> &x2));

    friend class Tests;
};