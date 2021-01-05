#include <iostream>
#include <string>

auto main(int argc, char* argv[]) -> int
{
    if (argc == 1) {
        std::cerr << "no argument given on cmd"
                  << "\n";
        return 1;
    }

    auto i = std::stoi(argv[1]);

    for (i = std::stoi(argv[1]); i != 0; (i > 0) ? --i : ++i) {
        std::cout << i << "\n";
    }

    std::cout << "0\n";

    return 0;
}
