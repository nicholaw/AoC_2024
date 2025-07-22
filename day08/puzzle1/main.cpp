#include <exception>
#include <fstream>
#include <iostream>
#include "FrequencySet.cpp"

void readInput(std::string filename) {
    //open input file
    std::ifstream inputFile;
    try {
        inputFile.open(filename);
    } catch (std::exception e) {
        std::cout << "Could not find file \"" << filename << "\"\n";
    }

    //read input file
    std::string line;
    int x, y = 0;
    while(std::getline(inputFile, line)) {
        //TODO
    }
}//readInput

int main() {
    readInput("input.txt");
}//main