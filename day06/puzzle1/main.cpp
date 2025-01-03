#include "lab.cpp"

int main() {
    Lab* lab = new Lab("input.txt");
    std::cout << lab->run();
    return 0;
}