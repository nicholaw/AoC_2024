#include <fstream>
#include <iostream>
#include "FrequencyMap.cpp"

FrequencyMap* nodes;
std::set<std::pair<int, int>>* antinodes;
std::pair<int, int>* dimensions;

/**
 * Returns true if the given position is within the input map and false otherwise.
 */
bool inbounds(std::pair<int, int> pos) {
    if((pos.first < 0) || (pos.second < 0)) {
        return false;
    } else {
        return ((pos.first < dimensions->first) && (pos.second < dimensions->second));
    }
}//inbounds

/**
 * Adds antinodes from each frequency into the set of all antinodes if the position is within the bound of the input map.
 */
void addPositions(std::vector<std::pair<int, int>> positions) {
    for(int curr = 0; curr < positions.size(); curr++) {
        for(int next = (curr + 1); next < positions.size(); next++) {
            std::pair<int, int> anti1 = std::pair<int, int>(2 * positions.at(curr).first - positions.at(next).first, 
                2 * positions.at(curr).second - positions.at(next).second);
            std::pair<int, int> anti2 = std::pair<int, int>(2 * positions.at(next).first - positions.at(curr).first, 
                2 * positions.at(next).second - positions.at(curr).second);
            if(inbounds(anti1)) {
                antinodes->insert(anti1);
            }
            if(inbounds(anti2)) {
                antinodes->insert(anti2);
            }
        }
    }
}//addPositions

/**
 * 
 */
int mapAntiNodes() {
    for(const auto& mapPair : nodes->getMap()) {
        addPositions(*nodes->getAntennaPositions(mapPair.first));
    }
    return antinodes->size();
}//mapAntiNodes

/**
 * Populates a map with nodes and their frequencies from the provided input.
 */
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
        for(x = 0; x < line.size(); x++) {
            str = line.at(x);
            if(!(str == ".")) {
                nodes->addFreq(str, std::pair<int, int>(x, y));
            }
        }
        dimensions->first = x;
        y++;
    }
    dimensions->second = y;
}//readInput

/**
 * Prints contents of the node and antinode maps to the provided output file.
 */
void writeOutput(std::string filename) {
    std::ofstream out;
    out.open(filename);
    out << "[" << dimensions->first << ", " << dimensions->second << "]\n\n";
    out << "NODES\n";
    for(const auto& mappair : nodes->getMap()) {
        out << mappair.first << ": ";
        for(std::pair<int, int> setpair : *mappair.second) {
            out << "{" << setpair.first << ", " << setpair.second << "} ";
        }
        out << "\n";
    }
    out << "\nANTINODES: " << antinodes->size() << "\n";
    int x = 0;
    for(const auto& pair : *antinodes) {
        if(x >= 10) {
            out << "\n";
            x = 0;
        }
        out << "{" << pair.first << ", " << pair.second << "} ";
        x++;
    }
    out << "\n";
    out.close();
}//writeOutput

int main() {
    nodes = new FrequencyMap();
    antinodes = new std::set<std::pair<int, int>>();
    dimensions = new std::pair<int, int>();
    readInput("input.txt");
    std::cout << mapAntiNodes() << "\n";
    writeOutput("output.txt");
}//main