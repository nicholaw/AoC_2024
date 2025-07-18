#include <exception>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/**
 * Returns the concatination of the provided numbers.
 * For example, provided 12 and 34, returns 1234
 */
uint64_t concatNum(uint64_t a, uint64_t b) {
    return (std::stoull(std::to_string(a) + std::to_string(b)));
}//concatNum

/**
 * Returns true if the provided number is present in the provided set and false otherwise.
 */
bool contains(uint64_t target, std::vector<uint64_t>* set) {
    for(int i = 0; i < set->size(); i++) {
        if(target == set->at(i)) {
            return true;
        }
    }
    return false;
}//contains

/**
 * Returns the target number if the provided calibration can be solved with legal operators and 0 otherwise.
 */
uint64_t solveCalibration(uint64_t target, std::vector<uint64_t>* operands) {
    std::vector<uint64_t>* products = new std::vector<uint64_t>();
    std::vector<uint64_t>* temp;
    
    for(int i = 0; i < operands->size(); i++) {
        uint64_t next = operands->at(i);
        if(i == 0) {
            products->push_back(next);
        } else {
            temp = new std::vector<uint64_t>();
            for(int j = 0; j < products->size(); j++) {
                temp->push_back(products->at(j) + next);
                temp->push_back(products->at(j) * next);
                temp->push_back(concatNum(products->at(j), next));
            }
            products = temp;
        }
    }

    if(contains(target, products)) {
        return target;
    } else {
        return 0;
    }
}//solveCalibration

/**
 * Parses the provided line into a target calibration and list of operands; returns the target
 * calibration if the line can be solved and zero otherwise.
 */
uint64_t parseLine (std::string line) {
    uint64_t target = 0;
    std::string str = "";
    std::vector<uint64_t>* operands = new std::vector<uint64_t>();
    bool skip = true;
    for(int i = 0; i < line.size(); i++) {
        switch(line.at(i)) {
            case ':':
                target = std::stoull(str);
                str = "";
                break;
            case ' ':
                if(skip) {
                    skip = false;
                } else {
                    operands->push_back(std::stoull(str));
                    str = "";
                }
                break;
            default:
                str += line.at(i);
                break;
        }
    }
    operands->push_back(std::stoull(str));

    return solveCalibration(target, operands);
}//parseLine

/**
 * Reads the provided input file and returns sum of legal calibrations.
 */
uint64_t run(std::string filename) {
    //Open input file; catch FileNotFound Exception
    uint64_t calibrationTotal = 0;
    std::ifstream input;
    try {
        input.open(filename);
    } catch(std::exception e) {
        std::cout << "Could not find file \"" << filename << "\"\n";
        return 0;
    }

    //Read input file
    std::string line;
    while(std::getline(input, line)) {
        calibrationTotal += parseLine(line);
    }

    return calibrationTotal;
}//run

int main() {
    std::cout << std::to_string(run("input.txt"));
    return 0;
}//main