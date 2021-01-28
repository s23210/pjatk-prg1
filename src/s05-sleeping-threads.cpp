#include <chrono>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

auto print(int const id, std::queue<std::string>& q, std::mutex& m) -> void
{
    while (true) {
        std::lock_guard<std::mutex> lg{m};

        if (q.empty()) {
            m.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds{100});
            continue;
        }

        auto const x = q.front();
        q.pop();

        if (x.empty()) {
            std::cout << "thread " << id << " exiting"
                      << "\n";
            return;
        }

        std::cout << "from thread " << id << ": " << x << "\n";
    }
}

auto main() -> int
{
    auto q = std::queue<std::string>{};
    std::mutex m;

    auto ts = std::vector<std::thread>{};

    auto empty = 0;

    for (auto i = 1; i < 5; ++i) {
        ts.push_back(std::thread{print, i, std::ref(q), std::ref(m)});
    }
    while (empty < 4) {
        auto s = std::string{};
        std::getline(std::cin, s);
        if (s.empty()) {
            ++empty;
        }
        std::lock_guard<std::mutex> lg{m};
        q.push(s);
    }

    for (auto& each : ts) {
        each.join();
    }

    return 0;
}
