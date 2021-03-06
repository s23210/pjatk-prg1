#ifndef S23210_TIME_H
#define S23210_TIME_H

#include <string>

namespace s23210 {

enum class Time_of_day { morning, day, evening, night };

struct Time {
    int hour;
    int minute;
    int second;

    auto to_string() const -> std::string;

    auto time_of_day() const -> Time_of_day;

    auto to_string(Time_of_day v) -> std::string;

    auto next_hour() -> void;

    auto next_minute() -> void;

    auto next_second() -> void;

    auto operator+(Time const&) const -> Time;

    auto operator-(Time const&) const -> Time;

    auto operator<(Time const&) const -> bool;

    auto operator>(Time const&) const -> bool;

    auto operator==(Time const&) const -> bool;

    auto operator!=(Time const&) const -> bool;

    auto count_seconds() const -> uint64_t;

    auto count_minutes() const -> uint64_t;

    auto time_to_midnight(Time const&) const -> Time;

    Time(int, int, int);
};

}  // namespace s23210

#endif
