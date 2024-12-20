#include <map>
#include <iostream>

using namespace std;

void printMap(std::map<int, int> m) {
    for(std::pair p : m) {
        cout << p.first << " : " << p.second << "\n";
    }
}//printMap

std::map<int, int> incrementValues(std::map<int, int> m) {
    for(std::pair p : m) {
        m.at(p.first) = m.at(p.first) + 1;
    }
    return m;
}//incrementValues

int main() {
    std::map<int, int> numbers;
    numbers.insert({0, 0});
    numbers.insert({1, 1});
    numbers.insert({2, 2});
    printMap(numbers);
    cout << "\n";
    numbers = incrementValues(numbers);
    printMap(numbers);
    return 0;
}
