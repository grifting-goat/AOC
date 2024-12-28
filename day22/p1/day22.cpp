#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using namespace std;

string fileName = "input.txt";

const int PRUNE = 16777216;

long long nthIter(long long seed, int n);

int main() {

    vector<long long> seeds;

    fstream file(fileName);
    string line;

    while(getline(file,line)) {
        try{seeds.push_back(stoll(line));}
        catch(const std::invalid_argument& e) {cerr << "invalid input";}
    }

    long long sum = 0;
    //follow the rules for each seed
    for (auto seed : seeds) {sum += nthIter(seed, 2000);}
    cout << sum;
}

long long nthIter(long long seed, int n) {
    for (int i = 0; i < n; i++) {
        seed = (seed ^ (seed << 6))%PRUNE;
        seed = (seed ^ (seed >> 5))%PRUNE;
        seed = (seed ^ (seed << 11))%PRUNE;
    }
    return seed;
}