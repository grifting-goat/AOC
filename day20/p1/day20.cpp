//very slow method, i though of a much faster onre right after impimenting this one but what is done is done
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<queue>

using namespace std;

string fileName = "input.txt";

//offsets
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

//check if an index is valid
bool inBounds(pair<int,int> test, vector<vector<char>> &map);

//generated a map where map[parent] = child
void generatePath(pair<int,int> start, pair<int,int> target, vector<vector<char>> &map, unordered_map<pair<int,int>, pair<int,int>, pair_hash<int, int>> &pathMap);

//iterate over a path from a starting index to a target index, recurns the count(distance) bewteen them on this path
int iteratePath(pair<int,int> start, pair<int,int> target, int iterations, pair<int,int> &endPos, vector<vector<char>> &map, unordered_map<pair<int,int>, pair<int,int>, pair_hash<int, int>> &pathMap);

int main() {
    vector<vector<char>> map;
    pair<int,int> startCoord; //rows, cols
    pair<int,int> endCoord;

    fstream file(fileName);
    string line;
    while (getline(file, line)) {
        vector<char> row;
        for (char c : line) {
            if (c == 'S') {startCoord = {map.size(), row.size()};}
            if (c == 'E') {endCoord = {map.size(), row.size()};}
            row.push_back(c);
        }
        map.push_back(row);
    }

    //build hash map to traverse the path
    unordered_map<pair<int,int>, pair<int,int>, pair_hash<int, int>> path;
    generatePath(startCoord, endCoord, map, path);

    pair<int,int> dummy;
    int maxTime = iteratePath(startCoord, endCoord, INT_MAX-1, dummy, map, path);

    int superCounter = 0;
    for (int i = 0; i < maxTime; i++) { // check each spot along the way for a potetnial short cut
        pair<int,int> newStart;
        iteratePath(startCoord, endCoord, i, newStart, map, path); //go to the spot
        for (int j = 0; j < 4; j++) { //attempt a phase in all 4 cardinal directions
            pair<int,int> test = {newStart.first + 2*offR[j], newStart.second + 2*offC[j]}; //phase
            if (inBounds(test, map) && map[test.first][test.second] != '#') {
                if (maxTime - (i + 3 + iteratePath(test, endCoord, maxTime, test, map, path)) >= 100) {superCounter++;} // count the ones that save over one hundred picoseconds
            }   
        }  
    }

    cout << superCounter << endl;
    

    //print for debug
    for(auto r : map) {
        for (auto c : r) {
            cout << c;
        }
        cout << endl;
    }
}


void generatePath(pair<int,int> start, pair<int,int> target, vector<vector<char>> &map, unordered_map<pair<int,int>, pair<int,int>, pair_hash<int, int>> &pathMap) {
    queue<pair<int,int>> q;
    unordered_set<pair<int,int>, pair_hash<int,int>> visited;

    q.push(start);
    visited.insert(start);

    while(!q.empty()) {
        pair<int,int> test = q.front(); q.pop();

        for (int i = 0; i < 4; i++) {
            pair <int,int> testAdj = {test.first+ offR[i], test.second+offC[i]};
            if(visited.find(testAdj) == visited.end() && inBounds(testAdj, map) && map[testAdj.first][testAdj.second] != '#') {
                q.push({testAdj.first, testAdj.second});
                visited.insert({testAdj.first, testAdj.second});
                pathMap[test] = {testAdj.first, testAdj.second};

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


int iteratePath(pair<int,int> start, pair<int,int> target, int iterations, pair<int,int> &endPos, vector<vector<char>> &map, unordered_map<pair<int,int>, pair<int,int>, pair_hash<int, int>> &pathMap) {
    int count = 0;
    pair<int,int> index = start;
    while (pathMap.find(index) != pathMap.end()) {
        if(index == target) {break;} //exit conidtion
        if(count > iterations) {break;} //excedes iterations
        index = pathMap[index];
        count++;
    }
    endPos = index;
    return count;
}

