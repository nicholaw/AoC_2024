#include "lab.h"

/**
 * 
 */
void Lab::buildLabMap(std::string input) {
    std::ifstream inputFile;
    try {
        inputFile.open(input);
    } catch(std::exception e) {
        std::cout << "Could not find file \'" << input << "\'\n";
    }
    std::string line = "";
    int x = 0;
    while(std::getline(inputFile, line)) {
        std::vector<MapNode*>* labRow = new std::vector<MapNode*>();
        for(int y = 0; y < line.size(); y++) {
            switch(line.at(y)) {
                case '.':
                    labRow->push_back(new MapNode(false));
                    break;
                case '#':
                    labRow->push_back(new MapNode(true));
                    break;
                case '^':
                    guardPosition = new std::pair<int, int>(x, y);
                    guardOrientation = UP;
                    labRow->push_back(new MapNode(false));
                    break;
                case '>':
                    guardPosition = new std::pair<int, int>(x, y);
                    guardOrientation = RIGHT;
                    labRow->push_back(new MapNode(false));
                    break;
                case 'v':
                    guardPosition = new std::pair<int, int>(x, y);
                    guardOrientation = DOWN;
                    labRow->push_back(new MapNode(false));
                    break;
                case '<':
                    guardPosition = new std::pair<int, int>(x, y);
                    guardOrientation = LEFT;
                    labRow->push_back(new MapNode(false));
                    break;
            }
        }//while
        labMap->push_back(labRow);
        x++;
    }
    inputFile.close();
}//buildLabMap

/**
 * Moves the guard one step forward in the direction she is oriented.
 */
void Lab::moveGuard() {
    switch(guardOrientation) {
        case UP:
            guardPosition->first--;
            break;
        case RIGHT:
            guardPosition->second++;
            break;
        case DOWN:
            guardPosition->first++;
            break;
        case LEFT:
            guardPosition->second--;
            break;
    }
}//moveGuard

/**
 * Returns true if the next node in front of the guard is obstructed and false otherwise.
 * 
 * Throws IndexOutOfBoundsException.
 */
bool Lab::peekNextNode() {
    switch(guardOrientation) {
        case UP:
            return labMap->at(guardPosition->first - 1)->at(guardPosition->second)->isObstructed();
        case RIGHT:
            return labMap->at(guardPosition->first)->at(guardPosition->second + 1)->isObstructed();
        case DOWN:
            return labMap->at(guardPosition->first + 1)->at(guardPosition->second)->isObstructed();
        case LEFT:
            return labMap->at(guardPosition->first)->at(guardPosition->second - 1)->isObstructed();
        default:
            return false;
    }
}//peekNextNode

/**
 * Rotates the guard's orientation based on her current orientation.
 */
void Lab::rotateGuard() {
    switch(guardOrientation) {
        case UP:
            guardOrientation = RIGHT;
            break;
        case RIGHT:
            guardOrientation = DOWN;
            break;
        case DOWN:
            guardOrientation = LEFT;
            break;
        case LEFT:
            guardOrientation = UP;
            break;
    }
}//rotateGuard

void Lab::writeLabMap(std::string destination) {
    std::ofstream outputFile;
    outputFile.open(destination);
    for(int i = 0; i < labMap->size(); i++) {
        for(int j = 0; j < labMap->at(i)->size(); j++) {
            if(labMap->at(i)->at(j)->isObstructed()) {
                outputFile << "#";
            } else if(i == guardPosition->first && j == guardPosition->second) {
                switch(guardOrientation) {
                    case UP:
                        outputFile << "^";
                        break;
                    case RIGHT:
                        outputFile << ">";
                        break;
                    case DOWN:
                        outputFile << "v";
                        break;
                    case LEFT:
                        outputFile << "<";
                        break;
                }
            } else {
                if(labMap->at(i)->at(j)->wasVisited()) {
                    outputFile << "X";
                } else {
                    outputFile << ".";
                }
            }
        }
        if(i < (labMap->size() - 1)) {
            outputFile << "\n";
        }
    }
    outputFile.close();
}//writeLabMap

int Lab::run() {
    try {
        int i = 0;
        while(i < 2147483647) {
            labMap->at(guardPosition->first)->at(guardPosition->second)->visit();
            visitedNodes->insert(labMap->at(guardPosition->first)->at(guardPosition->second));
            if (peekNextNode()) {
                rotateGuard();
            } else {
                moveGuard();
            }
            i++;
        }
    } catch (std::exception e) {
        writeLabMap("output.txt");
        return visitedNodes->size();
    }
    return -1;
}//run

Lab::Lab(std::string input) {
    labMap = new std::vector<std::vector<MapNode*>*>();
    visitedNodes = new std::set<MapNode*>();
    buildLabMap(input);
}//constructor