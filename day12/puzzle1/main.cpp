#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void mapRegions() {
    return;
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
    readInput("input.txt");
    return 0;
}//main