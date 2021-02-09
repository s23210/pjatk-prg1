#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <array>
#include <iostream>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

auto main() -> int
{
    auto const sock = socket(AF_INET, SOCK_STREAM, 0);

    auto const ip   = std::string{"127.0.0.1"};
    auto const port = uint16_t{8080};

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port   = htobe16(port);
    inet_pton(addr.sin_family, ip.c_str(), &addr.sin_addr);

    bind(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
    listen(sock, SOMAXCONN);
    std::cout << "listening on " << ip << ": " << port << "\n...\n";

    while (true) {
        auto client = accept(sock, nullptr, nullptr);    
        std::cout << "client fd " << client << "\n";
        std::array<char, 4096> filename{0};
        auto const n = read(client, filename.data(), filename.size());
        if (n == -1) {
            perror (" read (2)");
        } else {
            std :: cout << std :: string { filename. data (), static_cast <size_t >(n)};
        auto name = std::string{filename.data(), static_cast<size_t>(n-1)};
            auto fd = open(name.c_str(), O_RDONLY, S_IRUSR);
            std::array<char, 4096> buf{0};
            auto const data_size = read(fd, buf.data(), buf.size());
            write(client, filename.data(), n);
            write(client, "\n", 1);
            write(client, buf.data(), data_size);
            close(fd);
        }
        shutdown(client, SHUT_RDWR);
        close(client);
    }
    std::cout << "server shutdown\n";
    shutdown(sock, SHUT_RDWR);
    close(sock);

    return 0;
}
