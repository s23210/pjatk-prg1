#include <iostream>
#include <string>

auto ask_user_for_password() -> std::string
{
    std::cout << "type password:";
    auto n = std::string{};
    std::getline(std::cin, n);
    return std::string(n);
}

auto main(int, char* argv[]) -> int
{
    auto password = std::string{argv[1]};
    while (password != ask_user_for_password())
        ;
    return 0;
}
