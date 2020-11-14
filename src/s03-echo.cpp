#include <iostream>
#include <string>

auto main(int argc, char* argv[]) -> int
{
    // nie drukuje nowej linii na końcu programu
    if (std::string(argv[1]) == "-n") {
        for (int i = 2; i <= argc; ++i) {
            std::cout << argv[i] << " ";
        }
    }
    // drukuje argumenty w odwrotnej kolejności
    if (std::string(argv[1]) == "-r") {
        if (std::string(argv[2]) != "-n" && std::string(argv[2]) != "-l") {
            for (int i = argc - 1; i >= 2; --i) {
                std::cout << argv[i] << " ";
            }
            std::cout << "\n";
        }
        if (std::string(argv[2]) == "-n") {
            for (int i = argc - 1; i >= 3; --i) {
                std::cout << argv[i] << " ";
            }
        }
        if (std::string(argv[2]) == "-l") {
            for (int i = argc - 1; i >= 3; --i) {
                std::cout << argv[i] << "\n";
            }
        }
    }
    // drukuje argumenty po jednym na linię
    if (std::string(argv[1]) == "-l") {
        for (int i = 2; i <= argc; ++i) {
            std::cout << argv[i] << "\n";
        }
    }
    // basic print
    if (std::string(argv[1]) != "-n" && std::string(argv[1]) != "-r"
        && std::string(argv[1]) != "-l") {
        for (int i = 1; i < argc; ++i) {
            std::cout << argv[i] << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
