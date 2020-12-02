#ifndef S23210_STUDENT_H
#define S23210_STUDENT_H

#include <string>

namespace s23210 {

struct Student {
    std::string name;
    std::string surname;
    int index;
    int semester;
    float average;

    auto to_string() const -> std::string;

    Student(std::string, std::string, int, int, float);
};

}  // namespace s23210

#endif
