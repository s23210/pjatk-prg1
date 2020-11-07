#include <iostream>
#include <random>
#include <string>

auto main() -> int
{
    std::random_device rd;
    std::uniform_int_distribution<int> d100(1, 100);

    auto n  = d100(rd);
    auto in = std::string{};
    std::cout << "make a guess:";
    std::getline(std::cin, in);
    while (std::stoi(in) != n) {
        if (std::stoi(in) > n) {
            std::cout << "number is too big!"
                      << "\n";
            std::cout << "make a guess:";
            std::getline(std::cin, in);
        }
        if (std::stoi(in) < n) {
            std::cout << "number is too low!"
                      << "\n";
            std::cout << "make a guess:";
            std::getline(std::cin, in);
        }
        if (std::stoi(in) == n) {
            std::cout << "you're correct"
                      << "\n";
        }
    }
    return 0;
}
