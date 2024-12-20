#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Returns a vector<int> containing each level of the provided report.
 */
vector<int> parseLine(std::string line) {
    //Generate the base report
    string num = "";
    vector<int> baseReport;
    for(char c : line) {
        if(c == ' ') {
            baseReport.push_back(std::stoi(num));   //THIS IS FINE
            num = "";
        } else {
            num += c;
        }
    }
    baseReport.push_back(std::stoi(num));           //THIS IS FINE
    return baseReport;
}//parseLine

/**
 * Returns a map containing each legal permutation of the provided report as key and booleans
 * representing if the permutaion is SAFE or UNSAFE as values.
 */
vector<vector<int>> permuteReport(vector<int> report) {
    vector<vector<int>> permutations;
    for(int i = 0; i < report.size(); i++) {
        vector<int> permutation;
        for(int j = 0; j < report.size(); j++) {
            if(j != i) {
                permutation.push_back(report.at(j));
            }
        }
        permutations.push_back(permutation);
    }
    return permutations;
}//permuteReport

/**
 * Retruns true if elements of the provided vector are all positive or all negative;
 * returns false if vectors contains positive and negative elements or if any element
 * equals zero.
 */
bool constDir(vector<int> metaReport) {
    int pos, neg;
    pos = neg = 0;
    for(int i : metaReport) {                       //THIS IS FINE
        if(i == 0) {
            return false;
        } else if (i > 0) {
            pos++;
        } else {
            neg++;
        }
    }
    return !(pos > 0 && neg > 0);
}//constDir

/**
 * Returns true if the provided permutation has constant direction and
 * no difference is larger than three and false otherwise.
 */
bool isSafe(vector<int> permutation) {
    int curr, last, diff;
    curr = last = diff = -1;
    vector<int> metaReport;
    for(int i : permutation) {                      //THIS IS FINE
        if(curr < 0) {
            curr = i;
        } else {
            last = curr;
            curr = i;
            diff = (curr - last);
            metaReport.push_back(diff);             //THIS IS FINE
            if(std::abs(diff) > 3) {    //check diff
                return false;
            }
        }
    }//for loop
    return constDir(metaReport);        //check dir
}//isSafe

/**
 * Determines if each permuation in the provided map is SAFE or UNSAFE;
 * returns true if any permuation is SAFE and false otherwise.
 */
bool parsePermutations(vector<vector<int>> permutations) {
    for(vector<int> v : permutations) {             //THIS IS FINE
        if(isSafe(v)) {
            return true;
        }
    }
    return false;
}//parsePermutations

/**
 * Returns true if the given line is only increaseing or decreasing
 * and the difference between any two adjacent numbers is <= 3;
 * Returns false otherwise.
 */
bool parseReport(std::string line) {
    vector<int> baseReport = parseLine(line);
    vector<vector<int>> permutations = permuteReport(baseReport);
    return parsePermutations(permutations);
}//checkSafe

int main() {
    //Declare and open i/o files
    ifstream inputFile;
    ofstream outputFile;
    inputFile.open("input.txt");
    outputFile.open("output.txt");

    //Declare variables
    int numSafe = 0;    //Number of safe reactor reports
    std::string line;   //Current line/report being read
    
    //Loop through input file
    while(getline(inputFile, line)) {
        if(parseReport(line)) {
            outputFile << "safe\n";
            numSafe++;
        } else {
            outputFile << "unsafe\n";
        }   
    }

    //Print results
    cout << numSafe << "\n";

    //Close open files
    inputFile.close();
    outputFile.close();
    return 0;
}