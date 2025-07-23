#pragma once

#include <exception>
#include <map>
#include <set>
#include <string>
#include <utility>

class FrequencyMap {
    private:
        std::map<std::string, std::set<std::pair<int, int>>*>* anntenas;
    
    public:
        FrequencyMap() {
            anntenas = new  std::map<std::string, std::set<std::pair<int, int>>*>();
        };
        ~FrequencyMap() {
            delete anntenas;
        };
        bool addFreq(std::string freq, std::pair<int, int> pos);
        std::map<std::string, std::set<std::pair<int, int>>*> getMap();
};