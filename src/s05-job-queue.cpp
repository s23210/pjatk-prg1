#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

auto print(int const id, std::queue<int>& q, std::mutex& m) -> void
{
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds{1});
        std::lock_guard<std::mutex> lg{m};

        if (q.empty()) {
            return;
        }

        auto const x = q.front();
        q.pop();

        std::cout << "from thread " << std::to_string(id) << ": "
                  << std::to_string(x) << "\n";
    }
}

auto main() -> int
{
    auto q = std::queue<int>{};
    std::mutex m;

    auto ts = std::vector<std::thread>{};

    for (auto i = 0; i < 100; ++i) {
        q.push(i);
    }
    for (auto i = 1; i < 5; ++i) {
        ts.push_back(std::thread{print, i, std::ref(q), std::ref(m)});
    }
    for (auto& each : ts) {
        each.join();
    }

    return 0;
}
