//brute force

#include<fstream>
#include<iostream>
#include<string>
#include<vector>

using namespace std;

string fileName =  "input.txt";

void applyRules(vector<long long> &vals);

int main() {

    ifstream file(fileName);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file.\n";
        return 1;
    }
    //big ol vector
    vector<long long> stone;

    string line;
    string sub = "";
    getline(file, line);

    for(int i = 0; i < line.length(); i++) {
        if (line[i] == ' ') {
            stone.push_back(stoi(sub));
            sub = "";
        }
        else {
            sub += line[i];
        }
    }

    stone.push_back(stoi(sub));

    //do it 25 times
    for (int i = 0; i < 25; i++) {
        applyRules(stone);
    }
    

    cout << endl << stone.size();
        


    file.close(); 
    return 0;
}


void applyRules(vector<long long> &vals) {
    int i = 0;
    int len = vals.size();
    while (i < len) {
        if (vals[i] == 0) { // if 0 then 1
            vals[i] = 1;
        }
        else {
            string temp = to_string(vals[i]);
            int m = temp.length()/2;

            if (temp.length()%2 == 0) { // if even digits then split
                vals[i] = stoll(temp.substr(0,m));
                vals.push_back(stoll(temp.substr(m)));
            }
            else { //if all else fails
                vals[i] *= 2024;
            }
        }
        
        i++;
    }

}