#include <iostream>
#include <fstream>
#include <string>

//pranked i swtiched langues for this

using namespace std;

string fileName = "input4.txt";

const int c = 140;
const int r = 140;

bool isNextletter(char mat[r][c], int i, int j, int letter = 0, int dx = 0, int dy = 0);

int main() {
    ifstream file(fileName);
    string line;

    char mat[r][c] = {'\0'};

    int i = 0;
    while (getline(file, line)) {
        for (int j = 0; j < line.length(); j++) {
            mat[i][j] = line[j];
        }
        i++;
    }
/*
    for (int i = 0; i < r; i++)  {
        for (int j = 0; j < c; j++) {
            cout << mat[i][j];
        }
        cout << endl;
    }
*/
    int sum = 0;
    for (int i = 0; i < r; i++)  {
        for (int j = 0; j < c; j++) {
            //all direcitons //this cannot be the most effiecent way but it works
            for(int v = -1; v < 2; v++) {
                for (int w = -1; w < 2; w++) {
                    //if (v == 0 && w == 0) continue;
                    if (v * w == 0) continue;
                    sum += isNextletter(mat, i, j, 0, v, w);    
                }
            }
        }
    }
    
    cout << sum;
    file.close();


    return 0;
}

bool isNextletter(char mat[r][c], int i, int j, int letter, int dx, int dy) {
    char key[3] = {'M', 'A', 'S'};

    if (letter == 3) {
        return true; 
    }

    if (i < 0 || i >= r || j < 0 || j >= c || mat[i][j] != key[letter]) {
        return false;
    }

    char temp = mat[i][j];
    mat[i][j] = '\0';

    //recursion hurts my head
    bool found = isNextletter(mat, i + dx, j + dy, letter + 1, dx, dy);

    mat[i][j] = temp;
    
    return found;
}