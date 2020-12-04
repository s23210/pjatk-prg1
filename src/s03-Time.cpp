#include <s23210/Time.h>

#include <iostream>
#include <sstream>
#include <string>
using namespace s23210;

Time::Time(unsigned hour, unsigned minute, unsigned second)
        : hour{hour}, minute{minute}, second{second}
{
    if (hour > 23) {
        throw std::out_of_range{"hour value cannot exceed 23"};
    }

    if (minute > 59) {
        throw std::out_of_range{"minute value cannot exceed 59"};
    }

    if (second > 59) {
        throw std::out_of_range{"second value cannot exceed 59"};
    }
}

auto Time::to_string() const -> std::string
{
    std::stringstream ss;
    ss << hour << ":" << minute << ":" << second << "\n";
    return ss.str();
}

auto Time::next_hour() -> void
{
    if (hour < 23) {
        ++hour;
    } else hour = 0;
}

auto Time::next_minute() -> void
{
    if (minute < 59) {
        ++minute;
    } else minute = 0;
}

auto Time::next_second() -> void
{
    if (second < 59) {
        ++hour;
    } else second = 0;
}

