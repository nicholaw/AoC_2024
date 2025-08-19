#include <cstdint>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "FileBrick.h"

const std::string OUT_FILE = "output.txt";
const std::string IN_FILE = "input.txt";

void clearOutputFile(std::string filename) {
    std::ofstream output;
    output.open(filename);
    output << "";
    output.close();
}//clearOutputFile

void writeOutput(std::vector<FileBrick>* values, std::string filename) {
    std::ofstream output;
    output.open(filename, std::ios::app);
    int id;
    for(int i = 0; i < values->size(); i++) {
        id = values->at(i).getId();
        if(id < 0) {
            for(int j = 0; j < values->at(i).getSize(); j++) {
                output << ".";
            }
        } else {
            for(int j = 0; j < values->at(i).getSize(); j++) {
                output << "[" << id << "]";
            }
        }
    }
    output << "\n\n";
    output.close();
}//writeOutput

uint64_t checkSum(std::vector<FileBrick>* memory) {
    uint64_t sum = 0;
    for(int i = 0; i < memory->size(); i++) {
        if(memory->at(i).getId() >= 0) {
            sum += (i * memory->at(i).getId());
        }
    }
    return sum;
}//checkSum

void compactMemory(std::vector<FileBrick>* memory) {
    for(int i = (memory->size() - 1); i >= 0; i--) {
        if(memory->at(i).getId >= 0 && !(memory->at(i).wasMoved)) {         //location is an unmoved file
            for(int j = 0; j < i; j++) {                                    //search left to right for adequate space
                if(memory->at(j).getId() < 0) {                             //location is empty space
                    if(memory->at(j).getSize() > memory->at(i).getSize()) { //location has more than enough space to hold file
                        //Create new FileBrick with empty space and shift array right

                    } else if(memory->at(j).getSize() == memory->at(i).getSize()) { //location has just enough space to hold file
                        //Simply swap file with empty space
                        FileBrick temp = memory->at(j);
                        memory->at(i).move(0, 0);
                        memory->at(j) = memory->at(i);
                        memory->at(i) = temp;
                    }
                }
            }
        }
    }
    writeOutput(memory, OUT_FILE);
}//compactMemory

/**
 * Returns a vector of FileBricks representing file and empty space in memory.
 */
std::vector<FileBrick>* readInput(std::string filename) {
    std::vector<FileBrick>* memory = new std::vector<FileBrick>();
    std::ifstream input;
    try {
        input.open(filename);
    } catch(std::exception e) {
        std::cout << "Could not find file \"" << filename << "\"\n";
        return memory;
    }

    std::string line = "";
    int count;
    int fileID = 0;
    int memoryPosition = 0;
    while (std::getline(input, line)) {
        for(int i = 0; i < line.size(); i++) {
            count = line.at(i) - '0';
            if((i % 2) == 0) {    //position is a file
                memory->push_back(FileBrick(fileID, memoryPosition, (memoryPosition + count)));
                fileID++;
            } else {            //position is free space
                memory->push_back(FileBrick(-1, memoryPosition, (memoryPosition + count)));
            }
        }
    }
    writeOutput(memory, OUT_FILE);
    return memory;
}//readInput

int main() {
    clearOutputFile(OUT_FILE);
    std::vector<FileBrick>* memory = readInput(IN_FILE);
    compactMemory(memory);
    std::cout << checkSum(memory) << "\n";
}//main