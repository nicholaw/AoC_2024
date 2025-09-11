#include <iostream>
#include <vector>

using namespace std;

void printArray(vector<int> arr) {
    int index = 0;
    cout << "{";
    while(index < arr.size() - 1) {
        cout << arr.at(index) << ", ";
        index++;
    }
    cout << arr.at(index) << "}\n";
}//printArray

void print2DArray(vector<vector<int>> arr) {
    for(int i = 0; i < arr.size(); i++) {
        cout << i << ": ";
        printArray(arr.at(i));
    }
}//print2DArray

vector<int> generateArray(int start, int end) {
    vector<int> arr = vector<int>();
    for(int i = start; i <= end; i++) {
        arr.push_back(i);
    }
    return arr;
}//generateArray

int main() {
    vector<vector<int>>* arr = new vector<vector<int>>();
    arr->push_back(generateArray(1, 3));
    arr->push_back(generateArray(4, 6));
    arr->push_back(generateArray(7, 9));
    print2DArray(*arr);
    return 0;
}