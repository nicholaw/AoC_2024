#include <exception>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

struct Region {
    private:
        char crop;
        int perimeter;
        int area;
    
    public:
        Region(char _crop) {crop = _crop; perimeter = 0; area = 0;};
        void addPlot(int localPerimeter) {area++; perimeter += localPerimeter;};
        std::pair<int, int> getMeasurments() {return std::pair<int, int>(area, perimeter);};
        bool isMatch(char target) {return crop == target;};
};

/**
 * Returns the total cost of fencing by summing the product of area x perimeter of each regions 
 * contained in the provided set.
 */
int calculateCost(std::set<Region>* regions) {
    int total = 0;
    std::pair<int, int> p;
    for(Region r : *regions) {
        p = r.getMeasurments();
        total += (p.first * p.second);
    }
    return total;
}//calculateCost

/**
 * Adds the plot at the provided location to th provided regions and searches neighboring positions
 * for additional plots to add.
 */
void searchNeighbors(std::vector<std::vector<char>*>* array, std::pair<int, int> pos, Region region) {
    array->at(pos.first)->at(pos.second) = '.';
    int localPerimeter = 0;
    try {//searchUP
        if(region.isMatch(array->at(pos.first - 1)->at(pos.second))) {
            searchNeighbors(array, std::pair<int, int>(pos.first - 1, pos.second), region);
        } else {
            localPerimeter++;
        }
    } catch(std::exception a) {//OutOfBounds
        localPerimeter++;
    }
    try {//searchDOWN
        if(region.isMatch(array->at(pos.first + 1)->at(pos.second))) {
            searchNeighbors(array, std::pair<int, int>(pos.first + 1, pos.second), region);
        } else {
            localPerimeter++;
        }
    } catch(std::exception b) {//OutOfBounds
        localPerimeter++;
    }
    try {//searchRIGHT
        if(region.isMatch(array->at(pos.first)->at(pos.second + 1))) {
            searchNeighbors(array, std::pair<int, int>(pos.first, pos.second + 1), region);
        } else {
            localPerimeter++;
        }
    } catch(std::exception c) {//OutOfBounds
        localPerimeter++;
    }
    try {//searchLEFT
        if(region.isMatch(array->at(pos.first)->at(pos.second - 1))) {
            searchNeighbors(array, std::pair<int, int>(pos.first, pos.second - 1), region);
        } else {
            localPerimeter++;
        }
    } catch(std::exception d) {//OutOfBounds
        localPerimeter++;
    }
    region.addPlot(localPerimeter);
    return;
}//searchNeighbors

/**
 * Returns a set of all regions in the provided 2D array.
 */
std::set<Region>* mapRegions(std::vector<std::vector<char>*>* array) {
    std::set<Region>* regions = new std::set<Region>();
    for(int y = 0; y < array->size(); y++) {
        for(int x = 0; x < array->at(y)->size(); x++) {
            if(array->at(y)->at(x) != '.') {
                Region region = Region(array->at(y)->at(x));
                searchNeighbors(array, std::pair(y, x), region);
                regions->insert(region);
            }
        }
    }
    return regions;
}//mapRegions

/**
 * Writes contents of the provided 2D arary to a text file with the provided name.
 */
void writeOutput(std::string destination, std::vector<std::vector<char>*>* array) {
    std::ofstream output;
    output.open(destination);
    for(int i = 0; i < array->size(); i++) {
        for(int j = 0; j < array->at(i)->size(); j++) {
            output << array->at(i)->at(j);
        }
        output << "\n";
    }
    output.close();
}//writeOutput

/**
 * Generates a 2D array of all plots from puzzle input.
 */
std::vector<std::vector<char>*>* readInput(std::string filename) {
    std::vector<std::vector<char>*>* plots = new std::vector<std::vector<char>*>();
    std::ifstream input;
    try{
        input.open(filename);
    } catch(std::exception e) {
        std::cout << "Could not find file \'" << filename << "\'\n";
        return plots;
    }
    
    std::string line;
    int y = 0;
    while(std::getline(input, line)) {
        plots->push_back(new std::vector<char>());
        for(int x = 0; x < line.size(); x++) {
            plots->at(y)->push_back(line.at(x));
        }
        y++;
    }
    writeOutput("output.txt", plots);
    return plots;
}//readInput

int main() {
    std::cout << calculateCost(mapRegions(readInput("input.txt"))) << "\n";
    return 0;
}//main