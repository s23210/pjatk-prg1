#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

auto print_stuff(std::string x) -> void
{
    std::this_thread::sleep_for(std::chrono::milliseconds{1});
    std::cout << (x + "\n");
}

auto main() -> int
{
    for (auto i = 1; i <= 7; ++i) {
        auto ts = std::vector<std::thread>{};
        std::cout << "Group " << i << "\n";
        for (auto x = 0; x < 6; ++x) {
            auto s = std::string{"Hello, "} + std::to_string(x) + "!";
            auto t = std::thread{print_stuff, std::move(s)};
            ts.push_back(std::move(t));
        }
        for (auto& each : ts) {
            each.join();
        }
    }
    return 0;
}
