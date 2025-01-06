#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

const int NUM_OPERATORS = 2;

/**
 * Build map of calibrations from the provided input file.
 */
std::map<int, std::vector<int>> readInput(std::string input) {
    std::ifstream inputFile;
    std::map<int, std::vector<int>> calibrations;
    try {
        inputFile.open(input);
    } catch(std::exception e) {
        std::cout << "Cannot find file \'" << input << "\'\n";
    }
    std::string line;
    std::string str;
    int key;
    bool skip;
    while(std::getline(inputFile, line)) {
        std::vector<int> operands = {};
        skip = true;
        str = "";
        for(char c : line) {
            if(c == ' ') {
                if(skip) {
                    skip = false;
                } else {
                    operands.push_back(std::stoi(str));
                    str = "";
                }
            } else if(c == ':') {
                key = std::stoi(str);
                str = "";
            } else {
                str += c;
            }
        }
        operands.push_back(std::stoi(str));
        calibrations.insert({key, operands});
    }
    return calibrations;
};

/**
 * Writes the provided map to the provided destination.
 */
void writeOutput(std::map<int, std::vector<int>> calibrations, std::string destination) {
    std::ofstream outputFile;
    outputFile.open(destination);
    for(std::pair p : calibrations) {
        outputFile << p.first << " = ";
        for(int i = 0; i < p.second.size(); i++) {
            if(i == p.second.size() - 1) {
                outputFile << calibrations.at(p.first).at(i) << "\n";
            } else {
                outputFile << calibrations.at(p.first).at(i) << " ";
            }
        }
    }
};

/**
 * Retunrs true if the provided int can be reached with a permutation of operators but witout 
 * changing the order of the provided operands.  
 */
bool isSolvable(int target, std::vector<int> operands) {
    int product = operands.at(0);
    int numMultiples = operands.size() - 1;
    for(int i = 0; i < (NUM_OPERATORS^(operands.size() - 1)); i++) {
        for(int j = 1; j < operands.size(); j++) {
            if() {

            } else {

            }
        }
    }
    return false;
}

/**
 * Returns the sum of the provided calibrations which are solvable.
 */
int sumSolvable(std::map<int, std::vector<int>> calibrations) {
    int sum = 0;
    for(std::pair p : calibrations) {
        if(isSolvable(p.first, p.second)) {
            sum += p.first;
        }
    }
    return sum;
};//sumSolvable

int main() {
    std::cout << sumSolvable(readInput("input.txt")) << "\n";
    return 0;
}//main