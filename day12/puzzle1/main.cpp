#include <exception>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include "Region.h"

using namespace std;

void printRegions(set<Region>* regions) {
    int count = 0;
    for(Region r : *regions) {
        if(count < 10) {
            cout << "0";
        }
        cout << count << ": " << r.getCrop() << ", " << r.getMeasurements().first << ", " << r.getMeasurements().second << "\n";
        count++;
    }
}//printRegions

set<Region>* mapRegions(vector<vector<char>>* plots) {
    set<Region>* regions = new set<Region>();
    for(int i = 0; i < plots->size(); i++) {
        for(int j = 0; j < plots->at(i).size(); j++) {
            regions->insert(Region(plots->at(i).at(j)));
        }
    }
    printRegions(regions);
    return regions;
}//mapRegions

/**
 * Writes contents of the provided 2D arary to a text file with the provided name.
 */
void writeOutput(string destination, vector<vector<char>>* table) {
    ofstream output;
    output.open(destination);
    for(int i = 0; i < table->size(); i++) {
        for(int j = 0; j < table->at(i).size(); j++) {
            output << table->at(i).at(j);
        }
        output << "\n";
    }
    output.close();
}//writeOutput

/**
 * Generates a 2D array of all plots from puzzle input.
 */
vector<vector<char>>* readInput(string filename) {
    vector<std::vector<char>>* plots = new vector<vector<char>>();
    ifstream input;
    try{
        input.open(filename);
    } catch(exception e) {
        std::cout << "Could not find file \'" << filename << "\'\n";
        return plots;
    }
    
    string line;
    int y = 0;
    while(getline(input, line)) {
        plots->push_back(vector<char>());
        for(int x = 0; x < line.size(); x++) {
            plots->at(y).push_back(line.at(x));
        }
        y++;
    }
    writeOutput("output.txt", plots);
    return plots;
}//readInput

int main() {
    vector<vector<char>>* plots = readInput("input.txt");
    set<Region>* regions = mapRegions(plots);
    return 0;
}//main