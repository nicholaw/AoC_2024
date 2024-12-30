#include <regex>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

//Represents possible table orientations
enum orientation {
    HORIZONTAL,
    VERTICAL,
    DIAGONAL_DOWN,
    DIAGONAL_UP
};

/**
 * Writes the given table to a file with the given filename
 */
void writeTable(std::string filename, std::vector<std::vector<char>> table) {
    std::ofstream output;
    output.open(filename);
    for(std::vector<char> v : table) {
        for(char c : v) {
            output << c;
        }
        output << "\n";
    }
    output.close();
}//writeTable

/**
 * Returns a string containing all characters in the provided vector
 */
std::string buildString(std::vector<char> v) {
    string str = "";
    for(char c : v) {
        str += c;
    }
    return str;
}//buildString

/**
 * Returns a 2D vector represeting the provided table rotated to the specified orientation
 */
std::vector<std::vector<char>> rotateTable(std::vector<std::vector<char>> original, orientation ort) {
    std::vector<std::vector<char>> rotated;
    std::vector<char> v1 = {};
    switch(ort) {
        case HORIZONTAL:
            for(vector<char> v0 : original) {
                v1.clear();
                for(char c : v0) {
                    v1.push_back(c);
                }
                rotated.push_back(v1);
            }
            break;
        case VERTICAL:
            for(int i = original.at(0).size() - 1; i >=0; i--) {
                v1.clear();
                for(int j = 0; j < original.size(); j++) {
                    v1.push_back(original.at(j).at(i));
                }
                rotated.push_back(v1);
            }
            break;
        case DIAGONAL_DOWN:
            for(int i = 0; i < original.at(0).size() - 1; i++) {   //front half
                v1.clear();
                for(int j = 0; j < i + 1; j++) {
                    v1.push_back(original.at(j).at(j + original.at(0).size() - 1 - i));
                }
                rotated.push_back(v1);
            }
            for(int i = original.at(0).size() - 1; i > 0; i--) {   //back half
                v1.clear();
                for(int j = 0; j < i; j++) {
                    v1.push_back(original.at(original.at(0).size() - 1 - i + j).at(j));
                }
                rotated.push_back(v1);
            }
            break;
        case DIAGONAL_UP:
            for(int i = 0; i < (original.at(0).size() - 1); i++) { //front half
                v1.clear();
                for(int j = 0; j < i + 1; j++) {
                    v1.push_back(original.at(i - j).at(j));
                }
                rotated.push_back(v1);
            }
            for(int i = 0; i < original.at(0).size() - 1; i++) { //back half
                v1.clear();
                for(int j = original.at(0).size() - 2; j >= i; j--) {
                    v1.push_back(original.at(j).at((original.at(0).size() - 1) - (j - i)));
                }
                rotated.push_back(v1);
            }
            break;
        default:
            rotated = rotateTable(original, HORIZONTAL);
    }
    return rotated;
}//rotateTable

/**
 * Returns the number of matches to the provided pattern in the provided table
 */
int searchTable(std::vector<std::vector<char>> table, std::regex pattern) {
    std::smatch matches;
    int numMatches = 0;
    std::string str = "";
    for(std::vector<char> v : table) {
        str = buildString(v);
        while(std::regex_search(str, matches, pattern)) {
            numMatches++;
            str = matches.suffix().str();
        }
    }
    return numMatches;
}//searchTable

int main() {
    //Declare variables
    std::ifstream inputFile;
    std::ofstream outputFile;
    //inputFile.open("input.txt");
    inputFile.open("testInput.txt");
    //outputFile.open("output.txt");
    outputFile.open("testOutput.txt");

    std::regex forwardPattern("(XMAS)");
    std::regex backwardPattern("(SAMX)");
    std::vector<std::vector<char>> table;
    std::string line;
    int occurances = 0;

    //Read input file and store in 2D vector
    while(std::getline(inputFile, line)) {
        vector<char> v;
        for(char c : line) {
            v.push_back(c);
        }
        table.push_back(v);
    }

    //Check table read input correctly
    for(std::vector<char> v : table) {
        for(char c : v) {
            outputFile << c;
        }
        outputFile << "\n";
    }

    //Search table in each orientation
    occurances += searchTable(table, forwardPattern);
    occurances += searchTable(table, backwardPattern);
    occurances += searchTable(rotateTable(table, VERTICAL), forwardPattern);
    occurances += searchTable(rotateTable(table, VERTICAL), backwardPattern);
    occurances += searchTable(rotateTable(table, DIAGONAL_DOWN), forwardPattern);
    occurances += searchTable(rotateTable(table, DIAGONAL_DOWN), backwardPattern);
    occurances += searchTable(rotateTable(table, DIAGONAL_UP), forwardPattern);
    occurances += searchTable(rotateTable(table, DIAGONAL_UP), backwardPattern);

    //Print results
    cout << occurances;

    //Close i/o files
    inputFile.close();
    outputFile.close();
    return 0;
}