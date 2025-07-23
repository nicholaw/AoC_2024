#include "FrequencyMap.h"

/**
 * Updates value at the provided key if it already exists, or inserts the nex key/value pair if it does not. 
 */
bool FrequencyMap::addFreq(std::string freq, std::pair<int, int> pos) {
    try{
        return anntenas->at(freq)->insert(pos).second; //key alreay exits; add given coordinate pair to the set at the given key
    } catch(std::exception e) {     
        std::set<std::pair<int, int>>* positions = new std::set<std::pair<int, int>>(); //key does not exist yet; insert a new key/value pair
        positions->insert(pos);
        return anntenas->insert(std::pair<std::string, std::set<std::pair<int, int>>*>(freq, positions)).second;
    }
    return false;
}//addFreq

/**
 * Retruns the underlying map representing anntenas and their positions.
 */
std::map<std::string, std::set<std::pair<int, int>>*> FrequencyMap::getMap() {
    return *anntenas;
}//getMap