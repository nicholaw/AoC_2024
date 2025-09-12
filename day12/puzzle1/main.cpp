#include <exception>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include "Region.h"

using namespace std;

/**
 * Returns the sum of the products of the areas and perimeters of each region
 * in the provided set of regions.
 */
int calculateCost(const set<Region>& regions) {
    int totalCost = 0;
    pair<int, int> p;
    for(Region r : regions) {
        r.printInfo();
        p = r.getMeasurements();
        totalCost += (p.first * p.second);
    }
    return totalCost;
}//calculateCost

/**
 * Prints each of the regions contained in the provided set.
 */
void printRegions(const set<Region>& regions) {
    for(Region r : regions) {
        r.printInfo();
    }
}//printRegions

/**
 * Search plots adjacent to the plot at the provided position in the provided table for plots that
 * match the crop in the provided region and add that plot to the provided region if the crops do match.
 */
void searchNeighbors(vector<vector<char>>& table, const pair<int, int>& pos, Region& region) {
    table.at(pos.first).at(pos.second) = '.';
    int localPerimeter = 0;
    int row = 0; 
    int column = 0;
    try { //search up
        row = pos.first - 1; column = pos.second;
        if(region.cropsMatch(table.at(row).at(column))) {
            searchNeighbors(table, pair<int, int>(row, column), region);
        } else {
            localPerimeter++;
        }
    } catch(exception a) { //out of bounds
        localPerimeter++;
    }
    try { //search down
        row = pos.first + 1; column = pos.second;
        if(region.cropsMatch(table.at(row).at(column))) {
            searchNeighbors(table, pair<int, int>(row, column), region);
        } else {
            localPerimeter++;
        }
    } catch(exception a) { //out of bounds
        localPerimeter++;
    }
    try { //search right
        row = pos.first; column = pos.second + 1;
        if(region.cropsMatch(table.at(row).at(column))) {
            searchNeighbors(table, pair<int, int>(row, column), region);
        } else {
            localPerimeter++;
        }
    } catch(exception a) { //out of bounds
        localPerimeter++;
    }
    try { //search left
        row = pos.first; column = pos.second - 1;
        if(region.cropsMatch(table.at(row).at(column))) {
            searchNeighbors(table, pair<int, int>(row, column), region);
        } else {
            localPerimeter++;
        }
    } catch(exception a) { //out of bounds
        localPerimeter++;
    }
    region.addPlot(localPerimeter);
}//searchNeighbors

/**
 * Maps discrete regions of common crops in the provided 2D array of plots.
 */
int mapRegions(vector<vector<char>>* plots) {
    set<Region>* regions = new set<Region>();
    int totalCost = 0;
    int curr = 0;
    for(int row = 0; row < plots->size(); row++) {
        for(int column = 0; column < plots->at(row).size(); column++) {
            if(plots->at(row).at(column) != '.') {
                Region r = Region(plots->at(row).at(column), curr);
                regions->insert(r);
                searchNeighbors(*plots, pair<int, int>(row, column), r);
                curr++;                                                     //At this point, r has expected area and perimeter.
                pair<int, int> p = r.getMeasurements();
                totalCost += (p.first * p.second);
            }
        }//loop through columns
    }//loop through rows
    return totalCost;                                                         //At this point, each region is back to area = perimeter = 0.
}//mapRegions

/**
 * Writes contents of the provided 2D arary to a text file with the provided name.
 */
void writeOutput(string destination, const vector<vector<char>>& table) {
    ofstream output;
    output.open(destination);
    for(int i = 0; i < table.size(); i++) {
        for(int j = 0; j < table.at(i).size(); j++) {
            output << table.at(i).at(j);
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
    writeOutput("output.txt", *plots);
    return plots;
}//readInput

int main() {
    vector<vector<char>>* plots = readInput("input.txt");
    int totalCost = mapRegions(plots);
    cout << "Total: " << totalCost << "\n";
    return 0;
}//main