//this is stupid i dont want to do this anymore

//i have no clue if this works or not because i would have to wait for the heat death of the universe

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

string fileName = "input.txt";

const int PRUNE = 16777216;

long long iter(long long seed);

long long nthIter(long long seed, int n);

void combo(vector<vector<long long>> &combinations);

int testStopping(const vector<long long>& largeVec, const vector<long long>& smallVec, vector<long long> &itvals);

long long sumCols(vector<vector<long long>> &combinations, vector<vector<long long>> &vals);

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
    vector<vector<long long>> changes;
    vector<vector<long long>> itvals;
    for (int i = 0; i < seeds.size(); i++) {
        vector<long long> row;
        vector<long long> rowVals;
        for (int j = 0; j < 2000; j++) {
            long long newSeed = iter(seeds[i]);
            int dif = newSeed%10 - seeds[i]%10;
            row.push_back(dif);
            rowVals.push_back(seeds[i]);
            seeds[i] = newSeed;
        }
        changes.push_back(row);
        itvals.push_back(rowVals);
    }

    vector<vector<long long>> combos;
    combo(combos);

    vector<vector<long long>> vals;
    


    int n = 0;
    for (auto r : changes) {
        vector<long long> row;

        for (auto bos : combos) {
            row.push_back(testStopping(r, bos, itvals[n]));
        }
        vals.push_back(row);
        n++;
    }

    cout << sumCols(combos, vals);
}


long long nthIter(long long seed, int n) {
    for (int i = 0; i < n; i++) {
        seed = (seed ^ (seed << 6))%PRUNE;
        seed = (seed ^ (seed >> 5))%PRUNE;
        seed = (seed ^ (seed << 11))%PRUNE;
    }
    return seed;
}

long long iter(long long seed) {
    seed = (seed ^ (seed << 6))%PRUNE;
    seed = (seed ^ (seed >> 5))%PRUNE;
    seed = (seed ^ (seed << 11))%PRUNE;

    return seed;
}


void combo(vector<vector<long long>> &combinations) {
    int min = -10, max = 10;
    //Generate combinations
    for (int a = min; a <= max; ++a) {
        for (int b = min; b <= max; ++b) {
            for (int c = min; c <= max; ++c) {
                for (int d = min; d <= max; ++d) {
                    combinations.push_back({a, b, c, d});
                }
            }
        }
    }

}


int testStopping(const vector<long long>& largeVec, const vector<long long>& smallVec, vector<long long> &itvals) {
    if (smallVec.empty() || largeVec.size() < smallVec.size()) {
        return false; // Handle edge cases
    }
    auto it = search(largeVec.begin(), largeVec.end(), smallVec.begin(), smallVec.end());


    if (it != largeVec.end()) {
        return itvals[*it];
    }
    return 0;
}

long long sumCols(vector<vector<long long>> &combinations, vector<vector<long long>> &vals) {
    long long maxsum = 0;
    for (int c = 0; c < vals[0].size(); c++) {
        long long localSum = 0;
        for (int r = 0; r < vals.size(); r++) {
            localSum += vals[r][c];
        }

        maxsum = max(maxsum, localSum);

    }
    return maxsum;
}