#include <condition_variable>
#include <iostream>
#include <mutex>
#include <random>
#include <string>
#include <thread>

auto print(std::string id,
           std::string idnext,
           int& i,
           std::mutex& m,
           std::condition_variable& cv,
           std::random_device& rd,
           std::uniform_int_distribution<int>& d1_42) -> void
{
    while (true) {
        std::unique_lock<std::mutex> lock{m};

        if (idnext == id) {
            cv.wait(lock);
        }
        std::cout << id << " " << i << "\n";

        i = i + d1_42(rd);

        idnext = id;

        cv.notify_all();

        if (i > 1024) {
            break;
        }
    }
}

auto main() -> int
{
    std::mutex m;
    std::condition_variable cv;

    std::random_device rd;
    std::uniform_int_distribution<int> d1_42(1, 42);

    int i = d1_42(rd);

    auto ping = std::thread{print,
                            std::string{"ping"},
                            std::string{"pong"},
                            std::ref(i),
                            std::ref(m),
                            std::ref(cv),
                            std::ref(rd),
                            std::ref(d1_42)};
    auto pong = std::thread{print,
                            std::string{"pong"},
                            std::string{"ping"},
                            std::ref(i),
                            std::ref(m),
                            std::ref(cv),
                            std::ref(rd),
                            std::ref(d1_42)};

    ping.join();
    pong.join();

    return 0;
}
