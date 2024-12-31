#pragma once

#include <exception>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <set>
#include <vector>

using namespace std;

bool containsKey(std::map<int, std::set<int>> searchMap, int targetKey);
bool containsValue(std::map<int, std::set<int>> searchMap, int searchKey, int targetValue);
void writeRuleset(std::map<int, std::set<int>> ruleset, std::string destination);
void writeUpdates(std::vector<std::vector<int>> updates, std::string destination);
std::map<int, std::set<int>> readRuleset(std::string input);
std::vector<std::vector<int>> readUpdates(std::string input);