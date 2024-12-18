//very simple to brute force this problem, i even optimized it with a funny goto statement of my own concoction.
//i love brute force

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<unordered_set>
#include<unordered_map>
#include<queue>
#include<vector>

using namespace std;

string fileName = "input.txt";

//given in problem
const int ROWS = 70;
const int COLS = 70;

//offset array for concise code
int offR[4] = {1,0,-1,0};
int offC[4] = {0,1,0,-1};

//hash function for pairs
template <typename T1, typename T2>
struct pair_hash {
    size_t operator()(const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

//checks if a valid path can be found // bfs
bool isPath(unordered_set<pair<int,int>,pair_hash<int, int>> destroyed);

//checks if an index is in bounds (uses the global cols and rows)
bool inBounds(pair<int,int> testCase);

int main() {
    //file and data parseing
    fstream file(fileName);
    string line;
    vector<pair<int,int>> list;
    unordered_set<pair<int,int>,pair_hash<int, int>> coors;

    //get the list of destroyed bits
    while (getline(file, line)) {
        int a, b;
        if (sscanf(line.c_str(), "%d,%d", &a, &b) == 2) {
            list.push_back({b, a});
        }
    }

    //brute force with goto statements?!?!!? -- lets go 
    int start = 1024;
    int inc = 1024;

    recursiveLabel:
    if (inc == 1) {cout << start << ": " << list[start].second << "," << list[start].first; return 0;}
    for (int i = start; i < list.size(); i+= inc) {
        coors.clear();
        for (int j = 0; j < i; j++) {
            coors.insert(list[j]);
        }
        if (!isPath(coors)) {start = i - inc; inc >>= 1; goto recursiveLabel;} //what kind of psychopath writes this kind of code
    }


    return 0;
}

//breath first search
bool isPath(unordered_set<pair<int,int>,pair_hash<int, int>> destroyed) {
    queue<pair<int,int>> q;
    unordered_set<pair<int,int>, pair_hash<int, int>> visited = destroyed; //resuse recycle
    bool found = 0;

    q.push({0,0});
    visited.insert({0,0});
    
    while (!q.empty() && !found) {
        pair<int,int> test = q.front(); q.pop();

        for (int i = 0; i < 4; i++) {
            pair <int,int> testAdj = {test.first+ offR[i], test.second+offC[i]};
            if(visited.find(testAdj) == visited.end() && inBounds(testAdj)) {
                q.push({testAdj.first, testAdj.second});
                visited.insert({testAdj.first, testAdj.second});
                //break out if it makes it to the target
                if (testAdj == make_pair(ROWS, COLS)) {return 1;} //found path
            }
        }
    }

    return 0; //no path :(
}


bool inBounds(pair<int,int> testCase) {
    if (testCase.first < 0 || testCase.first > ROWS || testCase.second < 0 || testCase.second > COLS) {
        return false;
    }
    return true;

}