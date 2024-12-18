//surprisinly simple given the questions this week. just simple bfs with back tracking
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<unordered_set>
#include<unordered_map>
#include<queue>

using namespace std;

string fileName = "input.txt";

//size of the area given by problem
const int ROWS = 70;
const int COLS = 70;

//the number of bits that fall
const int MAXBITS = 1024;

int offR[4] = {1,0,-1,0};
int offC[4] = {0,1,0,-1};

//hash function for a pair
template <typename T1, typename T2>
struct pair_hash {
    size_t operator()(const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

//returns the length of the shortest path from (0,0) to (ROW,COL)
int countShortestPath(unordered_set<pair<int,int>,pair_hash<int, int>> destroyed);

//must i explain
bool inBounds(pair<int,int> testCase);


int main() {
    fstream file(fileName);
    string line;
    unordered_set<pair<int,int>,pair_hash<int, int>> coors;

    //get the list of destroyed bits
    int numBits = 0;
    while (getline(file, line)) {
        int a, b;
        if (sscanf(line.c_str(), "%d,%d", &a, &b) == 2) {
            coors.insert({b, a});
            numBits++;
        }
        //break when max bits is reached
        if (numBits >= MAXBITS) {break;}
    }

    cout << "shortest path: " << countShortestPath(coors);

}

int countShortestPath(unordered_set<pair<int,int>,pair_hash<int, int>> destroyed) {
    queue<pair<int,int>> q;
    unordered_set<pair<int,int>, pair_hash<int, int>> visited = destroyed; //so cant visit byte areas
    unordered_map<pair<int,int>, pair<int,int>, pair_hash<int, int>> parent; //map with key: cell, data: parentCell
    pair<int,int> index = make_pair(ROWS, COLS); //goal
    bool found = 0;

    q.push({0,0});
    visited.insert({0,0});
    
    while (!q.empty() && !found) {
        pair<int,int> test = q.front(); q.pop(); //remove front of queue

        for (int i = 0; i < 4; i++) {
            pair <int,int> testAdj = {test.first+ offR[i], test.second+offC[i]};
            if(visited.find(testAdj) == visited.end() && inBounds(testAdj)) {
                q.push({testAdj.first, testAdj.second});
                visited.insert({testAdj.first, testAdj.second});
                parent[{testAdj.first, testAdj.second}] =  test;

                //break out if it makes it to the target
                if (testAdj == index) {found = 1;break;}
            }
        }
    }

    if (found) {
        int count = 0;
        while (parent.find(index) != parent.end()) {
            index = parent[index]; //track back to the start point
            count++; //counting along the way
        }
        return count; //length of path
    }

    return -1; // no path

}


bool inBounds(pair<int,int> testCase) {
    if (testCase.first < 0 || testCase.first > ROWS || testCase.second < 0 || testCase.second > COLS) {
        return false;
    }
    return true;

}