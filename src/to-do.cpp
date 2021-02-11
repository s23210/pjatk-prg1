#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include <algorithm>
#include <array>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

auto join(std::vector<std::string> str, char delimeter) -> std::string
{
    std::string temp;
    for (unsigned i = 0; i < str.size(); i++) {
        temp.append(str.at(i) + delimeter);
    }
    return temp;
}

auto split(std::string str, char delimeter) -> std::vector<std::string>
{
    std::string buf;
    std::stringstream ss(str);
    std::vector<std::string> tokens;

    while (getline(ss, buf, delimeter))
        tokens.push_back(buf);

    return tokens;
}

auto list(int n) -> void
{
    auto i = int{0};
    std::ifstream inFile;
    inFile.open("tasks.txt");
    if (inFile.is_open()) {
        auto temp = std::string{};
        while (std::getline(inFile, temp)) {
            if (n != ++i)
                continue;
            auto record = split(temp, ';');
            std::cout << "================================================\n"
                      << "ID: " << record.at(0) << "\nDATE: " << record.at(2)
                      << "\nDONE: " << (record.at(3) == "0" ? "[ ]" : "[*]")
                      << "\n------------------------------------------------\n"
                      << join(split(record.at(1), '`'), '\n')
                      << "\n================================================\n";
        }
    }
}

auto openEditor() -> std::string
{
    auto use_this_editor = getenv("EDITOR");
    auto data_file_path  = std::string{"/tmp/KRZYSZTOF_TMP_FILE"};
    auto launch_editor = std::string{use_this_editor ? use_this_editor : "vim"}
                         + " " + data_file_path;
    system(launch_editor.c_str());

    auto fdtmp = open(data_file_path.c_str(), O_RDWR, S_IRUSR | S_IWUSR);
    std::array<char, 4096> buf{0};
    auto const n = read(fdtmp, buf.data(), buf.size());
    close(fdtmp);

    if (n == -1) {
        std::cerr << "Empty task message"
                  << "\n";
        exit(1);
    }

    unlink(data_file_path.c_str());
    auto string = std::string{};
    for (auto i = 0; i < n; ++i) {
        string = string + buf[i];
    }
    return string;
}

auto countLine(const char* sourcefile) -> int
{
    std::ifstream infile;
    infile.open(sourcefile, std::ios::in);

    char data[100];
    int line = 0;

    while (infile.getline(data, 100))
        line++;

    return line;
}

auto removeLine(const char* sourcefile, int line) -> void
{
    std::ifstream infile;
    char tempPath[100] = "/tmp/REMOVE_LINE_TMP_FILE";
    infile.open(sourcefile, std::ios::in);

    if (infile) {
        int numLine = countLine(sourcefile);
        if (numLine < line) {
            std::cout << "\nNo task to delete.\n";
            return;
        }

        std::ofstream outfile;
        outfile.open(tempPath, std::ios::out);

        char data[100];
        int i  = 0;
        int id = 0;

        while (infile.getline(data, 100)) {
            i++;
            if (i == line)
                continue;
            ++id;
            auto temp  = split(data, ';');
            temp.at(0) = std::to_string(id);
            strcpy(data, join(temp, ';').c_str());
            outfile << data << "\n";
        }
        outfile.close();
    }

    infile.close();
    remove(sourcefile);
    rename(tempPath, sourcefile);
}

auto find_last_line(std::ifstream& myFile) -> std::string
{
    std::string lastline;
    std::string output;
    if (myFile.is_open()) {
        while (!myFile.eof()) {
            getline(myFile, lastline);
            if (lastline != std::string{}) {
                output = lastline;
            }
        }
        myFile.close();
    }
    return output.substr(0, output.find(";"));
}

auto check(const std::string& text) -> std::string
{
    std::string result;
    for (auto ch : text) {
        result.append(u8"\u0336");
        result.push_back(ch);
    }
    return result;
}

auto newtask() -> void
{
    auto string = openEditor();

    time_t date;
    time(&date);
    tm* date_pointer = localtime(&date);
    char date_string[100];
    strftime(date_string, 50, "%B %d %Y %T", date_pointer);

    auto isClosed = false;
    auto id       = 1;

    auto filename = std::string("tasks.txt");
    auto createfile =
        open(filename.c_str(), O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    close(createfile);

    for (long unsigned int i = 0; i < string.length(); i++) {
        if (string[i] == '\n') {
            string[i] = '`';
        }
    }

    std::ifstream inFile;
    inFile.open("tasks.txt");

    auto number = find_last_line(inFile);
    number      = number == std::string{} ? std::string{"0"} : number;
    id          = std::stoi(number) + 1;

    std::ofstream file;
    file.open(filename, std::ofstream::out | std::ofstream::app);
    file << id << ";" << string << ";" << date_string << ";" << isClosed
         << "\n";
    file.close();

    std::cout << "New task created:\n";
    list(id);
    //        time_t czas; //tworzenie zmiennej przechowującej czas
    //        time(&czas); //pobranie do niej czasu
    //        std::cout<<"Task created: "<<ctime(&czas)<<"\n";
    //        //przetworzenie czasu funkcją ctime na ciąg znaków char
}

// auto edittask(int n}) -> void
//{
//
//}

auto check(bool check, int line) -> void
{
    auto sourcefile           = std::string{"tasks.txt"};
    const char* sourcefileptr = sourcefile.c_str();
    std::ifstream infile;
    char tempPath[100] = "/tmp/REMOVE_LINE_TMP_FILE";
    infile.open(sourcefile, std::ios::in);

    if (infile) {
        int numLine = countLine(sourcefileptr);
        if (numLine < line) {
            std::cout << "\nNo task to change status\n.";
            return;
        }

        std::ofstream outfile;
        outfile.open(tempPath, std::ios::out);

        char data[100];
        int i = 0;

        while (infile.getline(data, 100)) {
            i++;
            if (i == line) {
                auto temp  = split(data, ';');
                temp.at(3) = check ? "1" : "0";
                strcpy(data, join(temp, ';').c_str());
            }
            outfile << data << "\n";
        }
        outfile.close();
    }

    infile.close();
    remove(sourcefileptr);
    rename(tempPath, sourcefileptr);
}

auto main(int argc, char* argv[]) -> int
{
    if (argc == 1) {
        std::cerr << "No argument given on cmd"
                  << "\n";
        return 1;
    }

    if (std::string(argv[1]) == "add") {
        newtask();
    }

    if (std::string(argv[1]) == "remove") {
        if (argc == 2) {
            std::cerr << "No task given to remove"
                      << "\n";
            return 1;
        }
        auto filename           = std::string{"tasks.txt"};
        const char* filenameptr = filename.c_str();
        removeLine(filenameptr, std::stoi(argv[2]));
    }

    if (std::string(argv[1]) == "list") {
        list(std::stoi(argv[2]));
    }

    if (std::string(argv[1]) == "check") {
        if (argc == 2) {
            std::cerr << "No task given to check"
                      << "\n";
            return 1;
        }
        check(true, std::stoi(argv[2]));
    }

    if (std::string(argv[1]) == "uncheck") {
        if (argc == 2) {
            std::cerr << "No task given to ucheck"
                      << "\n";
            return 1;
        }
        check(false, std::stoi(argv[2]));
    }

    return 0;
}
