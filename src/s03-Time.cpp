#include <s23210/Time.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace s23210;

Time::Time(int hour, int minute, int second)
        : hour{hour}, minute{minute}, second{second}
{
    if (hour > 23) {
        throw std::out_of_range{"hour value cannot exceed 23"};
    }
    
    if (hour < 0) {
        throw std::out_of_range{"hour value cannot be a negative number"};
    }

    if (minute > 59) {
        throw std::out_of_range{"minute value cannot exceed 59"};
    }
    
    if (minute < 0) {
        throw std::out_of_range{"minute value cannot be a negative number"};
    }

    if (second > 59) {
        throw std::out_of_range{"second value cannot exceed 59"};
    }

    if (second < 0) {
        throw std::out_of_range{"second value cannot be a negative number"};
    }
}

auto Time::to_string() const -> std::string
{
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << hour << ":" << std::setfill('0') << std::setw(2) << minute << ":" << std::setfill('0') << std::setw(2) << second;
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

auto Time::operator+ (Time const& time_o) const -> Time
{
    int h = 0;
    int m = 0;
    int s = 0;

    if (second + time_o.second > 59) {
        s = second + time_o.second - 60;
        m++;
    } else s = second + time_o.second;
    if (minute + time_o.minute > 59) {
        m = m + minute + time_o.minute - 60;
        h++;
    } else {m = minute + time_o.minute;}
    h = (h + hour + time_o.hour) % 24;
    
    auto n_time = Time (h, m, s);
    
    return n_time;
}

auto Time::operator- (Time const& time_o) const -> Time
{
    int h = 0;
    int m = 0;
    int s = 0;

    if (second - time_o.second < 0) {
        s = 60 + second - time_o.second;
        m--; 
    } else s = second - time_o.second;
    if (minute - time_o.minute < 0) { 
        m = 60 + m + minute - time_o.minute;
        h--;
    } else m = minute - time_o.minute;
    if (hour - time_o.hour < 0) { 
        h = h + (hour - time_o.hour + 24) % 24;
    } else h = hour + time_o.hour;

    auto n_time = Time (h, m, s);

    return n_time;
}

auto Time::operator< (Time const& time_o) const -> bool
{
    if (hour < time_o.hour) return true;
    else if (hour == time_o.hour && minute < time_o.minute) return true;
        else if (hour == time_o.hour && minute == time_o.minute && second < time_o.second) return true;
            else return false;
}

auto Time::operator> (Time const& time_o) const -> bool
{
    if (hour > time_o.hour) return true;
    else if (hour == time_o.hour && minute > time_o.minute) return true;
        else if (hour == time_o.hour && minute == time_o.minute && second > time_o.second) return true;
            else return false;
}

auto Time::operator== (Time const& time_o) const -> bool
{
    if (hour == time_o.hour && minute == time_o.minute && second == time_o.second) return true;
    else return false;
}

auto Time::operator!= (Time const& time_o) const -> bool
{
    if ((hour != time_o.hour) | (minute != time_o.minute) | (second != time_o.second)) return true;
    else return false;
}

auto Time::count_seconds() const -> uint64_t
{
    auto sec_counter = hour * 3600 + minute * 60 + second;
    return sec_counter;
}

auto Time::count_minutes() const -> uint64_t
{
    auto min_counter = hour * 60 + minute;
    return min_counter;
}

auto Time::time_to_midnight(Time const& time_o) const -> Time
{
    int h = 0;
    int m = 0;
    int s = 0;

    auto t0 = Time (h, m, s);
    auto n_time = t0-time_o;
    
    return n_time;
}

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
    } else {
        minute = 0;
        next_hour();    
        }
}

auto Time::next_second() -> void
{
    if (second < 59) {
        ++second;
    } else {
        second = 0;
        next_minute();
        }
}

auto main() -> int
{
    auto t = Time{ 23, 59, 59 };
//to_string()
    std::cout << "#to_string()" << "\n";
    std::cout << t.to_string() << "\n" << "\n";
//next_hour()
    std::cout << "#next_hour()" << "\n";
    t.next_hour();
    std::cout << t.to_string() << "\n" << "\n";
//next_minute()
    std::cout << "#next_minute()" << "\n";
    t.next_minute();
    std::cout << t.to_string() << "\n" << "\n";
//next_second()
    std::cout << "#next_second()" << "\n";
    t.next_second();
    std::cout << t.to_string() << "\n" << "\n";
//time_of_day()
    std::cout << "#time_of_day()" << "\n";
    std::cout << t.to_string(t.time_of_day()) << "\n" << "\n";
//count_minutes()
    std::cout << "#count_minutes()" << "\n";
    std::cout << t.count_minutes() << " " << "minutes after midnight" << "\n" << "\n";
//count_seconds()
    std::cout << "#next_seconds()" << "\n";
    std::cout << t.count_seconds() << " " << "seconds after midnight" << "\n" << "\n";
//time_to_midnight()
    std::cout << "#time_to_midnight()" << "\n";
    std::cout << t.time_to_midnight(t).to_string() << " "  << "to midnight" << "\n" << "\n";
//operator+
    std::cout << "#operator+" << "\n";
    auto a1 = Time{ 23, 59, 59 };
    auto b1 = Time{  1,  36,  17 };
    std::cout << "Time1 = " << a1.to_string() << "\n";
    std::cout << "Time2 = " << b1.to_string() << "\n";
    std::cout << "Time1 + Time2 = " << (a1 + b1).to_string() << "\n" << "\n";
//operator-
    std::cout << "#operator-" << "\n";
    auto a2 = Time{  3, 50, 59 };
    auto b2 = Time{  4, 59, 35 };
    std::cout << "Time1 = " << a2.to_string() << "\n";
    std::cout << "Time2 = " << b2.to_string() << "\n";
    std::cout << "Time1 - Time2 = " << (a2 - b2).to_string() << "\n" << "\n";
//operator<
    std::cout << "#operator<" << "\n";
    auto a3 = Time{ 23, 59, 59 };
    auto b3 = Time{  0,  0,  1 };
    if (a3 < b3) {
        std::cout << a3.to_string() << " > " << b3.to_string() << "\n";
    } else {
        std::cout << a3.to_string() << " ? " << b3.to_string() << "\n";
    }
    std::cout << "\n";
//operator>
    std::cout << "#operator>" << "\n";
    auto a4 = Time{ 23, 59, 59 };
    auto b4 = Time{  0,  0,  1 };
    if (a4 > b4) {
        std::cout << a4.to_string() << " > " << b4.to_string() << "\n";
    } else {
        std::cout << a4.to_string() << " ? " << b4.to_string() << "\n";
    }
    std::cout << "\n";
//operator==
    std::cout << "#operator==" << "\n";
    auto a5 = Time{ 11, 22, 33 };
    auto b5 = Time{ 11, 22, 33 };
    if (a5 == b5) {
        std::cout << a5.to_string() << " == " << b5.to_string() << "\n";
    } else {
        std::cout << a5.to_string() << " != " << b5.to_string() << "\n";
    }
    std::cout << "\n";
//operator!=
    std::cout << "#operator!=" << "\n";
    auto a6 = Time{ 10, 20, 30 };
    auto b6 = Time{  0,  0,  1 };
    if (a6 != b6) {
        std::cout << a6.to_string() << " != " << b6.to_string() << "\n";
    } else {
        std::cout << a6.to_string() << " == " << b6.to_string() << "\n";
    }
    std::cout << "\n";

    return 0;
}
