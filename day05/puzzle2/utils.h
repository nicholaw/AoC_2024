#pragma once

#include <exception>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <set>
#include <vector>

namespace util {
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
}