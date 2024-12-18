#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <array>
#include <cmath>
#include <chrono>

using namespace std;

string fileName = "input.txt";

//function declarations

bool execute(int &pointer, vector<int> &program, unordered_map<char, int> &registers, unordered_map<int, int*> &comboOps);

//OPs
void adv(int operand, int &pointer, unordered_map<char, int> &registers, unordered_map<int, int*> &comboOps);

void bxl(int operand, int &pointer, unordered_map<char, int> &registers, unordered_map<int, int*> &comboOps);

void bst(int operand, int &pointer, unordered_map<char, int> &registers, unordered_map<int, int*> &comboOps);

void jnz(int operand, int &pointer, unordered_map<char, int> &registers, unordered_map<int, int*> &comboOps);

void bxc(int operand, int &pointer, unordered_map<char, int> &registers, unordered_map<int, int*> &comboOps);

void out(int operand, int &pointer, unordered_map<char, int> &registers, unordered_map<int, int*> &comboOps);

void bdv(int operand, int &pointer, unordered_map<char, int> &registers, unordered_map<int, int*> &comboOps);

void cdv(int operand, int &pointer, unordered_map<char, int> &registers, unordered_map<int, int*> &comboOps);

//set up a map of functions to match op codes
constexpr array<void(*)(int, int&, unordered_map<char, int>&, unordered_map<int, int*>&), 8> opMap = {
    adv, bxl, bst, jnz, bxc, out, bdv, cdv
    };

int main() {

    //store parsed info
    unordered_map<char, int> registers;
    vector<int> program;  

    //file parseing
    fstream file(fileName);
    string line;

    //Parse Register values
    while (getline(file, line)) {
        if (line.empty()) continue; //skip empty

        if (line.find("Program:") == 0) {break;} //skip program on first pass

        istringstream iss(line);
        string redundant, letter;
        int value;

        iss >> redundant >> letter >> value;
        registers[letter[0]] = value;  //add the letter identifier and data to a map   
    }

    //Parse Program
    if (!line.empty() && line.find("Program:") == 0) {
        istringstream prog(line.substr(8)); 
        string num;

        while (getline(prog, num, ',')) {
            program.push_back(stoi(num));
        }
    }

    unordered_map<int, int*> comboOps;

    //unnessisarily clunky
    int val0 = 0, val1 = 1, val2 = 2, val3 = 3;

    comboOps.insert({0, &val0});
    comboOps.insert({1, &val1});
    comboOps.insert({2, &val2});
    comboOps.insert({3, &val3});
    comboOps.insert({4, &registers['A']});
    comboOps.insert({5, &registers['B']});
    comboOps.insert({6, &registers['C']});

    //track where the program is
    int pointer = 0;

    //start clock (file parsing doesnt count)
    auto start = chrono::high_resolution_clock::now();

    //run commands
    while (execute(pointer, program, registers, comboOps)) {continue;}

    //timing
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "\nExecution time: " << duration.count() << " seconds" << endl;
}

bool execute(int &pointer, vector<int> &program, unordered_map<char, int> &registers, unordered_map<int, int*> &comboOps) {
    if (pointer >= program.size()) {return false;}
    int opCode = program[pointer];
    int operand = program[pointer+1];

    opMap[opCode](operand, pointer, registers, comboOps);

    return true;
}

void adv(int operand, int &pointer, unordered_map<char, int> &registers, unordered_map<int, int*> &comboOps) {
    registers['A'] = static_cast<int>(registers['A']/(pow(2,*comboOps[operand])));
    pointer+=2;
}

void bxl(int operand, int &pointer, unordered_map<char, int> &registers, unordered_map<int, int*> &comboOps) {
    registers['B'] = registers['B'] ^ operand;
    pointer+=2;
}

void bst(int operand, int &pointer, unordered_map<char, int> &registers, unordered_map<int, int*> &comboOps) {
    registers['B'] = *comboOps[operand] % 8;
    pointer+=2;
}

void jnz(int operand, int &pointer, unordered_map<char, int> &registers, unordered_map<int, int*> &comboOps) {
    if (registers['A'] == 0) {pointer+=2; return;}
    else {pointer = operand;}
}

void bxc(int operand, int &pointer, unordered_map<char, int> &registers, unordered_map<int, int*> &comboOps) {
    registers['B'] = registers['B'] ^ registers['C'];
    pointer+=2;
}

void out(int operand, int &pointer, unordered_map<char, int> &registers, unordered_map<int, int*> &comboOps) {
    cout << *comboOps[operand]%8 << ',';
    pointer+=2;
}

void bdv(int operand, int &pointer, unordered_map<char, int> &registers, unordered_map<int, int*> &comboOps) {
    registers['B'] = static_cast<int>(registers['A']/(pow(2,*comboOps[operand])));
    pointer+=2;
}

void cdv(int operand, int &pointer, unordered_map<char, int> &registers, unordered_map<int, int*> &comboOps) {
    registers['C'] = static_cast<int>(registers['A']/(pow(2,*comboOps[operand])));
    pointer+=2;
}