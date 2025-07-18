#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

double calibrationTotal = 0;

void readInput(std::string input) {
    std::ifstream inputFile;
    try {
        inputFile.open(input);
    } catch(std::exception e) {
        std::cout << "Cannot find file \'" << input << "\'\n";
    }

    //Loop through input file and determine if target calibration can be achieved with given numbers from input file.
    while(std::getline(inputFile, line)) {
    }//while
}//readInput

int main() {
    return 0;
}//main