#include <iostream>
#include <string>

auto main() -> int
{
    auto password_in = std::string{};
    std::cout << "set password:";
    auto password = std::string{};
    std::getline(std::cin, password);
    std::cout << "type password:";
    std::getline(std::cin, password_in);
    while (password != password_in) {
        std::cout << "wrong password"
                  << "\n";
        std::cout << "type password:";
        std::getline(std::cin, password_in);
    }
    std::cout << "You're logged in"
              << "\n";
    return 0;
}
