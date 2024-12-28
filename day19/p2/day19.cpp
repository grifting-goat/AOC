#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<unordered_set>
#include<unordered_map>

using namespace std;

string fileName = "input.txt";

//can the building be made from the blocks and how many different ways
long long buildible(int start, const string &building, unordered_set<string> &blocks, unordered_map<int, long long> &memo);

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
        patterns.insert(sub);
    }

    while (getline(file, line)) {combos.push_back(line);}

    //can they be made?
    long long count = 0;    
    for (const string& com : combos) {
        unordered_map<int, long long> memo;
        count += buildible(0, com, patterns, memo);
    }
    //count if they can be made
    cout << count << endl;


    //for (auto p : patterns) {cout << p << " ";}

    //cout << endl;

    //for (auto c : combos) {cout << c << " ";}

    file.close();
    return 0;

}

//see how many times a string can be build from a set of smaller strings
long long buildible(int start, const string &building, unordered_set<string> &blocks, unordered_map<int, long long> &memo) {
    if (start == building.size()) return 1; //done
    if (memo.find(start) != memo.end()) return memo[start]; //recycle

    long long count = 0;

    // Check for all substrings starting from 'start'
    for (int end = start + 1; end <= building.size(); ++end) {
        string sub = building.substr(start, end - start);
        if (blocks.find(sub) != blocks.end()) {
            count += buildible(end, building, blocks, memo);
        }
    }

    memo[start] = count; // Memoize the result
    return count;
}