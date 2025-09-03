#include <iostream>

int main() {
    int num = 5;
    int* ptr = nullptr;
    ptr = &num;
    std::cout << "num: " << num << "\n";
    std::cout << "ptr: " << ptr << "\n";
    std::cout << "*ptr: " << *ptr << "\n";
    return 0;
}