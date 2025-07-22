#pragma once

#include <map>
#include <set>
#include <string>
#include <utility>

class FrequencySet {
    private:
        std::map<std::string, std::pair<int, int>>* anntenas;
    
    public:
        FrequencySet() {
            anntenas = new  std::map<std::string, std::pair<int, int>>();
        };
        ~FrequencySet() {
            delete anntenas;
        };
        bool addFreq(std::string freq, std::pair<int, int> pos);
        bool containsFreq();
};