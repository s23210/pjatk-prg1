#include <iostream>
#include <string>

auto main(int, char* argv[]) -> int
{
    for (auto i = std::stoi(argv[1]); i >= 0; --i) {
        std::cout << i << "\n";
    }
    return 0;
}
