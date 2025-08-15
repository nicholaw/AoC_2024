#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "MemoryBrick.h"

void writeOutput(std::vector<MemoryBrick>* values, std::string filename) {
    std::fstream output;
    output.open(filename);
    int id;
    for(int i = 0; i < values->size(); i++) {
        id = values->at(i).getId();
        if(id < 0) {
            output << ".";
        } else {
            output << "[" << id << "]";
        }
    }
    output << "\n";
    output.close();
}

int compactMemory(std::vector<MemoryBrick>* memory) {
    int sum = 0;
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
                    sum += ((memory->at(frontPointer).getId()) * frontPointer);
                    frontPointer++;
                    backPointer--;
                } else {
                    backPointer--;
                }
            }
        } else {
            sum += ((memory->at(frontPointer).getId()) * frontPointer);
            frontPointer++;
        }
    }
    sum += ((memory->at(frontPointer).getId()) * frontPointer);

    writeOutput(memory, "output.txt");
    return sum;
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
    writeOutput(memory, "output.txt");
    return memory;
}//readInput

int main() {
    std::cout << compactMemory(readInput("input.txt")) << "\n";
}//main