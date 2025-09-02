#include <exception>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

//TODO: I think local score is supposed to be the number of destinations, not the number of routes
//i.e. do not count any '9' more than once

int globalScore;
std::vector<std::vector<int>*>* topomap;            //topographical map
std::set<std::pair<int, int>>* potentialTrailheads; //positions of all zeros

enum direction {
    UP,
    DOWN,
    RIGHT,
    LEFT
};

/**
 * Writes topographical map and set of potential trailheads to output file.
 */
void writeOutput(std::string destination) {
    std::ofstream output;
    output.open(destination);
    
    //Write topographical map
    for(int i = 0; i < topomap->size(); i++) {
        for(int j = 0; j < topomap->at(i)->size(); j++) {
            output << topomap->at(i)->at(j);
        }
        output << "\n";
    }
    output << "\n";

    //Write set of potential trailheads
    int maxColumns = 3;
    int currColumn = 0;
    for(std::pair<int, int> p : *potentialTrailheads) {
        if(currColumn >= maxColumns) {
            output << "\n";
            currColumn = 0;
        }
        output << "{" << p.first << ", " << p.second << "}";
        currColumn++;
    }

    output.close();
}//writeOutput

/**
 * Reads input file and stores information of topographical map in 2D vector and position of all
 * numeral zeros in set of pairs.
 */
void readInput(std::string filename) {
    std::ifstream input;
    try {
        input.open(filename);
    } catch(std::exception e) {
        std::cout << "Could not find file \'" << filename << "\'\n";
        return;
    }

    std::string line;
    int next;
    int y = 0;
    while(std::getline(input, line)) {
        topomap->push_back(new std::vector<int>());
        for(int x = 0; x < line.size(); x++) {
            next = line.at(x) - '0';
            topomap->at(y)->push_back(next);
            if(next == 0) {
                potentialTrailheads->insert(std::pair(x, y));
            }
        }
        y++;
    }
    writeOutput("output.txt");
}//readInput

/**
 * Prints the provided score of the provided trailhead to the console.
 */
void printScore(std::pair<int, int> pos, int score) {
    std::cout << "{" << pos.first << ", " << pos.second << "} [" << score << "]\n"; 
}//printScore

/**
 * Returns the element at the given position and -1 if the given position is out of bounds.
 */
int peek(std::pair<int, int> pos) {
    try {
        return topomap->at(pos.second)->at(pos.first);
    } catch(std::exception e) {
        return -1;
    }   
}//peek

void searchTrailhead(direction dir, std::pair<int, int> pos, std::set<std::pair<int, int>>* destinations) {
    int curr = topomap->at(pos.second)->at(pos.first);
    std::pair<int, int> nextpos;
    int next;
    switch(dir) {
    case UP:
        nextpos = std::pair<int, int>(pos.first, pos.second - 1);
        break;
    case DOWN:
        nextpos = std::pair<int, int>(pos.first, pos.second + 1);
        break;
    case RIGHT:
        nextpos = std::pair<int, int>(pos.first + 1, pos.second);
        break;
    case LEFT:
        nextpos = std::pair<int, int>(pos.first - 1, pos.second);
        break;
    default:
        return;
    }
    next = peek(nextpos);
    if(next < 0) {  //Route is out of bounds
        return;
    } else if(curr == 8 && next == 9) {  //Route is valid and complete
        destinations->insert(nextpos);
        return;
    } else if(next == (curr + 1)) { //Route is valid and ongoing
        searchTrailhead(UP, nextpos, destinations);
        searchTrailhead(DOWN, nextpos, destinations);
        searchTrailhead(RIGHT, nextpos, destinations);
        searchTrailhead(LEFT, nextpos, destinations);
        return;
    } else {        //Route is invalid
        return;
    }
}//searchTrailhead

/**
 * Walk through topographical map starting from each potential trailhead and calculate trailhead scores.
 */
void mapTrailheads() {
    std::set<std::pair<int, int>>* destinations; //Discrete peaks reachable from current trailhead
    for(std::pair<int, int> position : *potentialTrailheads) {
        destinations = new std::set<std::pair<int, int>>();
        searchTrailhead(UP, position, destinations);
        searchTrailhead(DOWN, position, destinations);
        searchTrailhead(RIGHT, position, destinations);
        searchTrailhead(LEFT, position, destinations);
        printScore(position, destinations->size());
        globalScore += destinations->size();
    }
}//mapTrailheads

int main() {
    globalScore = 0;
    topomap = new std::vector<std::vector<int>*>();
    potentialTrailheads = new std::set<std::pair<int, int>>();
    readInput("input.txt");
    mapTrailheads();
    std::cout << "(" << globalScore << ")\n";
    return 0;
}//main