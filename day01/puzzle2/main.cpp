#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main() {
    //Declare variables
    bool isLeft;
    vector<int> left, right;
    map<int, int> occurance;
    std::string input;
    std::string num;
    int sum = 0;

    //Delcare and open i/o files
    ifstream inputFile;
    inputFile.open("input.txt");
    
    //Loop through input file; grab integers for left map and right list
    while(getline(inputFile, input)) {
        num = "";
        isLeft = true;
        for(char c : input) {
            if(c == ' ' && isLeft) {
                left.push_back(std::stoi(num));
                occurance.insert({std::stoi(num), 0});
                num = "";
                isLeft = !isLeft;
            } else {
                if(c != ' ') {
                    num += c;
                }
            }
        }
        right.push_back(std::stoi(num));
    }

    //Loop through right list, increment left value using right as key
    for(int i : right) {
        try {
            occurance.at(i)++;
        } catch (std::exception e) {
            continue;
        }
    }

    //Caclulate simularity score by adding product of left key/value pairs
    for(int i : left) {
        sum += (i * occurance.at(i));
    }

    //Print result
    cout << sum << "\n";

    //Close i/o files
    inputFile.close();
    return 0;
}//main