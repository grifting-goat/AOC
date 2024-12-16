//much more elegant and intentional than some of my other solutions // worked just as i wanted it
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <windows.h>

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

//calcs the product of the sums in each quadrent
int calcGuards(vector<Guard> grds);

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
    for (int i = 0; i < TIME; i++) {
        for (Guard &g : guards) {
            g.pos.x += g.velocity.x;
            g.pos.y += g.velocity.y;
            teleport(g);
        }
    }
    
    //pretty pictures
    printGuards(guards);

    cout << calcGuards(guards);

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

int calcGuards(vector<Guard> grds) {
    int sums[4] = {0,0,0,0};
    for (auto g : grds) {

        //shift everything over so that coorinates cirle an origin of (0,0)
        int tx = g.pos.x - COLS/2;
        int ty = g.pos.y - ROWS/2;

        //first quadrent
        if (tx > 0 && ty > 0) {
            sums[0] += 1;
        }
        //second quadrent
        if (tx < 0 && ty > 0) {
            sums[1] += 1;
        }
        //third quadrent
        if (tx < 0 && ty < 0) {
            sums[2] += 1;
        }
        //fourth quadrent
        if (tx > 0 && ty < 0) {
            sums[3] += 1;
        }            
    }

    //product of the sums
    int tot = 1;
    for (int i = 0; i < 4; i++) {tot *= sums[i];}
    return tot;
}
