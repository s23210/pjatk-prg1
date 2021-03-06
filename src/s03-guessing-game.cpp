#include <iostream>
#include <random>
#include <string>

auto ask_user_for_integer() -> int
{
    std::cout << "make a guess:";
    auto in = std::string{};
    std::getline(std::cin, in);
    return std::stoi(in);
}

auto main() -> int
{
    std::random_device rd;
    std::uniform_int_distribution<int> d100(1, 100);

    int n   = d100(rd);
    auto in = ask_user_for_integer();

    while (in != n) {
        if (in > n) {
            std::cout << "number is too big!"
                      << "\n";
        }
        if (in < n) {
            std::cout << "number is too low!"
                      << "\n";
        }
        in = ask_user_for_integer();
    }
    std::cout << "you're correct"
              << "\n";
    return 0;
}
