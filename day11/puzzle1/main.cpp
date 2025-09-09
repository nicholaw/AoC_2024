#include <cstdint>
#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

std::map<uint64_t, uint8_t>* stoneline;

void clearOutput(std::string filename) {
    std::ofstream output;
    output.open(filename);
    output << "";
    output.close();
}//clearOutputFile

void writeOutput(std::string filename, int blinks) {
    std::ofstream output;
    output.open(filename, std::ios::app);
    output << blinks << ": ";
    for(const auto& pair : *stoneline) {
        for(int i = 0; i < pair.second; i++) {
            output << pair.first << " ";
        }
    }
    output << "\n";
    output.close();
}//writeOutput

void readInput(std::string filename) {
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
                stoneline->insert({std::stoull(num), 1});
                num = "";
            } else {
                num += line.at(i);
            }
        }
        stoneline->insert({std::stoull(num), 1});
    }
}//readInput

bool rule1(uint64_t value) {
    return value == 0;
}//rule1

bool rule2(uint64_t value) {
    std::string str = std::to_string(value);
    return (str.size() % 2) == 0;
}//rule2

std::pair<uint64_t, uint64_t> splitValue(uint64_t value) {
    std::string str = std::to_string(value);
    std::string front = "";
    std::string back = "";
    int index = 0;
    while(index < (str.size() / 2)) {
        front += str.at(index);
        index++;
    }
    while(index < str.size()) {
        back += str.at(index);
        index++;
    }
    return std::pair<uint64_t, uint64_t>(std::stoull(front), std::stoull(back));
}//splitValue

uint64_t countMap() {
    uint64_t sum = 0;
    for(const auto& pair : *stoneline) {
        sum += pair.second;
    }
    return sum;
}//countMap

bool addToMap(uint64_t key, uint8_t value, std::map<uint64_t, uint8_t>* map) {
    try {
        map->at(key) += value;
        return true;
    } catch(std::exception e) {
        return map->insert(std::pair{key, value}).second;
    }
    return false;
}//addToMap

void blink(int count) {
    writeOutput("output.txt", 0);
    for(int i = 0; i < count; i++) {
        std::cout << "Blink " << (i + 1) << "...";
        std::map<uint64_t, uint8_t>* temp = new std::map<uint64_t, uint8_t>();
        for (const auto& pair : *stoneline) {
            if(rule1(pair.first)) {
                addToMap(1, pair.second, temp);
            } else if(rule2(pair.first)) {
                std::pair<uint64_t, uint64_t> newValues = splitValue(pair.first);
                addToMap(newValues.first, pair.second, temp);
                addToMap(newValues.second, pair.second, temp);
            } else {
                addToMap(pair.first * 2024, pair.second, temp);
            }
        }
        stoneline = nullptr;
        stoneline = temp;
        if(i < 6) {
            writeOutput("output.txt", (i + 1));
        }
        std::cout << "complete (" << countMap() << ")\n";
    }
}//blink

int main() {
    stoneline = new std::map<uint64_t, uint8_t>();
    clearOutput("output.txt");
    readInput("input.txt");
    blink(75);
    std::cout << countMap() << "\n";
    return 0;
}