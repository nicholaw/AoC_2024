#include <exception>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <set>
#include <vector>

/**
 * Returns true if the provided map contains the provided key and false otherwise.
 */
bool containsKey(std::map<int, std::set<int>> searchMap, int targetKey) {
    for(std::pair p : searchMap) {
        if(p.first == targetKey) {
            return true;
        }
    }
    return false;
}//containsKey

/**
 * Returns true if the provided key in the provided map contains the provided value and false otherwise.
 */
bool contains(std::set<int> searchVector, int targetValue) {
    for(int i : searchVector) {
        if(i == targetValue) {
            return true;
        }
    }
    return false;
}//containsValue

/**
 * Writes the provided ruleset (map<int, vector<int>>) to the provided destination.
 */
void writeRuleset(std::map<int, std::set<int>> ruleset, std::string destination) {
    std::ofstream outputFile;
    outputFile.open(destination);
    for(std::pair p : ruleset) {
        outputFile << p.first << " | ";
        for(int i : p.second) {
            outputFile << i << " ";
        }
        outputFile << "\n";
    }
    outputFile.close();
}//writeRuleset

/**
 * Writes the provided 2D vector to the provided destination.
 */
void writeUpdates(std::vector<std::vector<int>> updates, std::string destination) {
    std::ofstream outputFile;
    outputFile.open(destination);
    for(std::vector<int> v : updates) {
        for(int i = 0; i < v.size(); i++) {
            if(i == (v.size() - 1)) {
                outputFile << v.at(i) << "\n";
            } else {
                outputFile << v.at(i) << ", ";
            }
        }
    }
    outputFile.close();
}//writeUpdates

/**
 * Returns a map<int, set<int>> containing the prereq. rules from the provided input file.
 */
std::map<int, std::set<int>> readRuleset(std::string input) {
    std::map<int, std::set<int>> ruleset = {};
    std::string line = "";
    try {
        std::ifstream inputFile;
        inputFile.open(input);
        int key = -1;
        std::string str;
        while(std::getline(inputFile, line)) {
            str = "";
            std::set<int> values = {};          //Create a new set to hold values
            for(char c : line) {
                if(c == '|') {
                    values.insert(std::stoi(str));
                    str = "";
                } else {
                    str += c;
                }
            }
            key = std::stoi(str);
            if(containsKey(ruleset, key)) {     //If key alreay exists in ruleset, add values
                for(int i : values) {
                    ruleset.at(key).insert(i);
                }
            } else {                            //If key does not already exist, insert key-value pair
                ruleset.insert({key, values});
            }
        }
        inputFile.close();
    } catch(std::exception e) {
        std::cout << "Could not find file \'" << input << "\'\n"; 
    }
    return ruleset;
}//readRuleset

/**
 * Returns a vector<vector<int>> of the updates from the provided input file.
 */
std::vector<std::vector<int>> readUpdates(std::string input) {
    std::vector<std::vector<int>> updates = {};
    std::ifstream inputFile;
    try{
        inputFile.open(input);
    } catch(std::exception e) {
        std::cout << "Could not find file \'" << input << "\'\n";
        return updates;
    }
    std::string line = "";
    std::string str = "";
    while(std::getline(inputFile, line)) {
        str = "";
        std::vector<int> values = {};
        for(char c : line) {
            if(c == ',') {
                values.push_back(std::stoi(str));
                str = "";
            } else {
                str += c;
            }
        }
        values.push_back(std::stoi(str));
        updates.push_back(values);
    }
    inputFile.close();
    return updates;
}//readUpdates

/**
 * Returns true if the provide key in not contained in the provided ruleset or if a key-value is present in the 
 * provided search vector and false otherwise.
 */
bool prereqPresent(std::vector<int> searchvector, int end, std::map<int, std::set<int>> ruleset, int key) {
    if(!containsKey(ruleset, key)) {
        return true;
    }
    for(int i = 0; i < end; i++) {
        if(contains(ruleset.at(key), searchvector.at(i))) {
           return true; 
        }
    }
    return false;
}//prereqPresent

/**
 * Returns true if the provided update is legal per the provided ruleset and false otherwise.
 */
bool isLegal(std::vector<int> update, std::map<int, std::set<int>> ruleset) {
    for(int i = 0; i < update.size(); i++) {
        if(!prereqPresent(update, i, ruleset, update.at(i))) {
            return false;
        }
    }
    return true;
}//isLegal

/**
 * Returns the sum of the mode of each legal update from the provided updates based on the provided ruleset.
 */
int countModes(std::vector<std::vector<int>> updates, std::map<int, std::set<int>> ruleset) {
    int sum = 0;
    for(std::vector<int> v : updates) {
        if(isLegal(v, ruleset)) {
            sum += (v.at(v.size() / 2));
        }
    }
    return sum;
}//coutModes

int main() {
    //writeRuleset(readRuleset("input_ruleset.txt"), "output_ruleset.txt");
    //writeUpdates(readUpdates("input_updates.txt"), "output_updates.txt");
    std::cout << countModes(readUpdates("input_updates.txt"), readRuleset("input_ruleset.txt")) << "\n";
    return 0;
}