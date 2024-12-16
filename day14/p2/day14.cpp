//because of the way the level was made if you find the first place where no duplicate guards exist then you have the right time; 
//key was made by running velocities in reverse for n times
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <utility>

using namespace std;

string fileName = "input.txt";

const int TIME = 100;

const int ROWS = 103;
const int COLS = 101;

struct Vec {
    int x,y;
};

struct Guard {
    Vec pos,velocity;
};


//telports guards to other side of map
void teleport(Guard &g);

//prints all the guards at that time
void printGuards(vector<Guard> grds);

//checks for duplicate guards
bool isDupes(vector<Guard> &grds);


struct pair_hash {
    template <class T1, class T2>
    std::size_t operator ()(const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ (h2 << 1); // Combine the two hash values
    }
};

vector<Guard> guards;

int main() {

    //parse the input file
    ifstream file(fileName);
    string line;
    while(getline(file, line)) {
        Guard g;
        istringstream lineStream(line);
        char skip;
        lineStream >> skip >> skip >> g.pos.x >> skip >> g.pos.y; //position
        lineStream >> skip >> skip >> g.velocity.x >> skip >> g.velocity.y; //velocity

        guards.push_back(g);
    }

    //update the positions with time
    int n = 0;
    while (!isDupes(guards)) {
        for (Guard &g : guards) {
            g.pos.x += g.velocity.x;
            g.pos.y += g.velocity.y;
            teleport(g);     
        }

        n++;
        if (!(n%1000)) {cout << n << endl;} 
    }
    
    //pretty pictures
    printGuards(guards);

    cout << n;
    
    return 0;
}

void teleport(Guard &g) {
    if (g.pos.x >= COLS) {
        g.pos.x -= COLS;
    }
    if (g.pos.x < 0) {
        g.pos.x += COLS;
    }
    if (g.pos.y >= ROWS) {
        g.pos.y -= ROWS;
    }
    if (g.pos.y < 0) {
        g.pos.y += ROWS;
    }
}


void printGuards(vector<Guard> grds) {
    char mat[ROWS][COLS];
    memset(mat, '.', sizeof(mat));

    for (auto g : grds) {
        mat[g.pos.y][g.pos.x] = '#';
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << mat[i][j];
        }
        cout << endl;
    }

}

bool isDupes(vector<Guard> &grds) {
    unordered_map<pair<int,int>, int, pair_hash> bins;
    for (auto &g : grds) {
        bins[{g.pos.x, g.pos.y}] += 1;
    }
    for (auto &b : bins) {
        if (b.second != 1) {
            return false;
        }
    }
    return true;
}

