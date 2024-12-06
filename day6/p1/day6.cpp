#include <iostream>
#include <fstream>
#include <string>
#include <utility>

using namespace std;

string key = "input.txt";

const int SIZE = 130;

int main() {
    char mapMat[SIZE][SIZE] = {};
    bool visited[SIZE][SIZE] = {false};

    pair<int, int> grdPos;
    int dirX = -1;
    int dirY = 0;

    ifstream file(key);
    string line;
    int i = 0;
    while (getline(file, line)) {
        for (int j = 0; j < SIZE; j++) {
            mapMat[i][j] = line[j];
            if (line[j] == '^') {
                grdPos = {i,j};
            }   
        }
        i++;
    }

    int count = 1;

    while (grdPos.first >= 0 && grdPos.first < SIZE && grdPos.second >= 0 && grdPos.second < SIZE) {
        int testX = grdPos.first + dirX;
        int testY = grdPos.second + dirY;

        if (testX >= 0 && testX < SIZE && testY >= 0 && testY < SIZE) {
            while (mapMat[testX][testY] == '#') {
                //rotate right
                int temp = dirX;
                dirX = dirY;
                dirY = -temp;
                testX = grdPos.first + dirX;
                testY = grdPos.second + dirY;
            }

            //move
            grdPos.first = testX;
            grdPos.second = testY;

            //im not good at reading and took double the time i should have on this problem 
            //because I didnt realize it was only supposed to count unique tiles
            if (visited[testX][testY] == false) {
                visited[testX][testY] = true;
                count++;
            }
            
        }
        else {break;}
    }

    cout << count;

    file.close();
}
