//this is the ultimate brute force algorithm 
//i wasted 45 minutes debugging bc i accidently incremented the counter twice per guard loop

#include <iostream>
#include <fstream>
#include <string>
#include <utility>

using namespace std;

string key = "input.txt";

const int SIZE = 130;

int main() {

    ifstream file(key);

    char mapMat[SIZE][SIZE] = {};
    char visited[SIZE][SIZE] = {' '};


    pair<int, int> masterPos;
    pair<int, int> grdPos;
    int dirX = -1;
    int dirY = 0;
    int maxMovements = 1;

    string line;
    int i = 0;
    while (getline(file, line)) {
        for (int j = 0; j < SIZE; j++) {
            mapMat[i][j] = line[j];
            if (line[j] == '^') {
                masterPos.first = i;
                masterPos.second = j;
            }
            if (line[j] == '.') { 
                maxMovements++;
            }
                
        }
        i++;
    }

    
    int tot = 0;

    //forgive me i have sinned
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            char place = mapMat[i][j];

            int count = 1;
            int runs = 0;
            mapMat[i][j] = '#'; //add obstacle to index
            grdPos.first = masterPos.first;
            grdPos.second = masterPos.second;
            dirX = -1;
            dirY = 0;

            while (grdPos.first >= 0 && grdPos.first < SIZE && grdPos.second >= 0 && grdPos.second < SIZE) {
                if (runs > maxMovements) {tot++; count = 0; break;}
                int testX = grdPos.first + dirX;
                int testY = grdPos.second + dirY;

                if (testX >= 0 && testX < SIZE && testY >= 0 && testY < SIZE) {
                    while (mapMat[testX][testY] == '#') {
                        int temp = dirX;
                        dirX = dirY;
                        dirY = -temp;
                        testX = grdPos.first + dirX;
                        testY = grdPos.second + dirY;
                    }

                    grdPos.first = testX;
                    grdPos.second = testY;

                    if (visited[testX][testY] != 'X') {
                        visited[testX][testY] = 'X';
                        count++;
                    }
                    runs++;
                    
                }
                else {break;}
            }

            mapMat[i][j] = place; //unadd obstacle

            //clear visisted matrix
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    visited[i][j] = ' ';
                }
            }    
            
        }
    }

    cout << tot;

    file.close();
}