#pragma once

#include <exception>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

class FrequencyMap {
    private:
        std::map<std::string, std::set<std::pair<int, int>>*>* antennas;
    
    public:
        FrequencyMap() {
            antennas = new  std::map<std::string, std::set<std::pair<int, int>>*>();
        };
        ~FrequencyMap() {
            delete antennas;
        };
        bool addFreq(std::string freq, std::pair<int, int> pos);
        std::map<std::string, std::set<std::pair<int, int>>*> getMap();
        std::vector<std::pair<int, int>>* getAntennaPositions(std::string freq);
};