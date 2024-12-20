#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    //Declare variables
    bool isLeft;
    vector<int> left, right;
    std::string input;
    std::string num;
    int sum = 0;

    //Delcare and open i/o files
    ifstream inputFile;
    inputFile.open("input.txt");
    
    //Loop through input file; grab integers for right and left lists
    while(getline(inputFile, input)) {
        num = "";
        isLeft = true;
        for(char c : input) {
            if(c == ' ' && isLeft) {
                left.push_back(std::stoi(num));
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

    //Sort the left and right lists in ascending order
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    //Sum differences of right and left lists
    for(int i = 0; i < left.size(); i++) {
        sum += abs(left[i] - right[i]);
    }

    //Print result
    cout << sum << "\n";

    //Close i/o files
    inputFile.close();
    return 0;
}//main