#include <fstream>
#include <iostream>
#include "FrequencyMap.cpp"

FrequencyMap* frequencies;

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
    std::string str;
    int x, y = 0;
    while(std::getline(inputFile, line)) {
        for(int x = 0; x < line.size(); x++) {
            str = line.at(x);
            if(!(str == ".")) {
                frequencies->addFreq(str, std::pair<int, int>(x, y));
            }
        }
        y++;
    }
}//readInput

void writeOutput(std::string filename) {
    std::ofstream out;
    out.open(filename);
    for(const auto& mappair : frequencies->getMap()) {
        out << mappair.first << ": ";
        for(std::pair<int, int> setpair : *mappair.second) {
            out << "{" << setpair.first << ", " << setpair.second << "} ";
        }
        out << "\n";
    }
    out.close();
}//writeOutput

int main() {
    frequencies = new FrequencyMap();
    readInput("input.txt");
    writeOutput("output.txt");
}//main