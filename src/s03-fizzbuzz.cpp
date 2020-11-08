#include <iostream>

auto main(int, char* argv[]) -> int
{
    auto n = std::stoi(argv[1]);
    for (auto i = 1; i <= n; ++i) {
        auto a = i % 3;
        auto b = i % 5;
        std::cout << i;
        if (a == 0 && b == 0) {
            std::cout << " FizzBuzz";
        } else {
            if (a == 0) {
                std::cout << " Fizz";
            }
            if (b == 0) {
                std::cout << " Buzz";
            }
        }
        std::cout << "\n";
    }
    return 0;
}
