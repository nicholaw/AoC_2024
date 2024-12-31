#include "utils.h"

/**
 * Returns true if the provide key in not contained in the provided ruleset or if a key-value is present in the 
 * provided search vector and false otherwise.
 */
bool prereqPresent(std::vector<int> searchvector, int end, std::map<int, std::set<int>> ruleset, int key) {
    if(!util::containsKey(ruleset, key)) {
        return true;
    }
    for(int i = 0; i < end; i++) {
        if(util::contains(ruleset.at(key), searchvector.at(i))) {
           return true; 
        }
    }
    return false;
}//prereqPresent

/**
 * Returns true if the provided update is legal per the provided ruleset and false otherwise.
 */
bool isLegal(std::vector<int> update, std::map<int, std::set<int>> ruleset) {
    for(int i = 0; i < update.size(); i++) {
        if(!prereqPresent(update, i, ruleset, update.at(i))) {
            return false;
        }
    }
    return true;
}//isLegal

/**
 * Returns the sum of the mode of each legal update from the provided updates based on the provided ruleset.
 */
int countModes(std::vector<std::vector<int>> updates, std::map<int, std::set<int>> ruleset) {
    int sum = 0;
    std::vector<std::vector<int>> legalUpdates;
    for(std::vector<int> v : updates) {
        if(isLegal(v, ruleset)) {
            legalUpdates.push_back(v);
            sum += (v.at(v.size() / 2));
        }
    }
    util::writeUpdates(legalUpdates, "output_updates.txt");
    return sum;
}//coutModes

int main() {
    std::cout << countModes(util::readUpdates("input_updates.txt"), util::readRuleset("input_ruleset.txt")) << "\n";
    return 0;
}