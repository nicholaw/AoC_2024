#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const std::string INPUT_FILE = "input.txt";
const std::string PATTERN = "XMAS";

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
 * Returns 1 if the next characters in the provided table match the provided pattern and 0 otherwise.
 */
int checkForward(std::vector<std::vector<char>> table, int xpos, int ypos, std::string pattern) {
    try {
        int x = xpos;
        int y = ypos;
        for(int patternIndex = 0; patternIndex < pattern.size(); patternIndex++) {
            if(!(table.at(x).at(y) == pattern.at(patternIndex))) {
                return 0;
            }
            y++;
        }
        return 1;
    } catch(std::exception e) {
        return 0;
    }
}//checkForward

/**
 * Returns 1 if the previus caracters in the provided table match the provided pattern and 0 otherwise.
 */
int checkBackward(std::vector<std::vector<char>> table, int xpos, int ypos, std::string pattern) {
    try {
        int x = xpos;
        int y = ypos;
        for(int patternIndex = 0; patternIndex < pattern.size(); patternIndex++) {
            if(!(table.at(x).at(y) == pattern.at(patternIndex))) {
                return 0;
            }
            y--;
        }
        return 1;
    } catch(std::exception e) {
        return 0;
    }
}//checkBackward

/**
 * Returns 1 if the characters above the provided coordinates match the provided pattern and false otherwise.
 */
int checkUpward(std::vector<std::vector<char>> table, int xpos, int ypos, std::string pattern) {
    try {
        int x = xpos;
        int y = ypos;
        for(int patternIndex = 0; patternIndex < pattern.size(); patternIndex++) {
            if(!(table.at(x).at(y) == pattern.at(patternIndex))) {
                return 0;
            }
            x--;
        }
        return 1;
    } catch(std::exception e) {
        return 0;
    }
}//checkUpward

/**
 * Returns 1 if the characters below the provided coordinates match the proviced pattern and false otherwise.
 */
int checkDownward(std::vector<std::vector<char>> table, int xpos, int ypos, std::string pattern) {
    try {
        int x = xpos;
        int y = ypos;
        for(int patternIndex = 0; patternIndex < pattern.size(); patternIndex++) {
            if(!(table.at(x).at(y) == pattern.at(patternIndex))) {
                return 0;
            }
            x++;
        }
        return 1;
    } catch(std::exception e) {
        return 0;
    }
}//checkDownward

/**
 * Returns 1 if characters above and to the right of the given coordinates match the given pattern and 0 otherwise.
 */
int checkDiagonalUpRight(std::vector<std::vector<char>> table, int xpos, int ypos, std::string pattern) {
    try {
        int x = xpos;
        int y = ypos;
        for(int patternIndex = 0; patternIndex < pattern.size(); patternIndex++) {
            if(!(table.at(x).at(y) == pattern.at(patternIndex))) {
                return 0;
            }
            x--;
            y++;
        }
        return 1;
    } catch(std::exception e) {
        return 0;
    }
}//checkDiagonalUpRight

/**
 * Returns 1 if characters above and to the left of the given coordinates match the given pattern and 0 otherwise.
 */
int checkDiagonalUpLeft(std::vector<std::vector<char>> table, int xpos, int ypos, std::string pattern) {
    try {
        int x = xpos;
        int y = ypos;
        for(int patternIndex = 0; patternIndex < pattern.size(); patternIndex++) {
            if(!(table.at(x).at(y) == pattern.at(patternIndex))) {
                return 0;
            }
            x--;
            y--;
        }
        return 1;
    } catch(std::exception e) {
        return 0;
    }
}//checkDiagonalUpLeft

/**
 * Returns 1 if characters below and to the right of the given coordinates match the given pattern and 0 otherwise.
 */
int checkDiagionalDownRight(std::vector<std::vector<char>> table, int xpos, int ypos, std::string pattern) {
    try {
        int x = xpos;
        int y = ypos;
        for(int patternIndex = 0; patternIndex < pattern.size(); patternIndex++) {
            if(!(table.at(x).at(y) == pattern.at(patternIndex))) {
                return 0;
            }
            x++;
            y++;
        }
        return 1;
    } catch(std::exception e) {
        return 0;
    }
}//checkDiagonalDownRight

/**
 * Returns 1 if characters below and to the right of the given coordinates match the given pattern and 0 otherwise.
 */
int checkDiagionalDownLeft(std::vector<std::vector<char>> table, int xpos, int ypos, std::string pattern) {
    try {
        int x = xpos;
        int y = ypos;
        for(int patternIndex = 0; patternIndex < pattern.size(); patternIndex++) {
            if(!(table.at(x).at(y) == pattern.at(patternIndex))) {
                return 0;
            }
            x++;
            y--;
        }
        return 1;
    } catch(std::exception e) {
        return 0;
    }
}//checkDiagonalDownLeft

/**
 * Returns the number of occurances of the provided pattern originating from the provided xy coordinates.
 */
int findMatch(std::vector<std::vector<char>> table, int xpos, int ypos, std::string pattern) {
    int sum = 0;
    sum += checkForward(table, xpos, ypos, pattern);
    sum += checkBackward(table, xpos, ypos, pattern);
    sum += checkUpward(table, xpos, ypos, pattern);
    sum += checkDownward(table, xpos, ypos, pattern);
    sum += checkDiagonalUpRight(table, xpos, ypos, pattern);
    sum += checkDiagonalUpLeft(table, xpos, ypos, pattern);
    sum += checkDiagionalDownRight(table, xpos, ypos, pattern);
    sum += checkDiagionalDownLeft(table, xpos, ypos, pattern);
    return sum;
}//findMatch

/**
 * Returns the number of occurances of the provided pattern in the provided 2D vector.
 */
int countMatches(std::vector<std::vector<char>> table, std::string pattern) {
    int sum = 0;
    for(int i = 0; i < table.size(); i++) {
        for(int j = 0; j < table.at(i).size(); j++) {
            if(table.at(i).at(j) == pattern.at(0)) {
                sum += findMatch(table, i, j, pattern);
            }
        }
    }
    return sum;
}//countMatches

int main() {
    cout << countMatches(readInput(INPUT_FILE), PATTERN) << "\n";
    return 0;
}//main