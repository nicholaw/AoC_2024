#include <cstdint>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

const std::string OUT_FILE = "output.txt";
const std::string IN_FILE = "input.txt";

class MemoryBlock {
    private:
        int id;
        int index;
        int size;
        bool moved;
    
    public:
        MemoryBlock(int _id, int _index, int _size) {id = _id; index = _index; size = _size; moved = false;};
        int getId() {return id;};
        int getIndex() {return index;};
        int getSize() {return size;};
        bool getMoved() {return moved;}
        void move(int newIndex) {index = newIndex; moved = true;};
        void resize(int newSize) {size = newSize;};
};

void clearOutputFile(std::string filename) {
    std::ofstream output;
    output.open(filename);
    output << "";
    output.close();
}//clearOutputFile

void writeOutput(std::pair<std::vector<int>*, std::vector<MemoryBlock>*> values, std::string filename) {
    std::ofstream output;
    output.open(filename, std::ios::app);

    //Write output from memory
    for(int i = 0; i < values.first->size(); i++) {
        if(values.first->at(i) < 0) {
            output << ".";
        } else {
            output << "[" << values.first->at(i) << "]";
        }
    }
    //output << "\n";

    //Write output from meta_memory
    /*for(int j = 0; j < values.second->size(); j++) {
        if(values.second->at(j).getId() < 0) {
            for(int k = 0; k < values.second->at(j).getSize(); k++) {
                output << ".";
            }
        } else {
            for(int k = 0; k < values.second->at(j).getSize(); k++) {
                output << "[" << values.second->at(j).getId() << "]";
            }
        }
    }*/

    output << "\n\n";
    output.close();
}//writeOutput

uint64_t checkSum(std::vector<int>* memory) {
    uint64_t sum = 0;
    for(int i = 0; i < memory->size(); i++) {
        if(memory->at(i) >= 0) {
            sum += (i * memory->at(i));
        }
    }
    return sum;
}//checkSum

std::pair<std::vector<int>*, std::vector<MemoryBlock>*> compactMemory(std::pair<std::vector<int>*, std::vector<MemoryBlock>*> memory) {
    //Compact memory based on meta memory data
    for(int i = (memory.second->size() - 1); i >= 0; i--) {
        if(memory.second->at(i).getId() >= 0) {     //Found a file
            for(int j = 0; j < i; j++) {            //Look of free space big enough to acocmodate file
                if(memory.second->at(j).getId() < 0) {//Found free space
                    if(memory.second->at(j).getSize() >= memory.second->at(i).getSize()) {    //Free space is big enough
                        for(int k = 0; k < memory.second->at(i).getSize(); k++) {           //Swap file position
                            memory.first->at(memory.second->at(j).getIndex() + k) = memory.second->at(i).getId();
                            memory.first->at(memory.second->at(i).getIndex() + k) = -1;
                        }
                        //Update size and location of empty space
                        int tempIndex = memory.second->at(j).getIndex();
                        memory.second->at(j).resize(memory.second->at(j).getSize() - memory.second->at(i).getSize());
                        if(memory.second->at(j).getSize() > 0) {
                            memory.second->at(j).move(memory.second->at(j).getIndex() + memory.second->at(i).getSize());
                        }
                        memory.second->at(i).move(tempIndex);
                        j = (i + 1); //Break for-loop; stop looking for free space
                    }
                }
            }
        }
    }
    writeOutput(memory, OUT_FILE);
    return memory;
}//compactMemory

/**
 * Returns a vector of FileBricks representing file and empty space in memory.
 */
std::pair<std::vector<int>*, std::vector<MemoryBlock>*> readInput(std::string filename) {
    std::vector<int>* memory = new std::vector<int>();
    std::vector<MemoryBlock>* meta_memory = new std::vector<MemoryBlock>();
    std::ifstream input;
    try {
        input.open(filename);
    } catch(std::exception e) {
        std::cout << "Could not find file \"" << filename << "\"\n";
        return std::pair(memory, meta_memory);
    }

    std::string line = "";
    int count;
    int fileID = 0;
    int position = 0;
    while (std::getline(input, line)) {
        for(int i = 0; i < line.size(); i++) {
            count = line.at(i) - '0';
            if((i % 2) == 0) {    //position is a file
                meta_memory->push_back(MemoryBlock(fileID, position, count));
                position += count;
                for(int j = 0; j < count; j++) {    //populate memory
                    memory->push_back(fileID);
                }
                fileID++;
            } else {            //position is free space
                meta_memory->push_back(MemoryBlock(-1, position, count));
                position += count;
                for(int j = 0; j < count; j++) {    //populate memory
                    memory->push_back(-1);
                }
            }
        }
    }//while
    std::pair<std::vector<int>*, std::vector<MemoryBlock>*> fullMemory = std::pair(memory, meta_memory);
    writeOutput(fullMemory, OUT_FILE);
    return fullMemory;
}//readInput

int main() {
    clearOutputFile(OUT_FILE);
    std::pair<std::vector<int>*, std::vector<MemoryBlock>*> memory = readInput(IN_FILE);
    compactMemory(memory);
    std::cout << checkSum(memory.first) << "\n";
}//main