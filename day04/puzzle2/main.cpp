#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const std::string INPUT_FILE = "input.txt";
const char FOCUS = 'A';

/**
 * Writes the provided 2D vector to file with the provided name.
 */
void writeOutput(std::vector<std::vector<char>> table, std::string destination) {
    std::ofstream outputFile;
    outputFile.open(destination);
    for(std::vector<char> v : table) {
        for(char c : v) {
            outputFile << c;
        }
        outputFile << "\n";
    }
    outputFile.close();
}//writeOutput

/**
 * Returns a 2D vector of char values read from input file with the provided name.
 */
std::vector<std::vector<char>> readInput(std::string input) {
    std::ifstream inputFile;
    inputFile.open(input);
    std::vector<std::vector<char>> table = {};
    std::string line = "";
    std::vector<char> v = {};
    while(std::getline(inputFile, line)) {
        v.clear();
        for(char c : line) {
            v.push_back(c);
        }
        table.push_back(v);
    }
    inputFile.close();
    return table;
}//readInput

/**
 * Returns true if the characters on the up diagonal spell 'MAS' or 'SAM' and false otherwise.
 */
bool checkLeftDownRightUp(std::vector<std::vector<char>> table, int xpos, int ypos) {
    try {
        int downLeftX = xpos + 1;
        int downLeftY = ypos - 1;
        int upRightX = xpos - 1;
        int upRightY = ypos + 1;
        if(table.at(downLeftX).at(downLeftY) == 'M' && table.at(upRightX).at(upRightY) == 'S') {
            return true;
        } else if(table.at(downLeftX).at(downLeftY) == 'S' && table.at(upRightX).at(upRightY) == 'M') {
            return true;
        } else {
            return false;
        }
    } catch (std::exception e) {
        return false;
    }
}//checkLeftDownRightUp

/**
 * Returns true if the characters on the down diagonal spell 'MAS' or 'SAM' and false otherwise.
 */
bool checkLeftUpRightDown(std::vector<std::vector<char>> table, int xpos, int ypos) {
    try {
        int upLeftX = xpos - 1;
        int upLeftY = ypos - 1;
        int downRightX = xpos + 1;
        int downRightY = ypos + 1;
        if(table.at(upLeftX).at(upLeftY) == 'M' && table.at(downRightX).at(downRightY) == 'S') {
            return true;
        } else if(table.at(upLeftX).at(upLeftY) == 'S' && table.at(downRightX).at(downRightY) == 'M') {
            return true;
        } else {
            return false;
        }
    } catch (std::exception e) {
        return false;
    }
}//checkLeftUpRightDown

/**
 * Returns the number of occurances of the provided pattern in the provided 2D vector.
 */
int countMatches(std::vector<std::vector<char>> table) {
    int sum = 0;
    for(int i = 0; i < table.size(); i++) {
        for(int j = 0; j < table.at(i).size(); j++) {
            if(table.at(i).at(j) == FOCUS) {
                if(checkLeftDownRightUp(table, i, j) && checkLeftUpRightDown(table, i, j)) {
                    sum += 1;
                }
            }
        }
    }
    return sum;
}//countMatches

int main() {
    cout << countMatches(readInput(INPUT_FILE)) << "\n";
    return 0;
}//main