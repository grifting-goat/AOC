//this took a very long time to debug, the concepts are simple but i am cursed to make dumb errors
//am very happy with how it turned out
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<queue>
#include<utility>

using namespace std;

string fileName = "input.txt";

//offsets
int offR[4] = {1,0,-1,0};
int offC[4] = {0,1,0,-1};

//hash function for a pair
template <typename T1, typename T2>
struct pair_hash {
    size_t operator()(const pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

//check if an index is valid
bool inBounds(pair<int,int> test, vector<vector<char>> &map);

//generated a map where map[parent] = child
void generatePath(pair<int,int> start, pair<int,int> target, vector<vector<char>> &map, unordered_map<pair<int,int>, pair<int,int>, pair_hash<int, int>> &pathMap);

//iterate over a path from a starting index to a target index, recurns the count(distance) bewteen them on this path
void iteratePath(pair<int,int> start, pair<int,int> target, int maxLen, vector<vector<char>> &map,
unordered_map<pair<int,int>, pair<int,int>, pair_hash<int, int>> &pathMap, unordered_map<pair<int,int>, int, pair_hash<int, int>> &pathLen);

//generates a vector with 2D offsets in a certain range
void generate2Doffsets(int maxRange, vector<pair<int, int>> &offsets);

int main() {
    vector<vector<char>> map;
    pair<int,int> startCoord; //rows, cols
    pair<int,int> endCoord;
    int maxTime = 1;

    //input parsing
    fstream file(fileName);
    string line;
    while (getline(file, line)) {
        vector<char> row;
        for (char c : line) {
            if (c == 'S') {startCoord = {map.size(), row.size()};}
            if (c == 'E') {endCoord = {map.size(), row.size()};}
            if (c == '.') {maxTime++;} // count the distance to from start to end
            row.push_back(c);
        }
        map.push_back(row);
    }

    //build hash map to traverse the path
    unordered_map<pair<int,int>, pair<int,int>, pair_hash<int, int>> path;
    generatePath(startCoord, endCoord, map, path);

    //calculate the length to target at every point
    unordered_map<pair<int,int>, int, pair_hash<int, int>> pathLen;
    iteratePath(startCoord, endCoord,maxTime, map, path, pathLen);

    //make a vector containing all possible offsets
    vector<pair<int, int>> offsets;
    generate2Doffsets(20,offsets);

    int superCounter = 0; //sometimes names should be cool not descriptive
    int i = 0;
    pair<int,int> newStart = startCoord;
    for (int i = 0; i < maxTime; i++) { // check each spot along the way for a potetnial short cut
        for (int j = 0; j < offsets.size(); j++) { //attempt a phase in all 4 cardinal directions
            pair<int,int> test = {newStart.first + offsets[j].first, newStart.second + offsets[j].second}; //phase
            if (inBounds(test, map) && map[test.first][test.second] != '#') {
                if ((maxTime - (i + abs(offsets[j].first) + abs(offsets[j].second) + pathLen[test])) >= 100) {superCounter++;} // count the ones that save over one hundred picoseconds
            }   
        }
        newStart = path[newStart];  // go to the next path peice
    }

    cout << superCounter << endl;
    
    /* //print for debug 
    for(auto r : map) {
        for (auto c : r) {
            cout << c;
        }
        cout << endl;
    }*/
}

//generate the path using simple bfs(works bc only one valid path)
void generatePath(pair<int,int> start, pair<int,int> target, vector<vector<char>> &map, unordered_map<pair<int,int>, pair<int,int>, pair_hash<int, int>> &pathMap) {
    queue<pair<int,int>> q;
    unordered_set<pair<int,int>, pair_hash<int,int>> visited;

    q.push(start);
    visited.insert(start);

    while(!q.empty()) {
        pair<int,int> test = q.front(); q.pop();;

        for (int i = 0; i < 4; i++) {
            pair <int,int> testAdj = {test.first+ offR[i], test.second+offC[i]};
            if(visited.find(testAdj) == visited.end() && inBounds(testAdj, map) && map[testAdj.first][testAdj.second] != '#') {
                q.push({testAdj.first, testAdj.second});
                visited.insert({testAdj.first, testAdj.second});
                pathMap[test] = {testAdj.first, testAdj.second}; // add it to the path

                if (testAdj == target) {return;}//exit conidtion 
            }
        }
    }
}

bool inBounds(pair<int,int> test, vector<vector<char>> &map) {
    if (test.first < 0 || test.first >= map.size()) {return false;}
    if (test.second < 0 || test.second >= map[test.first].size()) {return false;}

    return true;
}

//builds a hash map where map[start] = distance to finish
void iteratePath(pair<int,int> start, pair<int,int> target, int maxLen, vector<vector<char>> &map, unordered_map<pair<int,int>, pair<int,int>, pair_hash<int, int>> &pathMap, 
unordered_map<pair<int,int>, int, pair_hash<int, int>> &pathLen) {
    int count = maxLen;
    pair<int,int> index = start;
    while (pathMap.find(index) != pathMap.end()) {
        pathLen[index] = count--;
        index = pathMap[index]; //traverse the path
    }

}

//create all the possible comindations of {r,c} in a given range
void generate2Doffsets(int maxRange, vector<pair<int, int>> &offsets) {
    while (maxRange) { //this feels scuffed
        for (int r = -maxRange; r <= maxRange; r++) {
            int c  = maxRange - abs(r);
            offsets.push_back({r,c});
            if (c) {offsets.push_back({r,-c});}
        }
        maxRange--;
    }
}