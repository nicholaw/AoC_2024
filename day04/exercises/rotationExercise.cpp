#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

enum orientation {
    HORIZONTAL,
    VERTICAL,
    DIAGONAL_DOWN,
    DIAGONAL_UP
};

void printTable(vector<vector<char>> table, orientation o) {
    switch(o) {
        case VERTICAL:
            for(int i = table.at(0).size() - 1; i >=0; i--) {
                for(int j = 0; j < table.size(); j++) {
                    cout << table.at(j).at(i);
                }
                cout << "\n";
            }
            break;
        case DIAGONAL_DOWN:
            for(int i = 0; i < table.at(0).size() - 1; i++) {   //front half
                for(int j = 0; j < i + 1; j++) {
                    cout << table.at(j).at(j + table.at(0).size() - 1 - i);
                }
                cout << "\n";
            }
            for(int i = table.at(0).size() - 1; i > 0; i--) {   //back half
                for(int j = 0; j < i; j++) {
                    cout << table.at(table.at(0).size() - 1 - i + j).at(j);
                }
                cout << "\n";
            }
            break;
        case DIAGONAL_UP:
            for(int i = 0; i < (table.at(0).size() - 1); i++) { //front half
                for(int j = 0; j < i + 1; j++) {
                    cout << table.at(i - j).at(j);
                }
                cout << "\n";
            }
            for(int i = (table.at(0).size() - 1); i > 0; i--) { //back half

            }
            break;
        default:
            for(vector<char> v : table) {
                for(char c : v) {
                    cout << c;
                }
                cout << "\n";
            }
    }//switch
}//printTable

int main() {
    std::vector<vector<char>> table;
    std::vector<char> row0 = {'A', 'A', 'A', 'A', 'A', 'A', 'A'};
    std::vector<char> row1 = {'B', 'B', 'B', 'B', 'B', 'B', 'B'};
    std::vector<char> row2 = {'C', 'C', 'C', 'C', 'C', 'C', 'C'};
    std::vector<char> row3 = {'D', 'D', 'D', 'D', 'D', 'D', 'D'};
    std::vector<char> row4 = {'E', 'E', 'E', 'E', 'E', 'E', 'E'};
    std::vector<char> row5 = {'F', 'F', 'F', 'F', 'F', 'F', 'F'};
    table.push_back(row0);
    table.push_back(row1);
    table.push_back(row2);
    table.push_back(row3);
    table.push_back(row4);
    table.push_back(row5);
    printTable(table, HORIZONTAL);
    cout << "\n";
    printTable(table, VERTICAL);
    cout << "\n";
    printTable(table, DIAGONAL_DOWN);
    cout<< "\n";
    printTable(table, DIAGONAL_UP);
    return 0;
}