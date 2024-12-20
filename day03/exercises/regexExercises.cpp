#include <regex>
#include <string>
#include <iostream>

using namespace std;

int main() {
    std::string line = "abcdefghijklmnopqrstuvwxyz";
    const std::regex pattern("(abc|def)");
    std::smatch matches;
    while(std::regex_search(line, matches, pattern)) {
        cout << matches.str(1) << "\n";
        line = matches.suffix().str();
    }

    cout << ("abc" == "abc") << "\n";
    cout << ("don't()" == "don't()") << "\n";
    return 0;
}