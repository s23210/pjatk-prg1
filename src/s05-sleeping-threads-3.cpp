#include <itp/channel.h>

#include <chrono>
#include <iostream>
#include <string>
#include <thread>


auto printer(itp::channel<std::string>& ch, int i) -> void
{
    std::cout << "Printer " << i << " is running!\n";

    std::string message = ch.wait();
    std::cout << "From printer " << i << " " << message << "\n";

    while (not message.empty()) {
        try {
            message = ch.wait_for(std::chrono::milliseconds{334});
            std::cout << "From printer " << i << " " << message << "\n";
        } catch (itp::timeout_expired_error const&) {
            // timeout expired, ignore
        }
    }

    std::cout << "Printer " << i << " is shutting down!\n";
}

auto main() -> int
{
    auto ts = std::vector<std::thread>{};
    auto ch = itp::channel<std::string>{};
    for (int i = 1; i < 5; ++i) {
        ts.push_back(std::thread{printer, std::ref(ch), i});
    }
    auto message = std::string{};
    auto empty   = 0;
    while (empty < 4) {
        std::getline(std::cin, message);
        ch.push(message);
        if (message.empty()) {
            ++empty;
        }
    }

    for (auto& each : ts) {
        each.join();
    }

    return 0;
}
