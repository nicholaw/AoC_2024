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

void moveGuard(std::pair<int, int> position, Orientation orientation) {
    switch(orientation) {
        case UP:
            position.first--;
            break;
        case RIGHT:
            position.second++;
            break;
        case DOWN:
            position.first++;
            break;
        case LEFT:
            position.first--;
            break;
    }
}//moveGuard

void rotateGuard(Orientation orientation) {
    switch(orientation) {
        case UP:
            orientation = RIGHT;
            break;
        case RIGHT:
            orientation = DOWN;
            break;
        case DOWN:
            orientation = LEFT;
            break;
        case LEFT:
            orientation = UP;
            break;
    }
}//rotateGuard

//Throws IndexOutOfBoundsException
bool peekNextNode(std::pair<int, int> pos, Orientation ort, std::vector<std::vector<MapNode*>> map) {
    switch(ort) {
        case UP:
            return map.at(pos.first - 1).at(pos.second) -> isObstructed();
        case RIGHT:
            return map.at(pos.first).at(pos.second + 1) -> isObstructed();
        case DOWN:
            return map.at(pos.first + 1).at(pos.second) -> isObstructed();
        case LEFT:
            return map.at(pos.first).at(pos.second - 1) -> isObstructed();
    }
}//peekNextNode

std::vector<std::vector<MapNode*>> buildLabMap(std::string input) {
    std::ifstream inputFile;
    std::vector<std::vector<MapNode*>> labMap = {};
    try {
        inputFile.open(input);
    } catch(std::exception e) {
        std::cout << "Could not find file \'" << input << "\'\n";
        return labMap;
    }
    std::string line = "";
    while(std::getline(inputFile, line)) {
        std::vector<MapNode*> labRow = {};
        for(char c : line) {
            switch(c) {
                case '.':
                    labRow.push_back(new MapNode(false));
                    break;
                case '#':
                    labRow.push_back(new MapNode(true));
                    break;
                case '^':
                    break;
                case '>':
                    break;
                case 'v':
                    break;
                case '<':
                    break;
            }
        }
        labMap.push_back(labRow);
    }
    inputFile.close();
    return labMap;
}//buildLabMap

int main() {
    std::set<MapNode*> visitedNodes;
    std::vector<std::vector<MapNode*>> labMap;
    std::pair<int, int> guardPosition;
    Orientation guardOrientation;
    return 0;
}