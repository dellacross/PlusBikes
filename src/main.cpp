#include <sstream>
#include <fstream>
#include <string>
#include "map.hpp"

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

int main(int argc, char *argv[])
{
    fstream file(argv[1]);

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
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                for (int k = 0; k < n; k++)
                {
                    if (vm[i][k].second >= g && !ifExists(k, auxV))
                    {
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
        map.GaleShapley(argv[1], false);

        file.close();
    }
    else
        cout << "ERROR: FILE NOT FOUND!"
             << "\n";

    return 0;
}