#include "Checkers.h"
#include <fstream>
#include <iostream>


int main(int argc, char const *argv[]) {
    ifstream infile;
    infile.open("board4.txt");
    vector<string> board;
    for (int i = 0; i < x; i++) {
        string s;
        infile >> s;
        board.push_back(s);
    }
    infile.close();
    return 0;
}