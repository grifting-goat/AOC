#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<unordered_set>
#include<unordered_map>

using namespace std;

string fileName = "input.txt";

//can the building be made from the blocks
bool buildible(int start, string building, unordered_set<string> &blocks, unordered_map<int, bool> &memo);

int main () {

    unordered_set<string> patterns;
    vector<string> combos;

    //file parsing
    fstream file(fileName);
    string line;
    while (getline(file, line)) {
        string sub;
        if (line == "") {break;}
        for (auto c : line) {
            if (c == ',') {patterns.insert(sub); sub = ""; continue;}
            if (c == ' ') {continue;}
            sub += c;
        }
    }

    while (getline(file, line)) {combos.push_back(line);}

    //can they be made?
    int count = 0;
    for (const string& com : combos) {
        unordered_map<int, bool> memo;
        if (buildible(0, com, patterns, memo)) {
            count++;
        }
    }
    //count if they can be made
    cout << count << endl;


    //for (auto p : patterns) {cout << p << " ";}

    //cout << endl;

    //for (auto c : combos) {cout << c << " ";}

    file.close();
    return 0;

}

//see if a string can be build from a set of smaller strings(no order and repeatable) returns the full string back if it works
bool buildible(int start, string building, unordered_set<string> &blocks, unordered_map<int, bool> &memo) {
    if (start == building.size()) return true; //we r done
    if (memo.find(start) != memo.end()) return memo[start]; // so we dont have to redo this steps

    //check if any matches
    for (int end = start + 1; end <= building.size(); end++) {
        string sub = building.substr(start, end - start);
        if (blocks.find(sub) != blocks.end() && buildible(end, building, blocks, memo)) {
            return memo[start] = true; 
        }
    }

    return memo[start] = false;// cant be done
}