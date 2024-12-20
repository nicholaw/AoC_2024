#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

enum dir {
    INCREASING,
    DECREASING,
    NOCHANGE,
    UNASSIGNED
};

/**
 * Returns INCREASING if b > a, DECREASING if b < a, and NOCHANGE otherwise.
 */
dir getDir(int a, int b) {
    if(b > a) {
        return INCREASING;
    } else if(b < a) {
        return DECREASING;
    } else {
        return NOCHANGE;
    }
}//getDir

/**
 * Returns true if the difference between the given integers is <= 3 and
 * false otherwise.
 */
bool checkDiff(int a, int b) {
    return (std::abs(a - b) <= 3);
}//checkDiff

/**
 * Returns true the provided directions are equal and false otherwise.
 */
bool checkDir(dir a, dir b) {
    return (a == b);
}//checkDir

/**
 * Returns true if the given line is only increaseing or decreasing
 * and the difference between any two adjacent numbers is <= 3;
 * Returns false otherwise.
 */
bool checkSafe(std::string line) {
    int last, curr = -1;
    string num = "";
    dir direction = UNASSIGNED;
    for(char c : line) {
        if(c == ' ') {
            if(curr < 0) {              //first number
                curr = std::stoi(num);
            } else {                    //subsequent number
                last = curr;
                curr = std::stoi(num); 
                if(!checkDiff(curr, last)) {             //check difference between current and last number
                    return false;
                }
                if(direction == UNASSIGNED) {           //assign initial direction if it is not already
                    if(getDir(last, curr) != NOCHANGE) {
                        direction = getDir(last, curr);
                    } else {
                        return false;
                    }
                } else {                                //check that current direction matches initial direction
                    if(!checkDir(direction, getDir(last, curr))) {
                        return false;
                    }
                }
            }
            num = "";
        } else {
            num += c;
        }
    }//for loop
    last = curr;
    curr = std::stoi(num);
    if(!checkDiff(curr, last)) {             //check difference between current and last number
        return false;
    } else if(!checkDir(direction, getDir(last, curr))) {
        return false;
    }
    return true;
}//checkSafe

int main() {
    //Declare and open input file
    ifstream inputFile;
    ofstream outputFile;
    inputFile.open("input.txt");
    outputFile.open("output.txt");

    //Declare variables
    int numSafe = 0;    //Number of safe reactor reports
    std::string line;   //Current line/report being read
    
    //Loop through input file
    while(getline(inputFile, line)) {
        if(checkSafe(line)) {
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