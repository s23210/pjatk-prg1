//#include <to-do-list.h>
#include <array>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <unistd.h>

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
//    auto use_this_editor = getenv("EDITOR");
//
//    auto data_file_path = std::string{"/tmp/KRZYSZTOF_TMP_FILE"};
//    auto launch_editor = std::string{use_this_editor} + " " + data_file_path;
//    system(launch_editor.c_str());
//
//    unlink(data_file_path.c_str());

//std::string filename = "/tmp/KRZYSZTOF_TMP_FILE";
//std::string cmd = "/usr/bin/vim " + filename;
//system(cmd.c_str());
//// read from filename

    auto filename = std::string{"/tmp/KRZYSZTOF_TMP_FILE"};
    auto cmd = "/usr/bin/vim " + filename;
    system(cmd.c_str());

    auto fd = open(filename.c_str(), O_RDWR, S_IRUSR | S_IWUSR);

    std::array<char, 4096> buf{0};
    auto const n = read(fd, buf.data(), buf.size());
    if (n == -1) {
//        perror("Something went wrong");
        std::cerr << "Empty task message"
                  << "\n";
    } else {
        time_t czas; //tworzenie zmiennej przechowującej czas
        time(&czas); //pobranie do niej czasu
        std::cout << "New task created:\n" << ctime(&czas) << "\n" << std::string{buf.data(), static_cast<size_t>(n)};
//        time_t czas; //tworzenie zmiennej przechowującej czas
//        time(&czas); //pobranie do niej czasu
//        std::cout<<"Task created: "<<ctime(&czas)<<"\n"; //przetworzenie czasu funkcją ctime na ciąg znaków char
    }

    auto task = std::string{buf.data(), static_cast<size_t>(n)};

    close(fd);

    unlink(filename.c_str());

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

    if (std::string(argv[1]) == "commit") {
        tasks.push_back(newtask());
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
