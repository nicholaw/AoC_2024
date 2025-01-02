#include "utils.h"

/**
 * If the provided update does not conform to the provided ruleset, returns a pair containing the index of the 'key' element and
 * the index of the misordered prerequisite {keyIndex, prereqIndex}; returns a pair containing {-1, -1} otherwise.
 */
std::pair<int, int> prereqPresentAndOrdered(std::vector<int> searchVector, int keyIndex, std::map<int, std::set<int>> ruleset) {
    if(util::containsKey(ruleset, searchVector.at(keyIndex))) {
        for(int i = 0; i < searchVector.size(); i++) {
            for(int j : ruleset.at(searchVector.at(keyIndex))) {
                if(searchVector.at(i) == j) {
                    if(i >= keyIndex) {
                        return {keyIndex, i};
                    }
                }
            }
        }
    }
    return {-1, -1};
}//prereqPresentAndOrdered

/**
 * Returns true if the provided update is legal per the provided ruleset and false otherwise.
 */
std::pair<int, int> isLegal(std::vector<int> update, std::map<int, std::set<int>> ruleset) {
    for(int i = 0; i < update.size(); i++) {
        std::pair<int, int> report = prereqPresentAndOrdered(update, i, ruleset);
        if(report.first != -1) {
            return report;
        }
    }
    return {-1, -1};
}//isLegal

/**
 * Rearranges elements in the provided update to conform with the provided ruleset then returns the middle element of the
 * conforming update.
 */
int correctOrder(std::vector<int> update, std::map<int, std::set<int>> ruleset) {
    bool isIllegal = true;
    int temp;
    int count = -1;
    std::pair<int, int> illegalIndexes;
    while(isIllegal) {
        count++;
        illegalIndexes = isLegal(update, ruleset);
        if(illegalIndexes.first == -1) {
            isIllegal = false;
        } else {
            temp = update.at(illegalIndexes.first);
            update.at(illegalIndexes.first) = update.at(illegalIndexes.second);
            update.at(illegalIndexes.second) = temp;
        }
    }
    if(count > 0) {
        return update.at(update.size() / 2);
    } else {
        return count;
    }
}//correctOrder

/**
 * Returns the sum of the mode of each legal update from the provided updates based on the provided ruleset.
 */
int countModes(std::vector<std::vector<int>> updates, std::map<int, std::set<int>> ruleset) {
    int sum = 0;
    int lineNum = 0;
    for(std::vector<int> v : updates) {
        sum += correctOrder(v, ruleset);
        std::cout << "Finished update line: " << lineNum << "\n";
        lineNum++;
    }
    return sum;
}//coutModes

int main() {
    std::cout << countModes(util::readUpdates("input_updates.txt"), util::readRuleset("input_ruleset.txt")) << "\n";
    return 0;
}