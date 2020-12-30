#include <s23210/Time.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include<unistd.h>

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
    ss << std::setfill('0') << std::setw(2) << hour << ":" << std::setfill('0') << std::setw(2) << minute << ":" << std::setfill('0') << std::setw(2) << second << "\n";
    return ss.str();
}

auto Time::time_of_day() const -> Time_of_day
{
    if (hour >= 7 && hour <= 11)
        return Time_of_day::morning;
    if (hour >= 12 && hour <= 16)
        return Time_of_day::day;
    if ((hour >= 17 && hour <= 23) || (hour == 0))
        return Time_of_day::evening;
    if(hour >= 1 && hour <= 6)
        return Time_of_day::night;
    return Time_of_day::morning;
}

auto Time::to_string(Time_of_day v) -> std::string
{
   switch(v)
    {
        case Time_of_day::morning: return "Morning";
        case Time_of_day::day: return "Day";
        case Time_of_day::evening: return "Evening";
        case Time_of_day::night: return "Night";
        default: return "Morning";
    }
}

//auto Time::operator+ (Time const&) const -> Time
//{
//
//}
//
//auto Time::operator- (Time const&) const -> Time
//{
//
//}
//
//auto Time::operator< (Time const&) const -> bool
//{
//
//}
//
//auto Time::operator> (Time const&) const -> bool
//{
//
//}
//
//auto Time::operator== (Time const&) const -> bool
//{
//
//}
//
//auto Time::operator!= (Time const&) const -> bool
//{
//
//}

//auto Time::count_seconds() const -> uint64_t
//{
//  
//}
//
//auto Time::count_minutes() const -> uint64_t
//{
//
//}

//auto Time::time_to_midnight() const -> Time
//{
//    auto t0 = Time(23-hour, 59-minute, 60-second);
//    return t0;
//}
//
//auto Time::to_string(t0) -> std::string
//{
//    std::stringstream ss;
//    ss << std::setfill('0') << std::setw(2) << hour << ":" << std::setfill('0') << std::setw(2) << minute << ":" << std::setfill('0') << std::setw(2) << second << "\n";
//    return ss.str();
//}

auto Time::next_hour() -> void
{
    if (hour < 23) {
        ++hour;
    } else {hour = 0;}
}

auto Time::next_minute() -> void
{
    if (minute < 59) {
        ++minute;
    } else {minute = 0;}
}

auto Time::next_second() -> void
{
    if (second < 59) {
        ++second;
    } else {second = 0;}
}

auto main() -> int
{
    auto t = Time(23, 59, 59);
    while (true) {
        std::cout << t.to_string();
//        std::cout << t.to_string(t.time_to_midnight());
        if (t.second == 55 || t.minute == 55 || t.hour == 23) sleep(1);
        t.next_second();
        if (t.second == 0) {
            t.next_minute();
            if (t.minute == 0) {
            t.next_hour();
            };
        };
        std::cout << t.to_string(t.time_of_day()) << " ";
}
    return 0;
}
