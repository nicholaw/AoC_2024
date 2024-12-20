#include <vector>
#include <iostream>

using namespace std;

void printVector(vector<int> vector) {
    cout << "{";
    for(int i = 0; i < vector.size() - 1; i++) {
        cout << vector.at(i) << ", ";
    }
    cout << vector.at(vector.size() - 1) << "}\n";
}//printVector

int main() {
    vector<int> numbers1 = {2, 4, 6, 8};
    vector<int> numbers2;
    numbers2 = numbers1;
    printVector(numbers1);
    printVector(numbers2);
    cout << "\n";
    numbers2.at(0) = 0;
    printVector(numbers1);
    printVector(numbers2);
    return 0;
}