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

    std::string line;
    std::string str;
    bool skipSpace;
    double target;
    std::vector<double>* operands;
    std::vector<double>* temp;
    std::string concat;
    double product;

    //Loop through input file and determine if target calibration can be achieved with given numbers from input file.
    while(std::getline(inputFile, line)) {
        str = "";
        skipSpace = true;
        operands = new std::vector<double>();

        //Loop through current line from input file.
        for(int i = 0; i < line.size(); i++) {
            temp = new std::vector<double>();
            
            switch(line.at(i)) {
                case ' ':
                    if(!skipSpace) {
                        if(operands->size() <= 0) {
                            operands->push_back(std::stod(str));
                        } else {
                            double next = std::stod(str);
                            for(int j = 0; j < operands->size(); j++) {
                                product = 0;
                                concat = "";
                                product = operands->at(j) + next;
                                if(product <= target) {
                                    temp->push_back(product);
                                }
                                product = operands->at(j) * next;
                                if(product <= target) {
                                    temp->push_back(product);
                                }
                                product = operands->at(j);
                                concat += std::to_string(static_cast<int>(product));
                                concat += std::to_string(static_cast<int>(next));
                                product = std::stod(concat);
                                if(product <= target) {
                                    temp->push_back(product);
                                }
                            }
                            operands = temp;
                        }
                        str = "";
                    } else {
                        skipSpace = false;
                    }
                    break;
                case ':':
                    target = std::stod(str);
                    str = "";
                    break;
                default:
                    str += line.at(i);
            }//switch
        }//for
        double next = std::stod(str);
        temp = new std::vector<double>();
        for(int j = 0; j < operands->size(); j++) {
            product = 0;
            concat = "";
            product = operands->at(j) + next;
            if(product <= target) {
                temp->push_back(product);
            }
            product = operands->at(j) * next;
            if(product <= target) {
                temp->push_back(product);
            }
            product = operands->at(j);
            concat += std::to_string(static_cast<int>(product));
            concat += std::to_string(static_cast<int>(next));
            product = std::stod(concat);
            if(product <= target) {
                temp->push_back(product);
            }
        }
        operands = temp;

        //If operands contains target, add target to calibrationTotal
        for(int i = 0; i < operands->size(); i++) {
            if(target == operands->at(i)) {
                calibrationTotal += target;
                break;
            }
        }
    }//while
}//readInput

int main() {
    readInput("input.txt");
    std::string output = std::to_string(calibrationTotal);
    std::cout << output;
    return 0;
}//main