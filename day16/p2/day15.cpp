//do not attempt to understand this code. you will waste time it is not worth understanding
//this is an absurd mess of nosequiters and poor legibility i am sorry
//there is absolutely no way this the correct way to do this

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <windows.h>
#include <cstdlib>

using namespace std;

const bool LIVE = false; // in case you like watching boxes move for some reason

//thanks interwebs
template <typename T1, typename T2>
struct pair_hash {
    size_t operator()(const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

//check if a move is valid
bool isValid(int i, int j, pair<int,int> command, vector<vector<char>> &map, int &recs);

//move a box up or down
void moveBox(int i, int j, bool up,vector<vector<char>> &map);

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
                row.push_back(c);
                row.push_back('.');
            }
            if (c == '.') {
                row.push_back(c);
                row.push_back(c);
            }
            if (c == 'O') {
                row.push_back('[');
                row.push_back(']');
            }
            if (c == '#') {
                row.push_back(c);
                row.push_back(c);
            }
        }
        // check if its empty
        if (row.size() == 0) {break;}

        //add row to vector
        mat.push_back(row);
    }

    //print for debug
    for (auto r : mat) {
                for (auto c : r) {
                    cout << c << ' ';
                }
                cout << endl;
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
            if (com.first == 0) {
                for (int n = 1; n <= boxCount; n++) { // for left and right
                    if (com.second == 1)
                        mat[pR + com.first*n][pC + com.second*n] = ']' -(2*(n%2));
                    else {
                        mat[pR + com.first*n][pC + com.second*n] = '[' + (2*(n%2));
                    }
                }
            }
            else { // for up and down
                if (mat[pR][pC] == '[' || mat[pR][pC] == ']') {
                    moveBox(pR, pC, (com.first == -1), mat);
                }
                
            }
                    
            mat[pR][pC] = '@';
        }

        //in case you want to watch this all happen
        if (LIVE) {
            for (auto r : mat) {
                    for (auto c : r) {
                        cout << c << ' ';
                    }
                    cout << endl;
                } 
            Sleep(1000); 
            system("cls");   
        }

    }

    //calc the GPS
    long long sum = 0;
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[i].size(); j++) {
            if (mat[i][j] == '[') {
                sum += i * 100 + j;
            }
                
        }
    }

    //print mat at end
    for (auto r : mat) {
        for (auto c : r) {
            cout << c << ' ';
        }
        cout << endl;
    }
    cout << endl << sum;
}



bool isValid(int i, int j, pair<int,int> command, vector<vector<char>> &map, int &recs) {
    if (i < 0 || i >= map.size() || j < 0 || j >= map[0].size()) {
        return 0;
    }
    if(map[i][j] == '#') {
        return 0;
    }
    if(map[i][j] == '.'){
        return 1;
    }

    if (command.first == 0){
        if(map[i][j] == '[' || map[i][j] == ']') {
            recs+=1;
            return isValid(i + command.first,j + command.second, command,map, recs);
        }
    }
    else {
        if(map[i][j] == '[') {
            recs+=1;
            return isValid(i + command.first,j + command.second, command,map, recs) && isValid(i + command.first, j + command.second + 1, command,map, recs);
        }

        if(map[i][j] == ']') {
            recs+=1;
            return isValid(i + command.first,j + command.second, command,map, recs) && isValid(i + command.first, j + command.second - 1, command,map, recs);
        }
    }

    return 0;
}
/*
void moveBox(int i, int j, vector<vector<char>> &map) {
    map[i][j] = '[';
    map[i][j+1] = ']';
}
*/

void moveBox(int i, int j, bool up,vector<vector<char>> &map) {
    queue<pair<int,int>> q;
    short dir = up ? -1 : 1;
    q.push({i,j}); //
    vector<pair<int, int>> boxIndex;
    unordered_set<pair<int, int>, pair_hash<int, int>> visited;
    int n = 0;

    while(!q.empty()) {
        pair <int, int> test = q.front(); q.pop();
        

        if (map[test.first][test.second] == '[' || map[test.first][test.second] == ']') {
            if(visited.find(test) == visited.end()) { //if not visited
                int trash = 0;
                if (map[test.first][test.second] == '[' 
                && map[test.first+dir][test.second] != '#' && map[test.first+dir][test.second+1] != '#') {
                    boxIndex.push_back(test);
                    q.push({test.first, test.second + 1});
                }
                
                if (map[test.first][test.second] == ']')
                    q.push({test.first, test.second - 1});
                
                q.push({test.first+dir, test.second});
            }
        }

        visited.insert(test);
    }

    //update the map
    for (auto coor : boxIndex) {
        map[coor.first][coor.second] = '.';
        map[coor.first][coor.second+1] = '.';

    }
    for (auto coor : boxIndex) {
        map[coor.first + dir][coor.second] = '[';
        map[coor.first + dir][coor.second+1] = ']';
    }


}