#include <fcntl.h>
#include <s23210/Student.h>
#include <sys/stat.h>
#include <unistd.h>

#include <iostream>
#include <sstream>
#include <string>
using namespace s23210;

Student::Student(std::string name,
                 std::string surname,
                 int index,
                 int semester,
                 float average)
        : name{name}
        , surname{surname}
        , index{index}
        , semester{semester}
        , average{average}
{}

auto Student::to_string() const -> std::string
{
    std::stringstream ss;
    ss << name << "\n"
       << surname << "\n"
       << index << "\n"
       << semester << "\n"
       << average << "\n";
    return ss.str();
}

auto main() -> int
{
    Student me = Student("Krzysztof", "Szymczyk", 23210, 1, 3.88);

    auto fdname = std ::string{"student.txt"};
    auto fd     = open(fdname.c_str(), O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

    auto buf = me.to_string();

    auto n = write(fd, buf.data(), buf.size());
    if (n == -1) {
        perror("Something went wrong");
    }
    close(fd);

    return 0;
}
