#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<unordered_set>
#include<unordered_map>
#include<algorithm>

using namespace std;

string fileName = "input.txt";

//function to find triangles
vector<vector<string>> findTriangles(unordered_map<string, vector<string>>& adjList) {
    vector<vector<string>> triangles;

    //iterate over each node in the adjacency list
    for (const auto& pair : adjList) {
        const string& node = pair.first;
        const vector<string>& neighbors = pair.second;
    
        for (int i = 0; i < neighbors.size(); i++) {
            for (int j = i + 1; j < neighbors.size(); j++) {
                const string& neighbor1 = neighbors[i];
                const string& neighbor2 = neighbors[j];

                //Check if the two neighbors are connected to each other
                if (find(adjList[neighbor1].begin(), adjList[neighbor1].end(), neighbor2) != adjList[neighbor1].end()) {
                    vector<string> triangle = {node, neighbor1, neighbor2};
                    sort(triangle.begin(), triangle.end());
                    triangles.push_back(triangle);
                }
            }
        }
    }

    return triangles;
}

int main() {

    fstream file(fileName);
    string line;
    
    unordered_map<string, vector<string>> adjList;

    //parse
    while (getline(file, line)) {
        string thing1 = line.substr(0, 2);  
        string thing2 = line.substr(3, 5);  

        adjList[thing1].push_back(thing2);
        adjList[thing2].push_back(thing1); 
    }

    //get the triangle groups
    vector<vector<string>> triangles = findTriangles(adjList);

    int sum = 0;
    for (const auto& triangle : triangles) {
        bool t = 0;
        for (const auto& str : triangle) {
            if (str[0] == 't'){ t = 1;}
        }
        sum+= t;
    }

    cout << sum/3; //gett rid of duped groups

    return 0;
}

