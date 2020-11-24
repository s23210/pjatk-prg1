#include <iostream>

auto main(int argc, char* argv[]) -> int
{
    if (argc == 1) {
        std::cerr << "no argument given on cmd"
                  << "\n";
        return 1;
    }

    auto n = std::stoi(argv[1]);

    for (auto i = 1; i <= n; ++i) {
        auto a = i % 3;
        auto b = i % 5;
        std::cout << i << " ";
        if (a == 0) {
            std::cout << "Fizz";
        }
        if (b == 0) {
            std::cout << "Buzz";
        }
        std::cout << "\n";
    }
    return 0;
}
