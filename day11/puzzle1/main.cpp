#include <exception>
#include <fstream>
#include <iostream>
#include "stonelist.h"

void clearOutput(std::string filename) {
    std::ofstream output;
    output.open(filename);
    output << "";
    output.close();
}//clearOutputFile

void writeOutput(std::string filename, std::vector<int>* values) {
    std::ofstream output;
    output.open(filename, std::ios::app);
    int index = 0;
    for(index; index < values->size() - 1; index++) {
        output << values->at(index) << " ";
    }
    output << values->at(index) << "\n";
    output.close();
}//writeOutput

void readInput(std::string filename, StoneList* list) {
    std::ifstream input;
    try {
        input.open(filename);
    } catch(std::exception e) {
        std::cout << "Could not find file \"" << filename << "\"\n";
        return;
    }

    std::string line = "";
    std::string num = "";
    while(std::getline(input, line)) {
        for(int i = 0; i < line.size(); i++) {
            if(line.at(i) == ' ') {
                list->append(new Stone(std::stoi(num)));
                num = "";
            } else {
                num += line.at(i);
            }
        }
        list->append(new Stone(std::stoi(num)));
    }
}//readInput

int main() {
    StoneList* list = new StoneList();
    clearOutput("output.txt");
    readInput("input.txt", list);
    writeOutput("output.txt", list->toArray());
    return 0;
}