#include <cstdint>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "MemoryBrick.h"

const std::string OUT_FILE = "output.txt";
const std::string IN_FILE = "input.txt";

void clearOutputFile(std::string filename) {
    std::ofstream output;
    output.open(filename);
    output << "";
    output.close();
}//clearOutputFile

void writeOutput(std::vector<MemoryBrick>* values, std::string filename) {
    std::ofstream output;
    output.open(filename, std::ios::app);
    int id;
    for(int i = 0; i < values->size(); i++) {
        id = values->at(i).getId();
        if(id < 0) {
            output << ".";
        } else {
            output << "[" << id << "]";
        }
    }
    output << "\n\n";
    output.close();
}//writeOutput

uint64_t checkSum(std::vector<MemoryBrick>* memory) {
    uint64_t sum = 0;
    for(int i = 0; i < memory->size(); i++) {
        if(memory->at(i).getId() >= 0) {
            sum += (i * memory->at(i).getId());
        }
    }
    return sum;
}//checkSum

void compactMemory(std::vector<MemoryBrick>* memory) {
    int frontPointer = 0;
    int backPointer = (memory->size() - 1);
    bool searchback = true;
    while(frontPointer < backPointer) {
        if(memory->at(frontPointer).getId() < 0) {
            searchback = true;
            while(searchback) {
                if(memory->at(backPointer).getId() >= 0) {
                    searchback = false;
                    memory->at(frontPointer) = memory->at(backPointer);
                    memory->at(backPointer) = MemoryBrick(-1);
                    frontPointer++;
                    backPointer--;
                } else {
                    backPointer--;
                }
            }
        } else {
            frontPointer++;
        }
    }
    writeOutput(memory, OUT_FILE);
}//compactMemory

std::vector<MemoryBrick>* readInput(std::string filename) {
    std::vector<MemoryBrick>* memory = new std::vector<MemoryBrick>();
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
    while (std::getline(input, line)) {
        for(int i = 0; i < line.size(); i++) {
            count = line.at(i) - '0';
            if((i % 2) == 0) {    //position is a file
                for(int j = 0; j < count; j++) {
                    memory->push_back(MemoryBrick(fileID));
                }
                fileID++;
            } else {            //position is free space
                for(int j = 0; j < count; j++) {
                    memory->push_back(MemoryBrick(-1));
                }
            }
        }
    }
    writeOutput(memory, OUT_FILE);
    return memory;
}//readInput

int main() {
    clearOutputFile(OUT_FILE);
    std::vector<MemoryBrick>* memory = readInput(IN_FILE);
    compactMemory(memory);
    std::cout << checkSum(memory) << "\n";
}//main