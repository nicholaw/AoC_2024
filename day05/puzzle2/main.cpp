#include "utils.h"

/**
 * Returns false if any prerequisites for the provided key present in the provided update vector are present but appear 
 * after the provided key index and true otherwise.
 */
bool prereqPresentAndOrdered(std::vector<int> searchVector, int keyIndex, std::map<int, std::set<int>> ruleset) {
    if(util::containsKey(ruleset, searchVector.at(keyIndex))) {
        for(int i = 0; i < searchVector.size(); i++) {
            for(int j : ruleset.at(searchVector.at(keyIndex))) {
                if(searchVector.at(i) == j) {
                    if(i >= keyIndex) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}//prereqPresentAndOrdered

/**
 * Returns true if the provided update is legal per the provided ruleset and false otherwise.
 */
bool isLegal(std::vector<int> update, std::map<int, std::set<int>> ruleset) {
    for(int i = 0; i < update.size(); i++) {
        if(!(prereqPresentAndOrdered(update, i, ruleset))) {
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
    for(std::vector<int> v : updates) {
        if(isLegal(v, ruleset)) {
            sum += (v.at(v.size() / 2));
        }
    }
    return sum;
}//coutModes

int main() {
    std::cout << countModes(util::readUpdates("input_updates.txt"), util::readRuleset("input_ruleset.txt")) << "\n";
    return 0;
}