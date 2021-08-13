#include <iostream>

int main() {
    int a = 3;
    int b = 4;
    int&& c = a + b;
    std::cout << c << std::endl;
    b = 5;
    std::cout << c << std::endl;
}