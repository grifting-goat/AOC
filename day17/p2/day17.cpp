//i have no clue how to do part two and dont have the time to figure it out
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

string globalString;

//function declarations

bool execute(long long &p, vector<long long> &program, unordered_map<char, long long> &registers, unordered_map<long long, long long*> &comboOps);

//OPs
void adv(long long operand, long long &p, unordered_map<char, long long> &registers, unordered_map<long long, long long*> &comboOps);

void bxl(long long operand, long long &p, unordered_map<char, long long> &registers, unordered_map<long long, long long*> &comboOps);

void bst(long long operand, long long &p, unordered_map<char, long long> &registers, unordered_map<long long, long long*> &comboOps);

void jnz(long long operand, long long &p, unordered_map<char, long long> &registers, unordered_map<long long, long long*> &comboOps);

void bxc(long long operand, long long &p, unordered_map<char, long long> &registers, unordered_map<long long, long long*> &comboOps);

void out(long long operand, long long &p, unordered_map<char, long long> &registers, unordered_map<long long, long long*> &comboOps);

void bdv(long long operand, long long &p, unordered_map<char, long long> &registers, unordered_map<long long, long long*> &comboOps);

void cdv(long long operand, long long &p, unordered_map<char, long long> &registers, unordered_map<long long, long long*> &comboOps);

//set up a map of functions to match op codes
constexpr array<void(*)(long long, long long&, unordered_map<char, long long>&, unordered_map<long long, long long*>&), 8> opMap = {
    adv, bxl, bst, jnz, bxc, out, bdv, cdv
    };

int main() {

    //store parsed info
    unordered_map<char, long long> registers;
    vector<long long> program;  

    //file parseing
    fstream file(fileName);
    string line;

    //Parse Register values
    while (getline(file, line)) {
        if (line.empty()) continue; //skip empty

        if (line.find("Program:") == 0) {break;} //skip program on first pass

        istringstream iss(line);
        string redundant, letter;
        long long value;

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

    unordered_map<long long, long long*> comboOps;

    //unnessisarily clunky
    long long val0 = 0, val1 = 1, val2 = 2, val3 = 3;

    comboOps.insert({0, &val0});
    comboOps.insert({1, &val1});
    comboOps.insert({2, &val2});
    comboOps.insert({3, &val3});
    comboOps.insert({4, &registers['A']});
    comboOps.insert({5, &registers['B']});
    comboOps.insert({6, &registers['C']});

    //track where the program is
    long long p = 0;

    //start clock (file parsing doesnt count)
    auto start = chrono::high_resolution_clock::now();

    //run commands
    while (execute(p, program, registers, comboOps)) {continue;}

    //timing
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "\nExecution time: " << duration.count() << " seconds" << endl;
}

bool execute(long long &p, vector<long long> &program, unordered_map<char, long long> &registers, unordered_map<long long, long long*> &comboOps) {
    if (p >= program.size()) {return false;}
    long long opCode = program[p];
    long long operand = program[p+1];

    opMap[opCode](operand, p, registers, comboOps);

    return true;
}

void adv(long long operand, long long &p, unordered_map<char, long long> &registers, unordered_map<long long, long long*> &comboOps) {
    registers['A'] = static_cast<long long>(registers['A']/(pow(2,*comboOps[operand])));
    p+=2;
}

void bxl(long long operand, long long &p, unordered_map<char, long long> &registers, unordered_map<long long, long long*> &comboOps) {
    registers['B'] = registers['B'] ^ operand;
    p+=2;
}

void bst(long long operand, long long &p, unordered_map<char, long long> &registers, unordered_map<long long, long long*> &comboOps) {
    registers['B'] = *comboOps[operand] % 8;
    p+=2;
}

void jnz(long long operand, long long &p, unordered_map<char, long long> &registers, unordered_map<long long, long long*> &comboOps) {
    if (registers['A'] == 0) {p+=2; return;}
    else {p = operand;}
}

void bxc(long long operand, long long &p, unordered_map<char, long long> &registers, unordered_map<long long, long long*> &comboOps) {
    registers['B'] = registers['B'] ^ registers['C'];
    p+=2;
}

void out(long long operand, long long &p, unordered_map<char, long long> &registers, unordered_map<long long, long long*> &comboOps) {
    cout << *comboOps[operand]%8 << ',';
    p+=2;
}

void bdv(long long operand, long long &p, unordered_map<char, long long> &registers, unordered_map<long long, long long*> &comboOps) {
    registers['B'] = static_cast<long long>(registers['A']/(pow(2,*comboOps[operand])));
    p+=2;
}

void cdv(long long operand, long long &p, unordered_map<char, long long> &registers, unordered_map<long long, long long*> &comboOps) {
    registers['C'] = static_cast<long long>(registers['A']/(pow(2,*comboOps[operand])));
    p+=2;
}