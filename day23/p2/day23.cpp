//why my head hurt how do ppl just do this

//i got right answer i am not quite sure how //even chatGTP was lost

//ergo i will not be commenting thouroghly

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<unordered_set>
#include<unordered_map>
#include<algorithm>
#include<queue>

using namespace std;

string fileName = "input.txt";

vector<string> bfs(const string& seed, unordered_map<string, unordered_set<string>>& adjList) {
    queue<string> q;
    unordered_set<string> visited;
    vector<string> component;

    q.push(seed);
    visited.insert(seed);

    while (!q.empty()) {
        string node = q.front(); q.pop();
        component.push_back(node);
        
        for (const auto& neighbor : adjList[node]) {
            if (visited.find(neighbor) == visited.end()) {
                
                bool bCon = 1;
                for (const auto& comp :  component) {
                    if (adjList[neighbor].find(comp) == adjList[neighbor].end()) {bCon = 0;}
                
                    if (bCon) {
                        visited.insert(neighbor);
                        q.push(neighbor);
                    }
                }
            }
        }
    }

    return component;
}


string longestConnected(unordered_map<string, unordered_set<string>>& adjList) {
    int maxSize = 0;
    vector<string> maxVec;

    for (const auto& pair : adjList) {
        string node = pair.first;
        vector<string> component = bfs(node, adjList);

        if (component.size() >= maxSize) {
            maxSize = component.size();
            maxVec = component;
        }
    }

    // Sort alphabetically
    sort(maxVec.begin(), maxVec.end());

    string password = "";
    for (size_t i = 0; i < maxVec.size(); ++i) {
        password += maxVec[i];
        if (i != maxVec.size() - 1) {
            password += ',';
        }
    }

    return password;
}

int main() {
    fstream file(fileName);
    string line;

    unordered_map<string, unordered_set<string>> adjList;

    //parse
    while (getline(file, line)) {
        string thing1 = line.substr(0, 2);  
        string thing2 = line.substr(3, 5);  

        adjList[thing1].insert(thing2);
        adjList[thing2].insert(thing1); 
    }

    string password = longestConnected(adjList);
    cout << password << endl;

    return 0;
}
