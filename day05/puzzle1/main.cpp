#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

/**
 * Returns true if the provided map contains the provided in as a key 
 * and false otherwise.
 */
bool containsKey(map<int, vector<int>> map, int target) {
    for(std::pair p : map) {
        if(p.first == target) {
            return true;
        }
    }
    return false;
}//containsKey

/**
 * Returns true if...
 */
bool isLegal(std::vector<int> update, std::map<int, vector<int>> ruleset) {
    return false;
}//isLegal

int main() {
    //Declare and open i/o files
    std::ifstream ruleInput;
    std::ifstream updateInput;
    std::ofstream ruleOutput;
    ruleInput.open("input_rules.txt");
    updateInput.open("input_updates.txt");
    ruleOutput.open("output_rules.txt");

    //Declare other variables
    std::map<int, vector<int>> rules;
    std::vector<int> rule;
    std::vector<vector<int>> updates;
    std::vector<int> update;
    int x, y;
    std::string line;
    std::string str;
    int sum = 0;

    //Read input files
    //Read rules
    while(std::getline(ruleInput, line)) {
        str = "";
        for(char c : line) {
            if(c == '|') {
                x = std::stoi(str);
                str = "";
            } else {
                str += c;
            }
        }
        y = std::stoi(str);
        if(containsKey(rules, y)) {
            rule = rules.at(y);
            rule.push_back(x);
        } else {
            rule = {x};
            rules.insert({y, rule});
        }
    }

    //Read Updates
    while(std::getline(updateInput, line)) {
        str = "";
        update = {};
        for(char c : line) {
            if(c == ',') {
                update.push_back(std::stoi(str));
                str = "";
            } else {
                str += c;
            }
        }
        update.push_back(std::stoi(str));
        updates.push_back(update);
    }

    //Check for leagal updates
    for(vector<int> v : updates) {
        if(isLegal(v, rules)) {
            sum += v.at(v.size() / 2);
        }
    }
    std::cout << sum;

    //Write to output
    for(std::pair p : rules) {
        ruleOutput << p.first << " | ";
        for(int i = 0; i < p.second.size(); i++) {
            if(i == p.second.size() - 1) {
                ruleOutput << p.second.at(i);
            } else {
                ruleOutput << p.second.at(i) << ", ";
            }
        }
        ruleOutput << "\n";
    }

    //Close open files
    ruleInput.close();
    updateInput.close();
    ruleOutput.close();
    return 0;
}