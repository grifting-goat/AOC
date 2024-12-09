#include<iostream>
#include<string>
#include<fstream>

//day 9: very straighforward to brute force

using namespace std;


string fileName = "input.txt";

int main() {
    ifstream file(fileName);
    //keep it classy
    if (!file) {
        std::cerr << "Unable to open file.\n";
        return 1;
    }

    string line;
    getline(file, line);// the one giant line lol

    long tot = 0;
    for(int i = 0; i < line.length(); i++) {
        tot += (line[i] - '0');
    }

    //take all the memory away
    int* mat = new int [tot];

    int head = 0;

    //this cannot be the best way to do this, its like taking a simple multiplaction problem to apples and then going back to numbers
    for(int i = 0; i < line.length(); i+=2) {
        for (int j = 0; j < line[i]- '0'; j++) {
            mat[head + j] = i/2;
        }
        head += line[i] - '0';
        for (int j = 0; j < line[i+1]- '0'; j++) {
            mat[head + j] = -1;
        }
        head += line[i+1] - '0';
    }

    //monster
    for(int i = tot-1; i >= 0; i--) {
        for(int j = 0; j < i; j++) {
            if (mat[j] == -1) {
                mat[j] = mat[i];
                mat[i] = -1;
                break;
            }
        }
    }

    //you know its bad when the long long shows up
    long long checksum = 0;
    for (int i = 0; i < tot; i++) {
        checksum += i * mat[i] * (mat[i] != -1);
        
    }


    cout << endl << checksum;

    file.close();

    delete[] mat;
}