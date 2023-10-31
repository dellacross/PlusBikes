#include <sstream>
#include <fstream>
#include <string>
#include "map.hpp"

bool BikeOrVisitor(char s) // true if is bike; false if is visitor;
{
    if (s == '0' || s == '1' || s == '2' || s == '3' || s == '4' || s == '5' || s == '6' || s == '7' || s == '8' || s == '9')
        return true;
    else
        return false;
}

int checkID(char s) // return the id
{
    if (s == '0' || s == 'a')
        return 1;
    else if (s == '1' || s == 'b')
        return 2;
    else if (s == '2' || s == 'c')
        return 3;
    else if (s == '3' || s == 'd')
        return 4;
    else if (s == '4' || s == 'e')
        return 5;
    else if (s == '5' || s == 'f')
        return 6;
    else if (s == '6' || s == 'g')
        return 7;
    else if (s == '7' || s == 'h')
        return 8;
    else if (s == '8' || s == 'i')
        return 9;
    else if (s == '9' || s == 'j')
        return 10;
    else
        return -1;
}

bool ifExists(int x, vector<int> q) // check if exists the element on the vector
{
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

int main(int argc, char *argv[])
{
    fstream file(argv[1]);

    if (file)
    {
        string line = "";
        vector<int> values = getDimensions(file);

        int n = values[0], x = values[1], y = values[2];

        Map map(x, y, n);

        for (int j = 0; j < x; j++)
        {
            getline(file, line);

            for (int k = 0; k < y; k++)
            {
                if (line[k] == '-')
                    map.updateMapMatrixCell(j, k, true, -1, -1);
                else if (line[k] == '*')
                    map.updateMapMatrixCell(j, k, false, -1, -1);
                else if (BikeOrVisitor(line[k]))
                {
                    map.updateMapMatrixCell(j, k, false, checkID(line[k]), -1);
                    map.addCoordOfBike(checkID(line[k]) - 1, j, k);
                }
                else if (!BikeOrVisitor(line[k]))
                {
                    map.updateMapMatrixCell(j, k, false, -1, checkID(line[k]));
                    map.addCoordOfVisitor(checkID(line[k]) - 1, j, k);
                }
            }
        }

        pair<int, int> vm[n][n];
        vector<int> auxV;
        for (int i = 0; i < n; i++)
        {
            int aux = 0;
            pair<int, int> av;
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
        map.GaleShapley();

        file.close();
    }
    else
        cout << "ERROR: FILE NOT FOUND!"
             << "\n";

    return 0;
}