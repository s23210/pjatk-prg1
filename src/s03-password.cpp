#include <iostream>
#include <string>

auto main(int, char* argv[]) -> int
{
    auto password = std::string{argv[1]};
    auto password_in = std::string{};
    std::cout << "type password:";
    std::getline(std::cin, password_in);
    while (password != password_in) {
        std::cout << "type password:";
        std::getline(std::cin, password_in);
    }
    return 0;
}
