#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <array>
#include <iostream>
#include <string>
#include <vector>

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
        std::array<char, 4096> buf{0};
        auto const n = read(client, buf.data(), buf.size());
        if (n == -1) {
            perror (" read (2)");
        } else {
            std :: cout << std :: string { buf. data (), static_cast <size_t >(n)};
            write(client, buf.data(), n);
        }
        shutdown(client, SHUT_RDWR);
        close(client);
    }
    std::cout << "server shutdown\n";
    shutdown(sock, SHUT_RDWR);
    close(sock);

    return 0;
}
