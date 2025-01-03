#include "lab.cpp"

int main() {
    Lab* lab = new Lab("input.txt");
    lab->writeLabMap("output.txt");
    return 0;
}