#ifndef S23210_TIME_H
#define S23210_TIME_H

#include <string>

namespace s23210 {

struct Time {
    unsigned hour;
    unsigned minute;
    unsigned second;

    auto to_string() const -> std::string;

    auto next_hour() -> void;

    auto next_minute() -> void;

    auto next_second() -> void;

    Time(unsigned, unsigned, unsigned);
};

}  // namespace s23210

#endif
