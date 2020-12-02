#include <s23210/Student.h>

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
    ss << "Name: " << name << "\n"
       << "Surname: " << surname << "\n"
       << "Index: " << index << "\n"
       << "Semester: " << semester << "\n"
       << "Average: " << average << "\n";
    return ss.str();
}

auto main() -> int
{
    Student me = Student("Krzysztof", "Szymczyk", 23210, 1, 3.88);

    std::cout << me.to_string();
    return 0;
}
