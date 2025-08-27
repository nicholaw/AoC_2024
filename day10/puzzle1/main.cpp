#include <exception>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

std::vector<std::vector<int>*>* topomap;            //topographical map
std::set<std::pair<int, int>>* potentialTrailheads; //positions of all zeros

/**
 * Reads input file and stores information of topographical map in 2D vector and position of all
 * numeral zeros in set of pairs.
 */
void readInput(std::string filename) {
    std::ifstream input;
    try {
        input.open(filename);
    } catch(std::exception e) {
        std::cout << "Could not find file \'" << filename << "\'\n";
        return;
    }

    std::string line;
    int next;
    int y = 0;
    while(std::getline(input, line)) {
        topomap->push_back(new std::vector<int>());
        for(int x = 0; x < line.size(); x++) {
            next = line.at(x) - '0';
            topomap->at(y)->push_back(next);
            if(next == 0) {
                potentialTrailheads->insert(std::pair(x, y));
            }
        }
        y++;
    }
}//readInput

/**
 * Writes topographical map and set of potential trailheads to output file.
 */
void writeOutput(std::string destination) {
    std::ofstream output;
    output.open(destination);
    
    //Write topographical map
    for(int i = 0; i < topomap->size(); i++) {
        for(int j = 0; j < topomap->at(i)->size(); j++) {
            output << topomap->at(i)->at(j);
        }
        output << "\n";
    }
    output << "\n";

    //Write set of potential trailheads
    int maxColumns = 3;
    int currColumn = 0;
    for(std::pair<int, int> p : *potentialTrailheads) {
        if(currColumn >= maxColumns) {
            output << "\n";
            currColumn = 0;
        }
        output << "{" << p.first << ", " << p.second << "}";
        currColumn++;
    }

    output.close();
}//writeOutput

int main() {
    topomap = new std::vector<std::vector<int>*>();
    potentialTrailheads = new std::set<std::pair<int, int>>();
    readInput("input.txt");
    writeOutput("output.txt");
    return 0;
}//main