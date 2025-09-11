#include <exception>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

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
    return 0;
}//main