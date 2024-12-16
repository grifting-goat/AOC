#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <windows.h>
#include <cstdlib>

using namespace std;

bool isValid(int i, int j, pair<int,int> command, vector<vector<char>> &map, int &recs);

string fileName = "input.txt";
int pR = 0;
int pC = 0;

int main() {
    //file processing
    ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file.\n";
        return 1;
    }

    vector<vector<char>> mat;
    string line;

    //get map
    while (getline(file, line)) {
        vector<char> row;  
        for (auto c : line) {
            if (c == '@') {
                pC = row.size();
                pR = mat.size();
            }
            row.push_back(c);
        }
        // check if its empty
        if (row.size() == 0) {break;}

        //add row to vector
        mat.push_back(row);
    }

    //get instructions
    queue <pair<int,int>> commands;
    while (getline(file, line)) {
        for (char c : line) {
            switch (c) {
                case '^': commands.push({-1,0}); break;
                case 'v': commands.push({1,0}); break;
                case '>': commands.push({0,1}); break;
                case '<': commands.push({0,-1}); break;
            }
        }
    }

    //run the commands
    while(!commands.empty()) {
        pair <int, int> com = commands.front();
        commands.pop();
        int boxCount = 0;
        if (isValid(pR + com.first, pC + com.second, com, mat, boxCount)) {
            mat[pR][pC] = '.';
            pR += com.first;
            pC += com.second;
            for (int n = 1; n <= boxCount; n++) {
                mat[pR + com.first*n][pC + com.second*n] = 'O';
            }
            mat[pR][pC] = '@';
        }
        //in case you want to watch this all happen

    /*
        for (auto r : mat) {
                for (auto c : r) {
                    cout << c << ' ';
                }
                cout << endl;
            } 
        Sleep(1000); 
        system("cls");  
    */
        
    }

    //calc the GPS
    long long sum = 0;
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[i].size(); j++) {
            if (mat[i][j] == 'O') {
                sum += i * 100 + j;
            }
                
        }
    }

    //print mat
    for (auto r : mat) {
        for (auto c : r) {
            cout << c << ' ';
        }
        cout << endl;
    }
    cout << endl << sum;
}



bool isValid(int i, int j, pair<int,int> command, vector<vector<char>> &map, int &recs) {
    if (i < 0 || i >= map.size() || j < 0 || j >= map[i].size()) {
        return 0;
    }
    else if(map[i][j] == '#') {
        return 0;
    }
    else if(map[i][j] == 'O') {
        recs+=1;
        return isValid(i + command.first,j + command.second, command,map, recs);
    }
    else {
        return 1;
    }
}