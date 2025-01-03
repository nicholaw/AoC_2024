#pragma once;

#include "mapNode.cpp"
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace util {
    MapNode* parseInput(char c) {
        switch(c) {
            case '.':
                return new MapNode(false);
            case '#':
                return new MapNode(true);
        }
    }

    /**
     * Returns a 2D vector representing the lab map based on the input file of the 
     * provided name.
     */
    std::vector<std::vector<MapNode*>> buildMap(std::string input) {
        //Open input file.
        std::ifstream inputFile;
        try {
            inputFile.open(input);
        } catch(std::exception e) {
            std::cout << "Could not find file \'" << input << "\'\n";
        }

        //Read input file
        std::string line = "";
        while(std::getline(inputFile, line)) {
        }
        inputFile.close();
    }
}//namespace util