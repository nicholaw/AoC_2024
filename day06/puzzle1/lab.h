#pragma once

#include <exception>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

enum Orientation {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

class MapNode {
    private:
        bool obstructed;
    
    public:
        MapNode(bool ob) {
            obstructed = ob;
        }

        bool isObstructed() {
            return obstructed;
        }
};

class Lab {
    private:
        std::pair<int, int>* guardPosition;
        Orientation guardOrientation;
        std::vector<std::vector<MapNode*>*>* labMap;
        std::set<MapNode*>* visitedNodes;
        void buildLabMap(std::string input);
        void moveGuard();
        bool peekNextNode();
        void rotateGuard();
    
    public:
        Lab(std::string input);
        ~Lab(){
            delete guardPosition;
            delete labMap;
            delete visitedNodes;
        };
        void writeLabMap(std::string destination);
        int run();
};