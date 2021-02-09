//#include <to-do-list.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include <array>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

auto check(const std::string& text) -> std::string
{
    std::string result;
    for (auto ch : text) {
        result.append(u8"\u0336");
        result.push_back(ch);
    }
    return result;
}

auto newtask() -> std::string
{
    auto use_this_editor = getenv("EDITOR");

    auto data_file_path = std::string{"/tmp/KRZYSZTOF_TMP_FILE"};
    auto launch_editor  = std::string{use_this_editor ? use_this_editor : "vim"}
                         + " " + data_file_path;
    system(launch_editor.c_str());

    auto fd = open(data_file_path.c_str(), O_RDWR, S_IRUSR | S_IWUSR);

    std::array<char, 4096> buf{0};
    auto const n = read(fd, buf.data(), buf.size());
    close(fd);

    unlink(data_file_path.c_str());

    if (n == -1) {
        std::cerr << "Empty task message"
                  << "\n";
        exit(1);
    }

    time_t czas;  // tworzenie zmiennej przechowującej czas
    time(&czas);  // pobranie do niej czasu
    std::cout << "New task created:\n"
              << ctime(&czas) << "\n"
              << std::string{buf.data(), static_cast<size_t>(n)};
    //        time_t czas; //tworzenie zmiennej przechowującej czas
    //        time(&czas); //pobranie do niej czasu
    //        std::cout<<"Task created: "<<ctime(&czas)<<"\n";
    //        //przetworzenie czasu funkcją ctime na ciąg znaków char

    auto task = std::string{buf.data(), static_cast<size_t>(n)};

    return task;
}

auto print(std::vector<std::string> tasks) -> void
{
    for (auto& each : tasks) {
        std::cout << each;
    }
}


auto main(int argc, char* argv[]) -> int
{
    if (argc == 1) {
        std::cerr << "No argument given on cmd"
                  << "\n";
        return 1;
    }

    auto tasks = std::vector<std::string>{};

    if (std::string(argv[1]) == "add") {
        tasks.push_back(newtask());
    }

    if (std::string(argv[1]) == "remove") {
    }

    if (std::string(argv[1]) == "list") {
        print(tasks);
    }

    if (std::string(argv[1]) == "check") {
    }

    if (std::string(argv[1]) == "uncheck") {
    }

    std::cout << check("strikethrough") << "\n";

    return 0;
}
