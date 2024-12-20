#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

int main() {
    //Declare and open i/o files
    ifstream inputFile;
    ofstream outputFile;
    inputFile.open("input.txt");
    outputFile.open("output.txt");

    //Declare variables
    std::string line;
    const std::regex commandPattern("(mul\\([0-9]{1,3},[0-9]{1,3}\\)|do\\(\\)|don't\\(\\))");
    const std::regex factorPattern("([0-9]{1,3})");
    std::smatch commands;
    std::smatch factors;
    int fact1, fact2;
    int sum = 0;
    bool doNext = true;

    //Read input
    while(getline(inputFile, line)) {
        while(std::regex_search(line, commands, commandPattern)) {
            string match = commands.str(1);
            outputFile << match << "\n";
            if(match == "do()") {
                doNext = true;
            } else if(match == "don't()") {
                doNext = false;
            } else if(doNext) {
                //Get the first factor
                std::regex_search(match, factors, factorPattern);
                fact1 = std::stoi(factors.str(1));
                match = factors.suffix().str();

                //Get the second factor
                std::regex_search(match, factors, factorPattern);
                fact2 = std::stoi(factors.str(1));

                //Print to output file and add product of factors to sum
                sum += (fact1 * fact2);
            }
            line = commands.suffix().str();
        }//Regex matching
    }//Read File
    cout << sum;

    //Close i/o files
    inputFile.close();
    outputFile.close();
    return 0;
}