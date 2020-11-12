#include <iostream>
#include <string>

auto main(int argc, char* argv[]) -> int
{
    if (argc == 2) {
        while (true) {
            for (int i = std::stoi(argv[1]); i > 0; --i) {
                std::cout << i << " bottles of beer on the wall, " << i
                          << " bottles of beer."
                          << "\n"
                          << "Take one down, pass it around, ";
                if (i == 1) {
                    std::cout << "No more bottles of beer on the wall, no more "
                                 "bottles of beer."
                              << "\n"
                              << "Go to the store and buy some more, ";
                }
            }
        }
    } else {
        while (true) {
            for (int i = 99; i > 0; --i) {
                std::cout << i << " bottles of beer on the wall, " << i
                          << " bottles of beer. "
                          << "\n"
                          << "Take one down, pass it around, ";
                if (i == 1) {
                    std::cout << "No more bottles of beer on the wall, no more "
                                 "bottles of beer."
                              << "\n"
                              << "Go to the store and buy some more, ";
                }
            }
        }
    }
    return 0;
}
