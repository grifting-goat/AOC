//i cntrl+f and replaced all of the "int" with "long long" and my code worked all of the sudden
//i should be studying for my DSA final or sleeping

#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>

using namespace std;

string fileName =  "input.txt";

//apply the rules and update counter
void applyRules(unordered_map<long long, long long> &counter);

int main() {
    //track the counts of each number
    unordered_map<long long, long long> counter;

    //file processing
    ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file.\n";
        return 1;
    }

    string line;
    string sub = "";
    getline(file, line);

    for(long long i = 0; i < line.length(); i++) {
        if (line[i] == ' ') {
            counter[stoi(sub)] = 1;
            sub = "";
        }
        else {
            sub += line[i];
        }
    }
    counter[stoi(sub)] = 1;

    //explode
    for (long long i = 0; i < 75; i++) {
        applyRules(counter);
    }

    //count up how many of everything there is
    long long sum = 0;
    for (const auto pair : counter) {
        sum +=pair.second;
    }

    cout << sum;
        
    //clean up
    file.close(); 
    return 0;
}

//pretty slick
void applyRules(unordered_map<long long, long long> &counter) {
    unordered_map<long long, long long> innerCounter;
    for(const auto &val : counter) {
        if (val.first == 0) { //if a thing is zero make it one
            innerCounter[1] += val.second;
        }
        else {
            string temp = to_string(val.first);
            long long m = temp.length()/2;
            if (temp.length()%2 == 0) { //if its an even numer of digits
                innerCounter[stoll(temp.substr(0,m))] += val.second; //split
                innerCounter[stoll(temp.substr(m))] += val.second;
            }
            else { //all else fails
                innerCounter[stoll(temp) * 2024] += val.second;
            }
        }
    }
    counter = innerCounter;

}
