#include <exception>
#include <fstream>
#include <iostream>
#include <string>

int compactMemory(std::string memory) {
    //Write original string to output file
    std::ofstream output;
    output.open("output.txt");
    output << memory << "\n\n";

    int sum = 0;
    int frontPointer = 0;
    int backPointer = (memory.size() - 1);
    bool searchback = true;
    while(frontPointer < backPointer) {
        if(memory.at(frontPointer) == '.') {
            searchback = true;
            while(searchback) {
                if(memory.at(backPointer) != '.') {
                    searchback = false;
                    memory.at(frontPointer) = memory.at(backPointer);
                    memory.at(backPointer) = '.';
                    sum += ((memory.at(frontPointer) - '0') * frontPointer);
                    frontPointer++;
                    backPointer--;
                } else {
                    backPointer--;
                }
            }
        } else {
            sum += ((memory.at(frontPointer) - '0') * frontPointer);
            frontPointer++;
        }
    }
    sum += ((memory.at(frontPointer) - '0') * frontPointer);

    //Write compacted string to output file and then close file.
    output << memory;
    output.close();

    return sum;
}//compactMemory

std::string readInput(std::string filename) {
    std::string memory;
    std::ifstream input;
    try {
        input.open(filename);
    } catch(std::exception e) {
        std::cout << "Could not find file \"" << filename << "\"\n";
        return "";
    }

    std::string line = "";
    std::string str;
    int count;
    int fileID = 0;
    while (std::getline(input, line)) {
        for(int i = 0; i < line.size(); i++) {
            str = line.at(i);
            count = std::stoi(str);
            if((i % 2) == 0) {    //position is a file
                for(int j = 0; j < count; j++) {
                    memory += std::to_string(fileID);
                }
                fileID++;
            } else {            //position is free space
                for(int j = 0; j < count; j++) {
                    memory += ".";
                }
            }
        }
    }
    return memory;
}//readInput

int main() {
    std::cout << compactMemory(readInput("input.txt")) << "\n";
}//main