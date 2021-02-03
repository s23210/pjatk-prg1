#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include <array>
#include <iostream>
#include <string>
#include <vector>

auto main(int argc, char* argv[]) -> int
{
    if (argc == 1) {
        std::cerr << "no file name given on cmd"
                  << "\n";
        return 1;
    }

    auto const fdname = std::string{argv[1]};

    auto fd = open(fdname.c_str(), O_RDONLY, S_IRUSR);

    std::array<char, 4096> buf{0};
    auto const n = read(fd, buf.data(), buf.size());
    if (n == -1) {
        perror("Something went wrong");
    } else {
        std::cout << std::string{buf.data(), static_cast<size_t>(n)};
    }

    close(fd);

    return 0;
}
