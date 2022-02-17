// printf_to_string.hpp : convert printf() parameters into a std::string
// requires -std=c++17 or later

#ifndef printf_to_string_hpp
#define printf_to_string_hpp

#include <cstdio>
#include <cstdarg>
#include <string>

inline std::string string_printf(const char *fmt,...) {
    std::string s{};
    va_list args, args2;
    va_start(args, fmt);
    va_copy(args2, args);

    s.resize(vsnprintf(nullptr, 0, fmt, args2) + 1);
    va_end(args2);
    vsprintf(s.data(), fmt, args);
    va_end(args);
    s.pop_back();
    return s;
}

#endif // printf_to_string_hpp