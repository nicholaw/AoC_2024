#include "FrequencyMap.h"

/**
 * Updates value at the provided key if it already exists, or inserts the nex key/value pair if it does not. 
 */
bool FrequencyMap::addFreq(std::string freq, std::pair<int, int> pos) {
    try{
        return antennas->at(freq)->insert(pos).second; //key alreay exits; add given coordinate pair to the set at the given key
    } catch(std::exception e) {     
        std::set<std::pair<int, int>>* positions = new std::set<std::pair<int, int>>(); //key does not exist yet; insert a new key/value pair
        positions->insert(pos);
        return antennas->insert(std::pair<std::string, std::set<std::pair<int, int>>*>(freq, positions)).second;
    }
    return false;
}//addFreq

/**
 * Returns a vectors containing all antenna positions for the antenna of the provided frequency.
 */
std::vector<std::pair<int, int>>* FrequencyMap::getAntennaPositions(std::string freq) {
    std::vector<std::pair<int, int>>* positions = new std::vector<std::pair<int, int>>();
    for(const auto& pair : *antennas->at(freq)) {
        positions->push_back(pair);
    }
    return positions;
}//getAntennaPositions

/**
 * Retruns the underlying map representing anntenas and their positions.
 */
std::map<std::string, std::set<std::pair<int, int>>*> FrequencyMap::getMap() {
    return *antennas;
}//getMap